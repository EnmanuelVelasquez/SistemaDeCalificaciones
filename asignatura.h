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
Asignatura crearAsignatura();
void mostrarAsignatura();
void menuActualizarAsignatura();
Asignatura actualizarAsignatura();
void guardararchivoAsignaturas(Asignatura *asignaturas, int tamanoVectorAsignaturas);
void leerArchvivosAsignaturas(Asignatura *Asignaturas, int *tamanoVectorAsignaturas);
void eliminarAsignatura();

// Inicialización de las funciones:
Asignatura crearAsignatura(){
    Asignatura asignatura;
    printf("\nIngrese el ID de la asignatura: \n");
    scanf("%d", &asignatura.id);
    printf("Ingrese el nombre de la asignatura: \n");
    scanf("%s", asignatura.nombre);
    for(int contador = 0; contador < MAXCALIFICACIONES; contador++){
        asignatura.calificaciones[contador] = 0;    
        }
    printf("\nAsignatura creada correctamente\n");
    return asignatura;
}

void mostrarAsignatura(Asignatura asignatura){
    printf("Id: %d\n", asignatura.id);
    printf("Nombre: %s\n", asignatura.nombre);
    printf("Calificaciones: ");
    for(int contador = 0; contador < MAXCALIFICACIONES; contador++){
        printf("%.1f ", asignatura.calificaciones[contador]);
    }
    printf("\n");
}

