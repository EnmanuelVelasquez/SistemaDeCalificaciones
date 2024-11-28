#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"
#include "admin.h"
#include "asignatura.h"

// Estructura del Estudiante
typedef struct {
    int id;               // ID del estudiante
    char nombre[50];      // Nombre del estudiante
    char apellido[50];    // Apellido del estudiante
    Asignatura asignaturas[MAXASIGNATURAS]; // Vector de asignaturas
    float calificaciones[MAXCALIFICACIONES];
} Estudiante;

// Definición de las funciones
int buscarEstudiantePorId(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante);
Estudiante crearEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes);
void mostrarEstudiante(Estudiante estudiante);
void menuActualizarEstudiante();
Estudiante actualizarEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante);
void guardarEstudiantes(Estudiante *estudiantes, int tamanoVectorEstudiantes);
void leerArchivosEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes);
void eliminarEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes, int idEstudiante);
void menuPrincipalEstudiante();
void menuInteraccionDocente();

int buscarEstudiantePorId(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante) {
    for (int contador = 0; contador < tamanoVectorEstudiantes; contador++) {
        if (estudiantes[contador].id == idEstudiante) {
            return contador; // Retorna el índice del estudiante encontrado
        }
    }
    return -1; // Estudiante no encontrado
}

// Crear un nuevo estudiante
Estudiante crearEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes) {
    Estudiante estudiante;
    printf("Ingrese ID del estudiante: ");
    scanf("%d", &estudiante.id);

    // Verificar si el ID ya está en uso
    if (buscarEstudiantePorId(estudiantes, tamanoVectorEstudiantes, estudiante.id) != -1) {
        printf("El ID ya está en uso. Intente nuevamente.\n");
        return crearEstudiante(estudiantes, tamanoVectorEstudiantes);
    }
    // Ingresar los datos del estudiante
    printf("Ingrese nombre del estudiante sin espacios: ");
    scanf("%49s", estudiante.nombre);
    printf("Ingrese apellido del estudiante sin espacios: ");
    scanf("%49s", estudiante.apellido);
    for(int contador = 0; contador < MAXCALIFICACIONES; contador++){
        estudiante.calificaciones[contador] = 0;    
        }
    printf("\nEstudiante creado exitosamente.\n");
    return estudiante;
}

Estudiante crearAsignaturasEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante){
    Estudiante estudiante;
    int indice = buscarEstudiantePorId(estudiantes, tamanoVectorEstudiantes, idEstudiante);
    if (indice == -1) {
        printf("Estudiante no encontrado.\n");
        return estudiantes[indice];
    }
    estudiante = estudiantes[indice];
    return estudiante;

}

// case 3:
//             printf("\nIngrese la posición de la calificacion a modificar: ");
//             scanf("%d", &posicionCalificacion);
//             if (posicionCalificacion >= 0 && posicionCalificacion < MAXCALIFICACIONES) {
//                 printf("Ingrese la nueva calificación: ");
//                 scanf("%f", &asignaturas[posicionModificarAsignatura].calificaciones[posicionCalificacion]);
//                 printf("Calificación actualizada correctamente.\n");
//             } else {
//                 printf("Posición de calificación no válida.\n");
//             }
//             break;

// Mostrar los datos de un estudiante
void mostrarEstudiante(Estudiante estudiante) {
    printf("\nID: %d\n", estudiante.id);
    printf("Nombre: %s\n", estudiante.nombre);
    printf("Apellido: %s\n", estudiante.apellido);
}

