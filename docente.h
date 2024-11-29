#ifndef DOCENTE_H
#define DOCENTE_H
// Incluimos las librerías y otros archivos que vamos a utilizar:
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "estudiante.h"
#include "admin.h"
#include "asignatura.h"

// Creación de la estructura Docente:
typedef struct {
    int id;             // ID del docente
    char nombre[50];    // Nombre del docente
    char apellido[50];  // Apellido del docente 
    Asignatura asignaturas[MAXASIGNATURAS]; // Asignatura que enseña el docente
} Docente;

// Definición de las funciones de Docente:
int buscarDocentePorId(Docente *docentes, int tamanoVectorDocentes, int idDocente);
Docente crearDocente(Docente *docentes, int tamanoVectorDocentes);
void mostrarDocente(Docente docente);
Docente actualizarDocente(Docente *docentes, int tamanoVectorDocentes, int idDocente);
void guardarDocentes(Docente *docentes, int tamanoVectorDocentes);
void leerArchivosDocente(Docente *docentes, int *tamanoVectorDocentes);
void eliminarDocente(Docente *docentes, int *tamanoVectorDocentes, int idDocente);
void menuPrincipalDocente();
void menuInteraccionDocente();
void generarListadoAsignaturas(Docente *docentes, int tamanoVectorDocentes);
void generarInformeGeneral(Docente *docentes, int tamanoVectorDocentes);

// Inicialización de las funciones:

int buscarDocentePorId(Docente *docentes, int tamanoVectorDocentes, int idDocente) { 
    if (tamanoVectorDocentes == 0) {
        return -1; // No encontrado
    }
    if (docentes[tamanoVectorDocentes - 1].id == idDocente) {
        return tamanoVectorDocentes - 1; // Retorna el índice encontrado
    }
    return buscarDocentePorId(docentes, tamanoVectorDocentes - 1, idDocente);
}

Docente crearDocente(Docente *docentes, int tamanoVectorDocentes) {
    Docente docente;
    printf("\nIngrese ID del docente: ");
    scanf("%d", &docente.id);
    if(buscarDocentePorId(docentes, tamanoVectorDocentes, docente.id) != -1) {
        printf("El ID ya está en uso. Intente nuevamente.\n");
        return crearDocente(docentes, tamanoVectorDocentes);
    }
    printf("Ingrese el nombre del docente sin espacios: ");
    scanf("%49s", docente.nombre);
    printf("Ingrese el apellido del docente sin espacios: ");
    scanf("%49s", docente.apellido);
    printf("\nDocente creado exitosamente.\n");
    return docente;
}

void mostrarDocente(Docente docente) {
    printf("\nID: %d\n", docente.id);
    printf("Nombre: %s\n", docente.nombre);
    printf("Apellido: %s\n", docente.apellido);
}

void menuActualizarDocente(){
    printf("\nMenu para actualizar datos de un docente\n");
    printf("\n1. Cambiar ID\n");
    printf("2. Cambiar nombre\n");
    printf("3. Cambiar apellido\n");
    printf("0. Regresar al menu anterior\n");
    printf("\nSeleccione una opcion: ");
}

Docente actualizarDocente(Docente *docentes, int tamanoVectorDocentes, int idDocente) {
    int indice = buscarDocentePorId(docentes, tamanoVectorDocentes, idDocente);
    if (indice == -1) {
        printf("\nDocente no encontrado.\n");
        return docentes[indice];
    }
    int opcion = 1;
    while (opcion != 0) {
        menuActualizarDocente();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("\nIngrese el nuevo ID del docente: ");
                scanf("%d", &docentes[indice].id);
                printf("\nID actualizada exitosamente.\n");
                break;
            case 2:
                printf("\nIngrese el nuevo nombre del docente sin espacios: ");
                scanf("%49s", docentes[indice].nombre);
                printf("\nNombre actualizado exitosamente.\n");
                break;
            case 3:
                printf("\nIngrese el nuevo apellido del docente sin espacios: ");
                scanf("%49s", docentes[indice].apellido);
                printf("\nApellido actualizado exitosamente.\n");
                break;
            case 0:
                printf("\nSaliendo del menu de actualizacion.\n");
                Sleep(1000);
                break;
            default:
                printf("\nOpcion no valida.\n");
                break;
        }
    }
    return docentes[indice];
}