void menuActualizarAsignatura(){
    printf("\nMenu para actualizar datos de una asignatura\n");
    printf("1. Cambiar id\n");
    printf("2. Cambiar nombre\n");
    printf("3. Cambiar calificacion\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

Asignatura actualizarAsignatura(Asignatura *asignaturas, int posicionModificarAsignatura){
    //Se recibe una posición del vector Asignaturas para seleccionar qué se desea modificar:
    int opcion = 1;    
    int posicionCalificacion;
    while (opcion != 0){
        menuActualizarAsignatura();
        scanf("%d", &opcion);
        switch (opcion){
        case 1:
            printf("Ingrese el nuevo id de la asignatura: ");
            scanf("%d", &asignaturas[posicionModificarAsignatura].id);
            printf("\nId actualizado exitosamente!\n");
            break;
        case 2:
            printf("Ingrese el nuevo nombre del asignatura: ");
            scanf("%s", asignaturas[posicionModificarAsignatura].nombre);
            printf("\nNombre actualizado exitosamente!\n");
            break;
        case 3:
            printf("\nIngrese la posición de la calificacion a modificar: ");
            scanf("%d", &posicionCalificacion);
            scanf("\nIngrse el valor de la calificacion: %f", &asignaturas[posicionModificarAsignatura].calificaciones[posicionCalificacion]);
            printf("\nCalificacion actualizada exitosamente!\n");
            break;
        case 0:
            printf("\nHas salido del menu de crear asignatura\n");
            break;
        default:
            printf("\nOpcion no válida!\n");
            break;
        }
    }
    //Se retorna el Asignatura modificado
    return asignaturas[posicionModificarAsignatura];
}

void guardararchivoAsignaturas(Asignatura *asignaturas, int tamanoVectorAsignaturas){
    FILE *archivoAsignaturas = fopen("data/asignaturas.bat", "wb"); //Modifica todo el archivoAsignatura en binario, cargando y actualizando todo el vector
    if(archivoAsignaturas == NULL){
        FILE_ERROR("Error al crear el archivo de asignaturas");// Retorna un código de error
    }
    fwrite(asignaturas, sizeof(Asignatura), tamanoVectorAsignaturas, archivoAsignaturas);
    fclose(archivoAsignaturas);
}

void leerArchvivosAsignaturas(Asignatura *Asignaturas, int *tamanoVectorAsignaturas){
    // Lee el archivo Asignaturas en binario
    FILE *archivoAsignaturas = fopen("data/asignaturas.bat", "rb");
    //Evaluamos si no está creado 
    if (archivoAsignaturas == NULL){
         // En caso que no esté creado, lo creamos de tipo binario
         archivoAsignaturas = fopen("data/asignaturas.bat", "wb"); 
         // Validamos nuevamente que esté creado
        if (archivoAsignaturas == NULL){
            FILE_ERROR("Error al crear el archivo de asignaturas"); //La macro finaliza el programa y muestra el mensaje
        }
        // Inicializa el tamaño del vector de Asignaturas en 0 para indicar que no hay nadie
    *tamanoVectorAsignaturas = 0; 
    fclose(archivoAsignaturas); // Cierra el archivo creado
    return;
    }
    // Inicializa el contador
    *tamanoVectorAsignaturas = 0; 
    while (*tamanoVectorAsignaturas < MAXASIGNATURAS && fread(&Asignaturas[*tamanoVectorAsignaturas], sizeof(Asignatura), 1, archivoAsignaturas)) {
        (*tamanoVectorAsignaturas)++;
    }
}

void eliminarAsignatura(Asignatura *Asignaturas, int *tamanoVectorAsignaturas, int idAsignatura){
    //Suponemos que el Asignatura no existe, inializamos en -1:
    int poscionAsignaturaEliminar = -1;
    for(int contador = 0; contador < *tamanoVectorAsignaturas; contador++){
        if (Asignaturas[contador].id == idAsignatura){ //Buscamos el id del Asignatura en el vector
            poscionAsignaturaEliminar = contador; //Asignamos la posición a la variable que vamos a usar
            break;
        }
    }
    if(poscionAsignaturaEliminar != -1){
        for (int contador = poscionAsignaturaEliminar; contador < *tamanoVectorAsignaturas - 1; contador++){
            //Reescribimos todo el vector desde el punto de referencia del Asignatura a eliminar
            Asignaturas[contador] = Asignaturas[contador + 1];
            //Los Asignaturas modificados fueron movidos una posición a la izquierda
        }
        (*tamanoVectorAsignaturas)--; //Reajustamos el tamaño del vector
        printf("Asignatura con ID %d eliminado exitosamente.\n", idAsignatura);
    } else {
        printf("Asignatura con ID %d no encontrado.\n", idAsignatura);
    }
}

void menuPrincipalAsignatura(){
    Asignatura asignaturas[MAXASIGNATURAS];
    int tamanoVectorAsignaturas = 0;
    int opcion = 1;
    int validarId;

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
                    Asignatura asignatura = crearAsignatura();
                    asignaturas[tamanoVectorAsignaturas] = asignatura;
                    tamanoVectorAsignaturas++;
                    guardararchivoAsignaturas(asignaturas, tamanoVectorAsignaturas); //Guardamos el Asignatura después de crearlo
                } else {
                    printf("\nEl máximo número de asignaturas ha sido alcanzado.\n");
                }
                break;
            case 2:
                //Se imprimen todos los Asignaturas guardados
                if(tamanoVectorAsignaturas == 0){
                    printf("\nNo hay Asignaturas para mostar!\n");
                    break;
                }else{
                    for (int contador = 0; contador < tamanoVectorAsignaturas; contador++){
                    printf("\nAsignatura %d:\n", contador);
                    mostrarAsignatura(asignaturas[contador]);
                    }
                }
                break;
            case 3:
                if(tamanoVectorAsignaturas == 0){
                    printf("\nNo hay Asignaturas para modificar!\n");
                    break;
                }else{
                    //Validamos la existencia del Asignatura en el vector
                    printf("\nIngrese el ID del Asignatura a modificar: ");
                    scanf("%d", &validarId);
                    for(int contador = 0; contador < tamanoVectorAsignaturas; contador++){
                        if(validarId != asignaturas[contador].id){
                            printf("\nEl ID ingresado no corresponde a ningun Asignatura!\n");
                            break;
                        }else if(validarId == asignaturas[contador].id){
                            printf("\nAsignatura encontrada!\n");
                            asignaturas[contador] = actualizarAsignatura(asignaturas, contador);
                            guardararchivoAsignaturas(asignaturas, tamanoVectorAsignaturas);
                        }
                    }
                }
                break;
            case 4:
                if(tamanoVectorAsignaturas == 0){
                        printf("\nNo hay Asignaturas para eliminar!\n");
                        break;
                    }else{
                        //Validamos la existencia del Asignatura en el vector
                        printf("\nIngrese el ID del Asignatura a eliminar: ");
                        scanf("%d", &validarId);
                        for(int contador = 0; contador < tamanoVectorAsignaturas; contador++){
                            if(validarId != asignaturas[contador].id){
                                printf("\nEl ID ingresado no corresponde a ningun Asignatura!\n");
                                break;
                            }else if(validarId == asignaturas[contador].id){
                                printf("\nAsignatura encontrado!\n");
                                eliminarAsignatura(asignaturas, &tamanoVectorAsignaturas, validarId);
                                guardararchivoAsignaturas(asignaturas, tamanoVectorAsignaturas); //Guardamos el Asignatura después de crearlo
                                break;
                            }
                        }
                    }
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