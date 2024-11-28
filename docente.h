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
    char contrasena[50]; // Contraseña del docente
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
    printf("Ingrese ID del docente: ");
    scanf("%d", &docente.id);
    if(buscarDocentePorId(docentes, tamanoVectorDocentes, docente.id) != -1) {
        printf("El ID ya está en uso. Intente nuevamente.\n");
        return crearDocente(docentes, tamanoVectorDocentes);
    }
    printf("Ingrese nombre del docente: ");
    scanf("%49s", docente.nombre);
    printf("Ingrese contrasena del docente: ");
    scanf("%49s", docente.contrasena);
    printf("\nDocente creado exitosamente.\n");
    return docente;
}

void mostrarDocente(Docente docente) {
    printf("\nID: %d\n", docente.id);
    printf("Nombre: %s\n", docente.nombre);
    printf("Contrasena: %s\n", docente.contrasena);
}

void menuActualizarDocente(){
    printf("\nMenu para actualizar datos de un docente\n");
    printf("1. Cambiar ID\n");
    printf("2. Cambiar nombre\n");
    printf("3. Cambiar contrasena\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

Docente actualizarDocente(Docente *docentes, int tamanoVectorDocentes, int idDocente) {
    int indice = buscarDocentePorId(docentes, tamanoVectorDocentes, idDocente);
    if (indice == -1) {
        printf("Docente no encontrado.\n");
        return docentes[indice];
    }
    int opcion = 1;
    while (opcion != 0) {
        menuActualizarDocente();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Ingrese el nuevo ID del docente: ");
                scanf("%d", &docentes[indice].id);
                break;
            case 2:
                printf("Ingrese el nuevo nombre del docente: ");
                scanf("%49s", docentes[indice].nombre);
                break;
            case 3:
                printf("Ingrese la nueva contraseña del docente: ");
                scanf("%49s", docentes[indice].contrasena);
                break;
            case 0:
                printf("Saliendo del menu de actualización.\n");
                break;
            default:
                printf("Opción no válida.\n");
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
    if (indice == -1) {
        printf("Docente con ID %d no encontrado.\n", idDocente);
        return;
    }
    for (int contador = indice; contador < *tamanoVectorDocentes - 1; contador++) {
        docentes[contador] = docentes[contador + 1];
    }
    (*tamanoVectorDocentes)--;
    printf("Docente con ID %d eliminado exitosamente.\n", idDocente);
}

void menuPrincipalDocente() {
    Docente docentes[MAXDOCENTES];
    int tamanoVectorDocentes;
    int opcion = 1;

    leerArchivosDocente(docentes, &tamanoVectorDocentes);
    
    while (opcion != 0) {
        printf("\nMenu principal docentes\n");
        printf("1. Crear docente\n");
        printf("2. Mostrar docentes\n");
        printf("3. Modificar docente\n");
        printf("4. Eliminar docente\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                if (tamanoVectorDocentes < MAXDOCENTES) {
                    docentes[tamanoVectorDocentes] = crearDocente(docentes, tamanoVectorDocentes);
                    tamanoVectorDocentes++;
                    guardarDocentes(docentes, tamanoVectorDocentes);
                } else {
                    printf("No se pueden agregar más docentes.\n");
                }
                break;
            case 2:
                if (tamanoVectorDocentes == 0) {
                    printf("No hay docentes registrados.\n");
                } else {
                    for (int contador = 0; contador < tamanoVectorDocentes; contador++) {
                        printf("\nDocente %d:\n", contador);
                        mostrarDocente(docentes[contador]);
                    }
                }
                break;
            case 3:
                printf("Ingrese el ID del docente a modificar: ");
                int idModificar;
                scanf("%d", &idModificar);
                actualizarDocente(docentes, tamanoVectorDocentes, idModificar);
                guardarDocentes(docentes, tamanoVectorDocentes);
                break;
            case 4:
                printf("Ingrese el ID del docente a eliminar: ");
                int idEliminar;
                scanf("%d", &idEliminar);
                eliminarDocente(docentes, &tamanoVectorDocentes, idEliminar);
                guardarDocentes(docentes, tamanoVectorDocentes);
                break;
            case 0:
                printf("Saliendo del menú de docentes.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    }
}

void menuInteraccionDocente(){
    Docente docentes[MAXDOCENTES];
    int tamanoVectorDocentes;
    int opcion = 1;

    leerArchivosDocente(docentes, &tamanoVectorDocentes);
    
    while(opcion != 0){
        printf("\n--- Menú de Docente ---\n");
        printf("1. Gestionar estudiantes\n");
        printf("0. Volver al menú principal\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menuPrincipalEstudiante();
                break;
                printf("Regresando al menú principal...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
                break;
        }
    } 
}


#endif