// Menú para actualizar datos de un estudiante
void menuActualizarEstudiante(){
    printf("\nMenu para actualizar datos de un estudiante\n");
    printf("1. Cambiar ID\n");
    printf("2. Cambiar nombre\n");
    printf("3. Cambiar apellido\n");
    printf("4. Modificar asignaturas\n");
    printf("5. Modificar calificaciones\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

// Función para actualizar los datos de un estudiante
Estudiante actualizarEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante) {
    int indice = buscarEstudiantePorId(estudiantes, tamanoVectorEstudiantes, idEstudiante);
    if (indice == -1){
        printf("Estudiante no encontrado.\n");
        return estudiantes[0]; //Lo retorna vacío
    }
    int opcion = 1;
    while (opcion != 0) {
        menuActualizarEstudiante();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Ingrese el nuevo ID del estudiante: ");
                scanf("%d", &estudiantes[indice].id);
                break;
            case 2:
                printf("Ingrese el nuevo nombre del estudiante sin espacios: ");
                scanf("%49s", estudiantes[indice].nombre);
                break;
            case 3:
                printf("Ingrese el nuevo apellido del estudiante sin espacios: ");
                scanf("%49s", estudiantes[indice].apellido);
                break;
            case 4:
                // printf("Ingrese las nuevas asignaturas del estudiante:\n");
                // for (int contadorAsignatura = 0; contadorAsignatura < MAXASIGNATURAS; contadorAsignatura++) {
                //     printf("Asignatura %d: ", contadorAsignatura + 1);
                //     estudiantes[contador].asignaturas[contadorAsignatura] = crearAsignatura();
                // }
                break;
            case 0:
                printf("Saliendo del menu de actualizacion.\n");
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
    return estudiantes[indice];
}

// Guardar los estudiantes en un archivo binario
void guardarEstudiantes(Estudiante *estudiantes, int tamanoVectorEstudiantes) {
    FILE *archivoEstudiantes = fopen("data/estudiantes.bat", "wb");
    if (archivoEstudiantes == NULL) {
        printf("Error al crear el archivo de estudiantes.\n");
        return;
    }
    fwrite(estudiantes, sizeof(Estudiante), tamanoVectorEstudiantes, archivoEstudiantes);
    fclose(archivoEstudiantes);
}

// Leer los estudiantes desde un archivo binario
void leerArchivosEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes){
    // Lee el archivo estudiantes en binario
    FILE *archivoEstudiantes = fopen("data/estudiantes.bat", "rb");
    // Evaluamos si el archivo no existe
    if (archivoEstudiantes == NULL) {
        // Si no existe, lo creamos de tipo binario
        archivoEstudiantes = fopen("data/estudiantes.bat", "wb"); 
        // Validamos nuevamente que se haya creado el archivo
        if (archivoEstudiantes == NULL) {
            FILE_ERROR("Error al crear el archivo de estudiantes"); // La macro finaliza el programa y muestra el mensaje
        }
        // Inicializa el tamaño del vector de estudiantes en 0 para indicar que no hay estudiantes registrados
        *tamanoVectorEstudiantes = 0; 
        fclose(archivoEstudiantes); // Cierra el archivo creado
        return;
    }
    // Inicializa el contador
    *tamanoVectorEstudiantes = 0;
    // Lee los datos de los estudiantes hasta el límite MAXESTUDIANTES o hasta que no haya más datos
    while (*tamanoVectorEstudiantes < MAXESTUDIANTES && fread(&estudiantes[*tamanoVectorEstudiantes], sizeof(Estudiante), 1, archivoEstudiantes)) {
        (*tamanoVectorEstudiantes)++;
    }
    fclose(archivoEstudiantes); // Cierra el archivo después de leer
}

// Eliminar un estudiante
void eliminarEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes, int idEstudiante) {
    int contador = buscarEstudiantePorId(estudiantes, *tamanoVectorEstudiantes, idEstudiante);
    int confirmacion;   
    if (contador == -1) {
        printf("Estudiante con ID %d no encontrado.\n", idEstudiante);
        return;
    }
    printf("\nEsta seguro de que desea eliminar al estudiante con ID %d?\n", idEstudiante);
    printf("\n1. Si");
    printf("\n0. No");
    printf("\nSeleccione una opcion: ");
    scanf("%d", &confirmacion);
    if (confirmacion != 1) {
        printf("\nEliminacion cancelada.\n");
        return;
    }
    for (int contador = contador; contador < *tamanoVectorEstudiantes - 1; contador++) {
        estudiantes[contador] = estudiantes[contador + 1];
    }
    (*tamanoVectorEstudiantes)--;
    printf("Estudiante con ID %d eliminado exitosamente.\n", idEstudiante);
}

// Menú principal de los estudiantes
void menuPrincipalEstudiante() {
    Estudiante estudiantes[MAXESTUDIANTES];
    int tamanoVectorEstudiantes;
    int opcion = 1;

    leerArchivosEstudiante(estudiantes, &tamanoVectorEstudiantes);

    while (opcion != 0) {
        printf("\nMenu principal estudiantes\n");
        printf("1. Crear estudiante\n");
        printf("2. Mostrar estudiantes\n");
        printf("3. Modificar estudiante\n");
        printf("4. Eliminar estudiante\n");
        printf("5. Crear asignaturas\n");
        printf("6. Modificar calificaciones\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                if (tamanoVectorEstudiantes < MAXESTUDIANTES) {
                    estudiantes[tamanoVectorEstudiantes] = crearEstudiante(estudiantes, tamanoVectorEstudiantes);
                    tamanoVectorEstudiantes++;
                    guardarEstudiantes(estudiantes, tamanoVectorEstudiantes);
                } else {
                    printf("No se pueden agregar mas estudiantes.\n");
                }
                break;
            case 2:
                if (tamanoVectorEstudiantes == 0) {
                    printf("No hay estudiantes registrados.\n");
                } else {
                    for (int contador = 0; contador < tamanoVectorEstudiantes; contador++) {
                        printf("\nEstudiante %d:\n", contador);
                        mostrarEstudiante(estudiantes[contador]);
                    }
                }
                break;
            case 3:
                printf("Ingrese el ID del estudiante a modificar: ");
                int idModificar;
                scanf("%d", &idModificar);
                actualizarEstudiante(estudiantes, tamanoVectorEstudiantes, idModificar);
                guardarEstudiantes(estudiantes, tamanoVectorEstudiantes);
                break;
            case 4:
                printf("Ingrese el ID del estudiante a eliminar: ");
                int idEliminar;
                scanf("%d", &idEliminar);
                eliminarEstudiante(estudiantes, &tamanoVectorEstudiantes, idEliminar);
                guardarEstudiantes(estudiantes, tamanoVectorEstudiantes);
                break;
            case 5:
                printf("\nIngrese el ID del estudiante a crear asignaturas: ");
                int idEstudiante;
                scanf("%d", &idEstudiante);
                crearAsignaturasEstudiante(estudiantes, tamanoVectorEstudiantes, idEstudiante);
                guardarEstudiantes(estudiantes, tamanoVectorEstudiantes);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("\nOpcion no valida.\n");
                break;
        }
    }
}

#endif // ESTUDIANTE_H