void guardarDocentes(Docente *docentes, int tamanoVectorDocentes) {
    FILE *archivoDocentes = ABRIR_ARCHIVO("data/docentes.bat", "wb");  // Modifica todo el archivo de docentes en binario
    if(archivoDocentes == NULL) {
        FILE_ERROR("Error al crear el archivo de docentes");
    }
    fwrite(docentes, sizeof(Docente), tamanoVectorDocentes, archivoDocentes);
    CERRAR_ARCHIVO(archivoDocentes);
}

void leerArchivosDocente(Docente *docentes, int *tamanoVectorDocentes) {
    FILE *archivoDocentes = ABRIR_ARCHIVO("data/docentes.bat", "rb"); 
    if (archivoDocentes == NULL) {
        archivoDocentes = ABRIR_ARCHIVO("data/docentes.bat", "wb"); 
        if (archivoDocentes == NULL) {
            FILE_ERROR("Error al crear el archivo de docentes");
        }
        *tamanoVectorDocentes = 0;
        CERRAR_ARCHIVO(archivoDocentes);
        return;
    }
    *tamanoVectorDocentes = 0;
    while (*tamanoVectorDocentes < MAXDOCENTES && fread(&docentes[*tamanoVectorDocentes], sizeof(Docente), 1, archivoDocentes)) {
        (*tamanoVectorDocentes)++;
    }
}

void eliminarDocente(Docente *docentes, int *tamanoVectorDocentes, int idDocente) {
    int indice = buscarDocentePorId(docentes, *tamanoVectorDocentes, idDocente);
    int confirmacion;
    if (indice == -1) {
        printf("\nDocente con ID %d no encontrado.\n", idDocente);
        return;
    }
    printf("\nEsta seguro de que desea eliminar al docente con ID %d?\n", idDocente);
    printf("\n1. Si");
    printf("\n0. No\n");
    printf("\nSeleccione una opcion: ");
    scanf("%d", &confirmacion);
    if (confirmacion != 1) {
        printf("\nEliminacion cancelada.\n");
        return;
    }
    // Eliminar al docente desplazando el resto del vector
    for (int contador = indice; contador < *tamanoVectorDocentes - 1; contador++){
        docentes[contador] = docentes[contador + 1];
    }
    (*tamanoVectorDocentes)--;
    printf("\nDocente con ID %d eliminado exitosamente.\n", idDocente);
}

void menuPrincipalDocente(){
    Docente docentes[MAXDOCENTES];
    int tamanoVectorDocentes = 0;
    int opcion;
    
    leerArchivosDocente(docentes, &tamanoVectorDocentes);
    
    while (opcion != 0){
        printf("\nMenu principal docentes\n");
        printf("\n1. Crear docente\n");
        printf("2. Mostrar docentes\n");
        printf("3. Modificar docente\n");
        printf("4. Eliminar docente\n");
        printf("0. Regresar al menu anterior\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                if (tamanoVectorDocentes < MAXDOCENTES) {
                    docentes[tamanoVectorDocentes] = crearDocente(docentes, tamanoVectorDocentes);
                    tamanoVectorDocentes++;
                    guardarDocentes(docentes, tamanoVectorDocentes);
                } else {
                    printf("\nNo se pueden agregar mas docentes.\n");
                }
                break;
            case 2:
                if (tamanoVectorDocentes == 0) {
                    printf("\nNo hay docentes registrados.\n");
                } else {
                    for (int contador = 0; contador < tamanoVectorDocentes; contador++) {
                        printf("\nDocente %d:\n", contador+1);
                        mostrarDocente(docentes[contador]);
                    }
                }
                break;
            case 3:
                printf("\nIngrese el ID del docente a modificar: ");
                int idModificar;
                scanf("%d", &idModificar);
                actualizarDocente(docentes, tamanoVectorDocentes, idModificar);
                guardarDocentes(docentes, tamanoVectorDocentes);
                break;
            case 4:
                printf("\nIngrese el ID del docente a eliminar: ");
                int idEliminar;
                scanf("%d", &idEliminar);
                eliminarDocente(docentes, &tamanoVectorDocentes, idEliminar);
                guardarDocentes(docentes, tamanoVectorDocentes);
                break;
            case 0:
                printf("\nSaliendo del menu de docentes.\n");
                Sleep(1000);
                break;
            default:
                printf("\nOpcion no valida.\n");
        }
    }
}

