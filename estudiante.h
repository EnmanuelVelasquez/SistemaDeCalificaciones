//Definimos la macro ESTUDIANTE_H:
#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H
//Incluímos las librerías y otros archivos.h que vamos a utilizar:
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "asignatura.h"

// Creación de la estructura estudiante:
typedef struct{
    int id;
    char nombre[50];
    char apellido[50];
    char contrasena[50];
    Asignatura asignaturas[6];
} Estudiante;

// Definición de las funciones de estudiante:
Estudiante crearEstudiante();
void mostrarEstudiante(Estudiante estudiante);
void menuActualizarEstudiante();
Estudiante actualizarEstudiante(Estudiante *estudiantes, int tamanoVector);
void guardararchivoEstudiantes(Estudiante *estudiantes, int tamanoVectorEstudiantes);
void leerArchvivosEstudiantes(Estudiante *estudiantes, int *tamanoVectorEstudiantes);
void eliminarEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes, int idEstudiante);
void mostrarCalificacion();
void generarBoletin();
void menuPrincipalEstudiante();
void menuInteraccionEstudiante();

// Inicialización de las funciones:
Estudiante crearEstudiante(){
    Estudiante estudiante;
    printf("\nIngrese el ID de estudiante: \n");
    scanf("%d", &estudiante.id);
    printf("Ingrese el nombre del estudiante: \n");
    scanf("%s", estudiante.nombre);
    printf("Ingrese el apellido del estudiante: \n");
    scanf("%s", estudiante.apellido);
    printf("Ingrese la contrasena del estudiante: \n");
    scanf("%s", estudiante.contrasena);
    printf("\nEstudiante creado exitosamente.\n");
    return estudiante;  
}

void mostrarEstudiante(Estudiante estudiante){
    printf("\nID: %d\n", estudiante.id);
    printf("Nombre: %s\n", estudiante.nombre);
    printf("Apellido: %s\n", estudiante.apellido);
    printf("Contrasena: %s\n", estudiante.contrasena);
}

