//Definimos la macro ASIGNATURA_H
#ifndef ASIGNATURA_H
#define ASIGNATURA_H
//Incluímos las librerías y otros archivos.h que vamos a utilizar:
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"

// Creación de la estructura Asignatura:
typedef struct {
    int id;
    char nombre[50];
    float calificaciones[MAXCALIFICACIONES];
} Asignatura;

// Definición de las funciones de Asignatura:
int buscarAsignaturaPorId(Asignatura *asignaturas, int tamanoVectorAsignaturas, int idAsignatura);
Asignatura crearAsignatura();
void mostrarAsignatura();
void menuActualizarAsignatura();
Asignatura actualizarAsignatura();
void guardararchivoAsignaturas(Asignatura *asignaturas, int tamanoVectorAsignaturas);
void leerArchvivosAsignaturas(Asignatura *Asignaturas, int *tamanoVectorAsignaturas);
void eliminarAsignatura();

// Inicialización de las funciones:
int buscarAsignaturaPorId(Asignatura *asignaturas, int tamanoVectorAsignaturas, int idAsignatura){//Función recursiva
    if (tamanoVectorAsignaturas == 0) {
        return -1; // No encontrado
    }
    if (asignaturas[tamanoVectorAsignaturas - 1].id == idAsignatura) {
        return tamanoVectorAsignaturas - 1; // Retorna el índice encontrado
    }
    return buscarAsignaturaPorId(asignaturas, tamanoVectorAsignaturas - 1, idAsignatura);
}

Asignatura crearAsignatura(Asignatura *asignaturas, int tamanoVectorAsiganutas){
    Asignatura asignatura;
    printf("\nIngrese el ID de la asignatura: \n");
    scanf("%d", &asignatura.id);
    if(buscarAsignaturaPorId(asignaturas, tamanoVectorAsiganutas, asignatura.id) != -1){
        printf("El ID ya está en uso. Intente nuevamente.\n");
        return crearAsignatura(asignaturas, tamanoVectorAsiganutas);
    }
    printf("Ingrese el nombre de la asignatura sin espacios: \n");
    scanf("%s", asignatura.nombre);
    printf("\nAsignatura creada correctamente\n");
    return asignatura;
}

void mostrarAsignatura(Asignatura asignatura){
    printf("Id: %d\n", asignatura.id);
    printf("Nombre: %s\n", asignatura.nombre);
}

