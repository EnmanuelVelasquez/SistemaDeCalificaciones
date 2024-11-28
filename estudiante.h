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
} Estudiante;

// Definición de las funciones
int buscarEstudiantePorId(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante);
Estudiante crearEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes);
Estudiante crearAsignaturasEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante);
void menuActualizarCalificaciones();
Estudiante actualizarCalificacionesEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante);
void mostrarEstudiante(Estudiante estudiante);
void menuActualizarEstudiante();
Estudiante actualizarEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante);
void guardarEstudiantes(Estudiante *estudiantes, int tamanoVectorEstudiantes);
void leerArchivosEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes);
void eliminarEstudiante(Estudiante *estudiantes, int *tamanoVectorEstudiantes, int idEstudiante);
void menuPrincipalEstudiante();
void menuInteraccionDocente();

//Buscar estudiante por id
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
    printf("\nEstudiante creado exitosamente.\n");
    return estudiante;
}

Estudiante asignarAsignaturasEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante){
    Asignatura asignaturas[MAXASIGNATURAS];
    int tamanoVectorAsignaturas;

    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas);

    int indiceEstudiante = buscarEstudiantePorId(estudiantes, tamanoVectorEstudiantes, idEstudiante);
    int numeroAsignaturas;
        if (indiceEstudiante == -1){
            printf("Estudiante no encontrado.\n");
            return estudiantes[0]; //Lo retorna vacío
        }
        printf("\nIngrese cuantas asignaturas desea asignar: ");
        scanf("%d", &numeroAsignaturas);
        for (int contador = 0; contador < numeroAsignaturas; contador++) {
            int idAsigntura;
            for(int contador = 0; contador < tamanoVectorAsignaturas; contador++){
                printf("\nAsignatura %d:\n", contador + 1);
                mostrarAsignatura(asignaturas[contador]);
            }
            printf("Ingrese el id de la asignatura a asignar: ");
            scanf("%d", &idAsigntura);
            int indiceAsignatura = buscarAsignaturaPorId(asignaturas, tamanoVectorAsignaturas, idAsigntura);
            estudiantes[indiceEstudiante].asignaturas[contador] = asignaturas[indiceAsignatura];
        }
    return estudiantes[indiceEstudiante];
}

// Mostrar los datos de un estudiante
void mostrarEstudiante(Estudiante estudiante){
    Asignatura asignaturas[MAXASIGNATURAS];
    int tamanoVectorAsignaturas;
    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas);

    printf("\nID: %d\n", estudiante.id);
    printf("Nombre: %s\n", estudiante.nombre);
    printf("Apellido: %s\n", estudiante.apellido);

    printf("Asignaturas:\n");
    for (int contador = 0; contador < tamanoVectorAsignaturas; contador++) {
        printf("Asignatura %d: %s\n", contador + 1, estudiante.asignaturas[contador].nombre);
    }
}

