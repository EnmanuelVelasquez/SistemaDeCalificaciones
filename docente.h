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
    printf("\nDocente creado exitosamente.\n");
    return docente;
}

void mostrarDocente(Docente docente) {
    printf("\nID: %d\n", docente.id);
    printf("Nombre: %s\n", docente.nombre);
}

void menuActualizarDocente(){
    printf("\nMenu para actualizar datos de un docente\n");
    printf("\n1. Cambiar ID\n");
    printf("2. Cambiar nombre\n");
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
    Docente docentes[MAXDOCENTES];
    int tamanoVectorDocentes;
    int opcion = 1;

    leerArchivosDocente(docentes, &tamanoVectorDocentes);
    
    while(opcion != 0){
        printf("\n--- Menu de Docente ---\n");
        printf("\n1. Gestionar estudiantes\n");
        printf("2. Gestionar asignaturas\n");
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
            case 0:
                salir();
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } 
}


#endif