void menuInteraccionDocente(){
    Asignatura asignaturas[MAXASIGNATURAS];
    Docente docentes[MAXDOCENTES];
    int tamanoVectorAsignaturas;
    int tamanoVectorDocentes;
    int opcion = 1;

    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas);
    leerArchivosDocente(docentes, &tamanoVectorDocentes);
    
    while(opcion != 0){
        printf("\n--- Menu de Docente ---\n");
        printf("\n1. Gestionar estudiantes\n");
        printf("2. Gestionar asignaturas\n");
        printf("3. Generar informe de asignaturas\n");
        printf("4. Generar informe general\n");
        printf("0. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                menuPrincipalEstudiante();
                break;
                printf("Regresando al menu principal...\n");
                break;
            case 2:
                menuPrincipalAsignatura();
                break;
            case 3:
                generarListadoAsignaturas(docentes, tamanoVectorDocentes);
                break;
            case 4:
                generarInformeGeneral(docentes, tamanoVectorDocentes);
                break;
            case 0:
                salir();
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } 
}

//INFORME ASIGNATURAS // TODOS LOS ESTUDIANTES CON NOTAS DEL ESTUDIANTE 
void generarListadoAsignaturas(Docente *docentes, int tamanoVectorDocentes){
    Estudiante estudiantes[MAXESTUDIANTES];
    Asignatura asignaturas[MAXASIGNATURAS];
    int tamanoVectorEstudiantes;
    int tamanoVectorAsignaturas;
    int idAsignatura; 
    int idDocente;  
    
    leerArchivosEstudiante(estudiantes, &tamanoVectorEstudiantes);
    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas);

    for (int contador = 0; contador < tamanoVectorDocentes; contador++) {
                        printf("\nDocente %d:\n", contador+1);
                        mostrarDocente(docentes[contador]);
    }  
    printf("\nIngrese el ID del docente a generar listado de asignaturas: ");
    scanf("%d", &idDocente);
    int indiceDocente = buscarDocentePorId(docentes, tamanoVectorDocentes, idDocente);
    if(indiceDocente == -1){
        printf("Docente no encontrado.\n");
        return;
    }
    
    for (int contador = 0; contador < tamanoVectorAsignaturas; contador++){
        printf("\nAsignatura %d:\n", contador + 1);
        mostrarAsignatura(asignaturas[contador]);
        }
    printf("\nIngrese la asignatura a generar listado: ");
    scanf("%d", &idAsignatura);
    int indceAsignatura = buscarAsignaturaPorId(asignaturas, tamanoVectorAsignaturas, idAsignatura);
    if(indceAsignatura == -1){
        printf("Asignatura no encontrada.\n");
        return;
    }

    FILE *archivoBoletin = ABRIR_ARCHIVO("data/informeAsignatura.txt", "wb"); // Crear archivo de texto
    if (archivoBoletin == NULL) {
        FILE_ERROR("Error al crear el archivo de boletin");
    }
    fprintf(archivoBoletin, "***************** INFORME DE ASIGNATURAS ******************\n\n");
    fprintf(archivoBoletin, "Institución: Universidad Tecnológica de Pereira\n\n");
    fprintf(archivoBoletin, "Nombre del docente: %s %s\n", docentes[indiceDocente].nombre, docentes[indiceDocente].apellido);
    fprintf(archivoBoletin, "Id del docente: %d\n\n", docentes[indiceDocente].id);

    fprintf(archivoBoletin, "Asignatura: %s\n", asignaturas[indceAsignatura].nombre);
    fprintf(archivoBoletin, "\nEstudiantes: \n");
    fprintf(archivoBoletin, "-------------------------------------------------------------\n");
    fprintf(archivoBoletin, " ID | -- Nombre -- | --- Calificaciones ---");
    fprintf(archivoBoletin, "\n-------------------------------------------------------------\n");
    for(int contador = 0; contador < tamanoVectorEstudiantes; contador++){
        fprintf(archivoBoletin, "%d |", estudiantes[contador].id);
        fprintf(archivoBoletin, " %s %s ", estudiantes[contador].apellido, estudiantes[contador].nombre);
        for(int contador2 = 1; contador2 < MAXCALIFICACIONES; contador2++){
            fprintf(archivoBoletin, "| %.1f", estudiantes[contador].asignaturas[0].calificaciones[contador2]);
        }
        fprintf(archivoBoletin, "\n-------------------------------------------------------------\n");
    }
    fprintf(archivoBoletin, "\n*************************************************************");
    printf("\nListado generado exitosamente.\n");
    CERRAR_ARCHIVO(archivoBoletin);
}