//Muestra menu para actualizar calificaciones de un estudiante
void menuActualizarCalificaciones(){
    printf("\nMenu para actualizar calificaciones de un estudiante\n");
    printf("1. Cambiar calificaciones\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

//Menu para actualizar calificaciones de un estudiante
Estudiante actualizarCalificacionesEstudiante(Estudiante *estudiantes, int tamanoVectorEstudiantes, int idEstudiante){
    Asignatura asignaturas[MAXASIGNATURAS];
    int tamanoVectorAsignaturas;
    int opcion = 1;
    int posicionCalificacion;
    float valorcapturado;

    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas);

    int indiceEstudiante = buscarEstudiantePorId(estudiantes, tamanoVectorEstudiantes, idEstudiante);
    int idAsigntura;

    if (indiceEstudiante == -1){
        printf("Estudiante no encontrado.\n");
        return estudiantes[0]; //Lo retorna vacío
    }
    
    for(int contador = 0; contador < tamanoVectorAsignaturas; contador++){
        printf("\nAsignatura %d:\n", contador + 1);
        mostrarAsignatura(asignaturas[contador]);
    }
    printf("\nIngrese el id de la asignatura: ");
    scanf("%d", &idAsigntura);
    int indiceAsignatura = buscarAsignaturaPorId(asignaturas, tamanoVectorAsignaturas, idAsigntura);

    while (opcion != 0){
    menuActualizarCalificaciones();
    scanf("%d", &opcion);
        if (opcion == 1){
            printf("\nCalificaciones: ");
            for(int contador = 0; contador < MAXCALIFICACIONES; contador++){
                printf("%.1f ", estudiantes[indiceEstudiante].asignaturas[indiceAsignatura].calificaciones[contador]);
            }
            printf("\n");
            printf("\nIngrese la posicion de la calificacion: ");
            scanf("%d", &posicionCalificacion);
            if (posicionCalificacion >= MAXCALIFICACIONES){
                printf("\nPosicion invalida.\n");
                continue;
            }

            printf("\nIngrese el valor de la calificacion: ");
            scanf("%f", &valorcapturado);

            estudiantes[indiceEstudiante].asignaturas[indiceAsignatura].calificaciones[posicionCalificacion] = valorcapturado;
            printf("\nCalificaciones: ");
            for(int contador = 0; contador < MAXCALIFICACIONES; contador++){
                printf("%.1f ", estudiantes[indiceEstudiante].asignaturas[indiceAsignatura].calificaciones[contador]);
            }
            printf("\nCalificacion actualizada exitosamente.\n");
        }
    }
    return estudiantes[indiceEstudiante];
}

// Muestra menu para actualizar datos de un estudiante
void menuActualizarEstudiante(){
    printf("\nMenu para actualizar datos de un estudiante\n");
    printf("1. Cambiar ID\n");
    printf("2. Cambiar nombre\n");
    printf("3. Cambiar apellido\n");
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
        printf("\n1. Crear estudiante\n");
        printf("2. Mostrar estudiantes\n");
        printf("3. Modificar estudiante\n");
        printf("4. Eliminar estudiante\n");
        printf("5. Asignar asignaturas\n");
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
                        printf("\nEstudiante %d:\n", contador + 1);
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
                for (int contador = 0; contador < tamanoVectorEstudiantes; contador++) {
                        printf("\nEstudiante %d:\n", contador + 1);
                        mostrarEstudiante(estudiantes[contador]);
                    }
                printf("\nIngrese el ID del estudiante para asignar asignaturas: ");
                int idEstudiante;
                scanf("%d", &idEstudiante);
                asignarAsignaturasEstudiante(estudiantes, tamanoVectorEstudiantes, idEstudiante);
                guardarEstudiantes(estudiantes, tamanoVectorEstudiantes);
                break;
            case 6:
                for (int contador = 0; contador < tamanoVectorEstudiantes; contador++) {
                        printf("\nEstudiante %d:\n", contador + 1);
                        mostrarEstudiante(estudiantes[contador]);
                    }
                printf("\nIngrese el ID del estudiante a actualizar calificaciones: ");
                int idEstudianteCalificaciones;
                scanf("%d", &idEstudianteCalificaciones);
                actualizarCalificacionesEstudiante(estudiantes, tamanoVectorEstudiantes, idEstudianteCalificaciones);
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

void mostrarCalificacionesEstudiante(){
    Estudiante estudiantes[MAXESTUDIANTES];
    Asignatura asignaturas[MAXASIGNATURAS];
    int tamanoVectorEstudiantes;
    int tamanoVectorAsignaturas;
    int indiceAsignatura;
    int indiceEstudiante;
    leerArchvivosAsignaturas(asignaturas, &tamanoVectorAsignaturas);
    leerArchivosEstudiante(estudiantes, &tamanoVectorEstudiantes);

    for (int contador = 0; contador < tamanoVectorEstudiantes; contador++) {
        printf("\nEstudiante %d:\n", contador + 1);
        mostrarEstudiante(estudiantes[contador]);
    }
    printf("\nIngrese el ID del estudiante a mostrar calificaciones: ");
    scanf("%d", &indiceEstudiante);
    mostrarEstudiante(estudiantes[indiceEstudiante]);
    printf("\nCalificaciones: ");
    for(int contador = 0; contador < MAXCALIFICACIONES; contador++){
        printf("%.1f ", estudiantes[indiceEstudiante].asignaturas[indiceAsignatura].calificaciones[contador]);
    }
    printf("\n");
}

void menuInteraccionEstudiante(){
    Estudiante estudiantes[MAXESTUDIANTES];
    int tamanoVectorEstudiantes;
    leerArchivosEstudiante(estudiantes, &tamanoVectorEstudiantes);

    int opcion = 1;

    while(opcion != 0){
        printf("\n--- Menu de Estudiante ---\n");
        printf("\n1. Mostrar calificaciones\n");
        printf("2. Generar boletin\n");
        printf("0. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                mostrarCalificacionesEstudiante();
                break;
            case 2:
                menuActualizarCalificaciones();
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

#endif // ESTUDIANTE_H