void menuActualizarAsignatura(){
    printf("\nMenu para actualizar datos de una asignatura\n");
    printf("1. Cambiar id\n");
    printf("2. Cambiar nombre\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

Asignatura actualizarAsignatura(Asignatura *asignaturas, int tamanoVectorAsignaturas, int idAsignatura){
    int indice = buscarAsignaturaPorId(asignaturas, tamanoVectorAsignaturas, idAsignatura);
    if (indice == -1){
        printf("No existe asignatura con ese id\n");
        return asignaturas[indice];
    }
    int opcion = 1;    
    while (opcion != 0){
        menuActualizarAsignatura();
        scanf("%d", &opcion);
        switch (opcion){
        case 1:
            printf("Ingrese el nuevo id de la asignatura: ");
            scanf("%d", &asignaturas[indice].id);
            printf("\nId actualizado exitosamente!\n");
            break;
        case 2:
            printf("Ingrese el nuevo nombre del asignatura sin espacios: ");
            scanf("%s", asignaturas[indice].nombre);
            printf("\nNombre actualizado exitosamente!\n");
            break;
        case 0:
            printf("\nHas salido del menu de crear asignatura\n");
            break;
        default:
            printf("\nOpcion no valida!\n");
            break;
        }
    }
    //Se retorna el Asignatura modificado
    return asignaturas[indice];
}

void guardararchivoAsignaturas(Asignatura *asignaturas, int tamanoVectorAsignaturas){
    FILE *archivoAsignaturas = ABRIR_ARCHIVO("data/asignaturas.bat", "wb"); //Modifica todo el archivoAsignatura en binario, cargando y actualizando todo el vector
    if(archivoAsignaturas == NULL){ 
        FILE_ERROR("Error al crear el archivo de asignaturas");// Retorna un código de error
    }
    fwrite(asignaturas, sizeof(Asignatura), tamanoVectorAsignaturas, archivoAsignaturas);
    CERRAR_ARCHIVO(archivoAsignaturas);
}

void leerArchvivosAsignaturas(Asignatura *Asignaturas, int *tamanoVectorAsignaturas){
    // Lee el archivo Asignaturas en binario
    FILE *archivoAsignaturas = ABRIR_ARCHIVO("data/asignaturas.bat", "rb");
    //Evaluamos si no está creado 
    if (archivoAsignaturas == NULL){
         // En caso que no esté creado, lo creamos de tipo binario
         archivoAsignaturas = ABRIR_ARCHIVO("data/asignaturas.bat", "wb");
         // Validamos nuevamente que esté creado
        if (archivoAsignaturas == NULL){
            FILE_ERROR("Error al crear el archivo de asignaturas"); //La macro finaliza el programa y muestra el mensaje
        }
        // Inicializa el tamaño del vector de Asignaturas en 0 para indicar que no hay nadie
    *tamanoVectorAsignaturas = 0; 
    CERRAR_ARCHIVO(archivoAsignaturas); // Cierra el archivo creado
    return;
    }
    // Inicializa el contador
    *tamanoVectorAsignaturas = 0; 
    while (*tamanoVectorAsignaturas < MAXASIGNATURAS && fread(&Asignaturas[*tamanoVectorAsignaturas], sizeof(Asignatura), 1, archivoAsignaturas)) {
        (*tamanoVectorAsignaturas)++;
    }
    CERRAR_ARCHIVO(archivoAsignaturas);
}

void eliminarAsignatura(Asignatura *Asignaturas, int *tamanoVectorAsignaturas, int idAsignatura) {
    int indice = buscarAsignaturaPorId(Asignaturas, *tamanoVectorAsignaturas, idAsignatura);
    int confirmacion;
    if (indice == -1) {
        printf("Asignatura con ID %d no encontrado.\n", idAsignatura);
        return;
    }
    printf("\nEsta seguro de que desea eliminar la asignatura con ID %d?\n", idAsignatura);
    printf("\n1. Si");
    printf("\n0. No");
    printf("\nSeleccione una opcion: ");
    scanf("%d", &confirmacion);
    if (confirmacion != 1) {
        printf("\nEliminacion cancelada.\n");
        return;
    }
    for (int contador = indice; contador < *tamanoVectorAsignaturas - 1; contador++) {
        Asignaturas[contador] = Asignaturas[contador + 1];
    }
    (*tamanoVectorAsignaturas)--;
    printf("Asignatura con ID %d eliminado exitosamente.\n", idAsignatura);
}

void menuPrincipalAsignatura(){
    Asignatura asignaturas[MAXASIGNATURAS];
    int tamanoVectorAsignaturas;
    int opcion = 1;

    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas); //Si hay datos en el vector, los leemos

    while(opcion != 0){
        printf("\nMenu principal asignaturas\n");
        printf("1. Crear asignatura\n");
        printf("2. Mostrar asignaturas\n");
        printf("3. Modificar asignatura\n");
        printf("4. Eliminar asignatura\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion){
            case 1:
                // Validamos que halla espacio para crear más Asignaturas
                if (tamanoVectorAsignaturas < MAXASIGNATURAS) {
                    asignaturas[tamanoVectorAsignaturas] = crearAsignatura(asignaturas, tamanoVectorAsignaturas);
                    tamanoVectorAsignaturas++;
                    guardararchivoAsignaturas(asignaturas, tamanoVectorAsignaturas); //Guardamos el Asignatura después de crearlo
                } else {
                    printf("\nEl maximo numero de asignaturas ha sido alcanzado.\n");
                }
                break;
            case 2:
                //Se imprimen todos las asignaturas guardadas
                if(tamanoVectorAsignaturas == 0){
                    printf("\nNo hay Asignaturas para mostar!\n");
                    break;
                }else{
                    for (int contador = 0; contador < tamanoVectorAsignaturas; contador++){
                    printf("\nAsignatura %d:\n", contador + 1);
                    mostrarAsignatura(asignaturas[contador]);
                    }
                }
                break;
            case 3:
                printf("Ingrese el ID de la asignatura a modificar: ");
                int idModificar;
                scanf("%d", &idModificar);
                actualizarAsignatura(asignaturas, tamanoVectorAsignaturas, idModificar);
                guardararchivoAsignaturas(asignaturas, tamanoVectorAsignaturas);
                break;
            case 4:
                printf("Ingrese el ID de la asignatura a eliminar: ");
                int idEliminar;
                scanf("%d", &idEliminar);
                eliminarAsignatura(asignaturas, &tamanoVectorAsignaturas, idEliminar);
                guardararchivoAsignaturas(asignaturas, tamanoVectorAsignaturas);
                break;
            case 0:
                printf("\nHas salido del menu de asignatura\n");
                break;
            default:
                break;
        }
    }
}

#endif