//INFORME GENERAL// TODOS LOS ESTUDIANTES CON PROMEDIO FINAL
void generarInformeGeneral(Docente *docentes, int tamanoVectorDocentes){
    Asignatura asignaturas[MAXASIGNATURAS];
    Estudiante estudiantes[MAXESTUDIANTES];
    int tamanoVectorAsignaturas;
    int tamanoVectorEstudiantes;
    int idDocenteInforme;

    leerArchivosEstudiante(estudiantes, &tamanoVectorEstudiantes);
    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas);

    for (int contador = 0; contador < tamanoVectorDocentes; contador++) {
        printf("\nDocente %d:\n", contador+1);
        mostrarDocente(docentes[contador]);
    }
    printf("\nIngrese el ID del docente a generar informe: ");
    scanf("%d", &idDocenteInforme);
    int indiceDocente = buscarDocentePorId(docentes, tamanoVectorDocentes, idDocenteInforme);
    if(indiceDocente == -1){
        printf("Docente no encontrado.\n");
        return;
    }
  
    FILE *archivoBoletin = ABRIR_ARCHIVO("data/informeGeneral.txt", "wb"); // Crear archivo de texto
    if (archivoBoletin == NULL) {
        FILE_ERROR("Error al crear el archivo de boletin");
    }

    fprintf(archivoBoletin, "***************** INFORME GENERAL ******************\n\n");
    fprintf(archivoBoletin, "Institución: Universidad Tecnológica de Pereira\n\n");
    fprintf(archivoBoletin, "Nombre del docente: %s %s\n", docentes[indiceDocente].nombre, docentes[indiceDocente].apellido);
    fprintf(archivoBoletin, "Id del docente: %d\n\n", docentes[indiceDocente].id);

    fprintf(archivoBoletin, "Asignaturas:\n");
    fprintf(archivoBoletin, "-------------------------------------------------------------\n");

    for(int contador = 0; contador < tamanoVectorAsignaturas; contador++){
        if(estudiantes[contador].asignaturas[contador].id == asignaturas[contador].id){
            fprintf(archivoBoletin, "Asignatura %s: \n", asignaturas[contador].nombre);
            fprintf(archivoBoletin, "ID asignatura: %d", asignaturas[contador].id);
            for(int contador2 = 0; contador2 < tamanoVectorAsignaturas; contador2++){
                fprintf(archivoBoletin, "\n\nNombre estudiante: %s %s\n", estudiantes[contador2].nombre, estudiantes[contador2].apellido);
                fprintf(archivoBoletin, "Id estudiante: %d\n", estudiantes[contador2].id);
                fprintf(archivoBoletin, "Promedio final asignatura: %.1f / ", obtenerPromedio(estudiantes[contador2].asignaturas[contador].calificaciones, MAXCALIFICACIONES));
                fprintf(archivoBoletin, EVALUAR_ESTADO(obtenerPromedio(estudiantes[contador2].asignaturas[contador2].calificaciones, MAXCALIFICACIONES)));
            }
            fprintf(archivoBoletin, "\n-------------------------------------------------------------\n");
        }
    }
    fprintf(archivoBoletin, "\n***************************************************************");
    printf("\nInforme generado exitosamente.\n");
    CERRAR_ARCHIVO(archivoBoletin);
}

#endif