void menuActualizarEstudiante(){
    printf("\nMenu para actualizar datos de un estudiante\n");
    printf("1. Cambiar ID\n");
    printf("2. Cambiar nombre\n");
    printf("3. Cambiar apellido\n");
    printf("4. Cambiar contrasena\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

Estudiante actualizarEstudiante(Estudiante *estudiantes, int posicionModificarEstudiante){
    //Se recibe una posición del vector estudiantes para seleccionar qué se desea modificar:
    int opcion = 1;    
    while (opcion != 0){
        menuActualizarEstudiante();
        scanf("%d", &opcion);
        switch (opcion){
        case 1:
            printf("Ingrese el nuevo ID de estudiante: ");
            scanf("%d", &estudiantes[posicionModificarEstudiante].id);
            printf("ID actualizado exitosamente.\n");
            break;  
        case 2:
            printf("Ingrese el nuevo nombre del estudiante: ");
            scanf("%s", estudiantes[posicionModificarEstudiante].nombre);
            printf("Nombre actualizado exitosamente.\n");
            break;
        case 3:
            printf("Ingrese el nuevo apellido del estudiante: ");
            scanf("%s", estudiantes[posicionModificarEstudiante].apellido);
            printf("Apellido actualizado exitosamente.\n");
            break;
        case 4:
            printf("Ingrese la nueva contraseña del estudiante: ");
            scanf("%s", estudiantes[posicionModificarEstudiante].contrasena);
            printf("Contraseña actualizada exitosamente.\n");
            break;
        //case 5:
            /*printf("Ingrese el nuevo nombre de asignatura: \n");
            scanf("%d", &estudiante.asignaturas[0].nombre);
            printf("Nombre de asignatura actualizado exitosamente.\n");
            break;*/
        //case 6:
            /*printf("Ingrese la nueva calificacion de asignatura: \n");
            scanf("%f", &estudiante.asignaturas[0].calificaciones[0]);
            printf("Calificacion actualizada correctamente\n");*/
        case 0:
            printf("\nHas salido del menu de crear estudiante\n");
            break;
        default:
            printf("\nOpcion no válida\n");
            break;
        }
    }
    //Se retorna el estudiante modificado
    return estudiantes[posicionModificarEstudiante];
}

void guardararchivoEstudiantes(Estudiante *estudiantes, int tamanoVectorEstudiantes){
    FILE *archivoEstudiantes = fopen("data/estudiantes.bat", "wb"); //Modifica todo el archivoEstudiantes en binario, cargando y actualizando todo el vector
    if(archivoEstudiantes == NULL){
        FILE_ERROR("Error al crear el archivo de estudiantes");// Retorna un código de error
    }
    fwrite(estudiantes, sizeof(Estudiante), tamanoVectorEstudiantes, archivoEstudiantes);
    fclose(archivoEstudiantes);
}

void leerArchvivosEstudiantes(Estudiante *estudiantes, int *tamanoVectorEstudiantes){
    // Lee el archivo estudiantes en binario
    FILE *archivoEstudiantes = fopen("data/estudiantes.bat", "rb");
    //Evaluamos si no está creado 
    if (archivoEstudiantes == NULL){
         // En caso que no esté creado, lo creamos de tipo binario
         archivoEstudiantes = fopen("data/estudiantes.bat", "wb"); 
         // Validamos nuevamente que esté creado
        if (archivoEstudiantes == NULL){
            FILE_ERROR("Error al crear el archivo de estudiantes"); // Retorna un código de error
        }
        // Inicializa el tamaño del vector de estudiantes en 0 para indicar que no hay nadie
    *tamanoVectorEstudiantes = 0; 
    fclose(archivoEstudiantes); // Cierra el archivo creado
    return;
    }
    // Inicializa el contador
    *tamanoVectorEstudiantes = 0; 
    while (*tamanoVectorEstudiantes < MAXESTUDIANTES && fread(&estudiantes[*tamanoVectorEstudiantes], sizeof(Estudiante), 1, archivoEstudiantes)) {
        (*tamanoVectorEstudiantes)++;
    }
}

void eliminarEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes, int idEstudiante){
    //Suponemos que el estudiante no existe, inializamos en -1:
    int poscionEstudianteEliminar = -1;
    for (int contador = 0; contador < *tamanoVectorEstudiantes; contador++) {
        if (estudiantes[contador].id == idEstudiante){ //Buscamos el id del estudiante en el vector
            poscionEstudianteEliminar = contador; //Asignamos la posición a la variable que vamos a usar
            break;
        }
    }
    if (poscionEstudianteEliminar != -1) {
        for (int contador = poscionEstudianteEliminar; contador < *tamanoVectorEstudiantes - 1; contador++){
            //Reescribimos todo el vector desde el punto de referencia del estudiante a eliminar
            estudiantes[contador] = estudiantes[contador + 1];
            //Los estudiantes modificados fueron movidos una posición a la izquierda
        }
        (*tamanoVectorEstudiantes)--; //Reajustamos el tamaño del vector
        printf("Estudiante con ID %d eliminado exitosamente.\n", idEstudiante);
    } else {
        printf("Estudiante con ID %d no encontrado.\n", idEstudiante);
    }
}

void mostrarCalificacion();

void generarBoletin();

void menuPrincipalEstudiante(){
    Estudiante estudiantes[MAXESTUDIANTES];
    int tamanoVectorEstudiantes = 0;
    int opcion = 1;
    int validarId;

    leerArchvivosEstudiantes(estudiantes, &tamanoVectorEstudiantes); //Si hay datos en el vector, los leemos

    while(opcion != 0){
        printf("\nMenu Principal Estudiante\n");
        printf("1. Crear Estudiante\n");
        printf("2. Mostrar Estudiantes\n");
        printf("3. Modificar Estudiante\n");
        printf("4. Eliminar Estudiante\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion){
            case 1:
                // Validamos que halla espacio para crear más estudiantes
                if (tamanoVectorEstudiantes < MAXESTUDIANTES) {
                    Estudiante estudiante = crearEstudiante();
                    estudiantes[tamanoVectorEstudiantes] = estudiante;
                    tamanoVectorEstudiantes++;
                    guardararchivoEstudiantes(estudiantes, tamanoVectorEstudiantes); //Guardamos el estudiante después de crearlo
                } else {
                    printf("El máximo número de estudiantes ha sido alcanzado.\n");
                }
                break;
            case 2:
                //Se imprimen todos los estudiantes guardados
                if(tamanoVectorEstudiantes == 0){
                    printf("\nNo hay estudiantes para mostar!\n");
                    break;
                }else{
                    for (int contador = 0; contador < tamanoVectorEstudiantes; contador++){
                    printf("\nEstudiante %d:\n", contador);
                    mostrarEstudiante(estudiantes[contador]);
                    }
                }
                break;
            case 3:
                if(tamanoVectorEstudiantes == 0){
                    printf("\nNo hay estudiantes para modificar!\n");
                    break;
                }else{
                    //Validamos la existencia del estudiante en el vector
                    printf("\nIngrese el ID del estudiante a modificar: ");
                    scanf("%d", &validarId);
                    for(int contador = 0; contador < tamanoVectorEstudiantes; contador++){
                        if(validarId != estudiantes[contador].id){
                            printf("\nEl ID ingresado no corresponde a ningun estudiante!\n");
                            break;
                        }else if(validarId == estudiantes[contador].id){
                            printf("\nEstudiante encontrado!\n");
                            estudiantes[contador] = actualizarEstudiante(estudiantes, contador);
                            guardararchivoEstudiantes(estudiantes, tamanoVectorEstudiantes);                            
                        }
                    }
                }
                break;
            case 4:
                if(tamanoVectorEstudiantes == 0){
                        printf("\nNo hay estudiantes para eliminar!\n");
                        break;
                    }else{
                        //Validamos la existencia del estudiante en el vector
                        printf("\nIngrese el ID del estudiante a eliminar: ");
                        scanf("%d", &validarId);
                        for(int contador = 0; contador < tamanoVectorEstudiantes; contador++){
                            if(validarId != estudiantes[contador].id){
                                printf("\nEl ID ingresado no corresponde a ningun estudiante!\n");
                                break;
                            }else if(validarId == estudiantes[contador].id){
                                printf("\nEstudiante encontrado!\n");
                                eliminarEstudiante(estudiantes, &tamanoVectorEstudiantes, validarId);
                                guardararchivoEstudiantes(estudiantes, tamanoVectorEstudiantes); //Guardamos el estudiante después de crearlo
                                break;
                            }
                        }
                    }
                break;
            case 0:
                printf("\nHas salido del menu de estudiante\n");
                break;
            default:
                break;
        }
    }
}

void menuInteraccionEstudiante(){
    printf("Está vacío");
}

#endif