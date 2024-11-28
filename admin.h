//Definimos la macro ADMIN_H:
#ifndef ADMIN_H
#define ADMIN_H
//Incluímos las librerías y otros archivos.h que vamos a utilizar:
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "estudiante.h"
#include "docente.h"
#include "asignatura.h"

// Creación de la estructura admin:
typedef struct {
    int id;             // ID del usuario
    char nombre[50];    // Nombre del usuario
    char contrasena[50]; // contrasena del usuario
} Admin;

// Definición de las funciones de admin:
Admin crearAdmin();
void mostrarAdmin();
Admin actualizarAdmin(Admin *admins, int tamanoVectorAdmin); 
void guardarAdmins(Admin *admins, int tamanoVectorAdmin);
void leerArchvivosAdmin(Admin *admins, int *tamanoVectorAdminAdmins);
void eliminarAdmin();
void menuPrincipalAdmin();
void menuGestionCruds();

void menuGestionAdmin();
void manejarAdmin();
void cerrarSesion();

//Inicialización de las funciones:
Admin crearAdmin(){
    Admin admin;
    printf("Ingrese ID del administrador: ");
    scanf("%d", &admin.id);
    printf("Ingrese nombre del administrador: ");
    scanf("%s", admin.nombre);
    printf("Ingrese contrasena del administrador: ");
    scanf("%s", admin.contrasena);
    printf("\nAdministrador creado exitosamente.\n");
    return admin;
}

void mostrarAdmin(Admin admin){
    printf("\nID: %d\n", admin.id);
    printf("Nombre: %s\n", admin.nombre);
    printf("contrasena: %s\n", admin.contrasena);
}

void menuActualizarAdmin(){
    printf("\nMenu para actualizar datos de un administrador\n");
    printf("1. Cambiar ID\n");
    printf("2. Cambiar nombre\n");
    printf("3. Cambiar apellido\n");
    printf("4. Cambiar contrasena\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

Admin actualizarAdmin(Admin *admins, int tamanoVectorAdmin){
    //Se recibe una posición del vector estudiantes para seleccionar qué se desea modificar:
    int opcion = 1;
    while (opcion != 0) {
        menuActualizarAdmin();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Ingrese el nuevo ID del administrador: ");
                scanf("%d", &admins[tamanoVectorAdmin].id);
                printf("ID actualizado exitosamente.\n");
                break;  
            case 2:
                printf("Ingrese el nuevo nombre del administrador: ");
                scanf("%s", admins[tamanoVectorAdmin].nombre);
                printf("Nombre actualizado exitosamente.\n");
                break;
            case 3:
                printf("Ingrese la nueva contrasena del administrador: ");
                scanf("%s", admins[tamanoVectorAdmin].contrasena);
                printf("contrasena actualizada exitosamente.\n");
                break;
            case 0:
                printf("\nHas salido del menu de actualización\n");
                break;
            default:
                printf("\nOpcion no válida\n");
                break;
        }
    }
    //Se retorna el estudiante modificado
    return admins[tamanoVectorAdmin];
}

void guardararchivoAdmin(Admin *admins, int tamanoVectorAdmins){
    FILE *archivoAdmins = fopen("data/admins.bat", "wb"); //Modifica todo el archivoEstudiantes en binario, cargando y actualizando todo el vector
    if(archivoAdmins == NULL){
        FILE_ERROR("Error al crear el archivo de estudiantes");// Retorna un código de error
    }
    fwrite(admins, sizeof(Estudiante), tamanoVectorAdmins, archivoAdmins);
    fclose(archivoAdmins);
}

void leerArchvivosAdmin(Admin *admins, int *tamanoVectorAdmins){
    // Lee el archivo estudiantes en binario
    FILE *archivoAdmins = fopen("data/admins.bat", "rb");
    //Evaluamos si no está creado 
    if (archivoAdmins == NULL){
         // En caso que no esté creado, lo creamos de tipo binario
         archivoAdmins = fopen("data/admins.bat", "wb"); 
         // Validamos nuevamente que esté creado
        if (archivoAdmins == NULL){
            FILE_ERROR("Error al crear el archivo de estudiantes"); //La macro finaliza el programa y muestra el mensaje
        }
        // Inicializa el tamaño del vector de estudiantes en 0 para indicar que no hay nadie
    *tamanoVectorAdmins = 0; 
    fclose(archivoAdmins); // Cierra el archivo creado
    return;
    }
    // Inicializa el contador
    *tamanoVectorAdmins = 0; 
    while (*tamanoVectorAdmins < MAXESTUDIANTES && fread(&admins[*tamanoVectorAdmins], sizeof(Estudiante), 1, archivoAdmins)) {
        (*tamanoVectorAdmins)++;
    }
}

void eliminarAdmin(Admin *admins, int *tamanoVectorAdmins, int idAdmin){
    //Suponemos que el estudiante no existe, inializamos en -1:
    int poscionEstudianteEliminar = -1;
    for (int contador = 0; contador < *tamanoVectorAdmins; contador++) {
        if (admins[contador].id == idAdmin){ //Buscamos el id del estudiante en el vector
            poscionEstudianteEliminar = contador; //Asignamos la posición a la variable que vamos a usar
            break;
        }
    }
    if (poscionEstudianteEliminar != -1) {
        for (int contador = poscionEstudianteEliminar; contador < *tamanoVectorAdmins - 1; contador++){
            //Reescribimos todo el vector desde el punto de referencia del estudiante a eliminar
            admins[contador] = admins[contador + 1];
            //Los estudiantes modificados fueron movidos una posición a la izquierda
        }
        (*tamanoVectorAdmins)--; //Reajustamos el tamaño del vector
        printf("Estudiante con ID %d eliminado exitosamente.\n", idAdmin);
    } else {
        printf("Estudiante con ID %d no encontrado.\n", idAdmin);
    }
}

void menuPrincipalAdmin(){
    Admin admins[MAXADMINS];
    int tamanoVectorAdmins = 0;
    int opcion = 1;
    int validarId;

    leerArchvivosAdmin(admins, &tamanoVectorAdmins);//Si hay datos en el vector, los leemos
    
    while(opcion != 0){
        printf("\nMenu principal administradores\n");
        printf("1. Crear administrador\n");
        printf("2. Mostrar administrador\n");
        printf("3. Modificar administrador\n");
        printf("4. Eliminar administrador\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion){
            case 1:
                // Validamos que halla espacio para crear más estudiantes
                if (tamanoVectorAdmins < MAXESTUDIANTES) {
                    Admin admin = crearAdmin();
                    admins[tamanoVectorAdmins] = admin;
                    tamanoVectorAdmins++;
                    guardararchivoAdmin(admins, tamanoVectorAdmins); //Guardamos el estudiante después de crearlo
                } else {
                    printf("El máximo número de administradores ha sido alcanzado.\n");
                }
                break;
            case 2:
                //Se imprimen todos los estudiantes guardados
                if(tamanoVectorAdmins == 0){
                    printf("\nNo hay administradores para mostar!\n");
                    break;
                }else{
                    for(int contador = 0; contador < tamanoVectorAdmins; contador++){
                    printf("\nEstudiante %d:\n", contador);
                    mostrarAdmin(admins[contador]);
                    }
                }
                break;
            case 3:
                if(tamanoVectorAdmins == 0){
                    printf("\nNo hay administradores para modificar!\n");
                    break;
                }else{
                    //Validamos la existencia del estudiante en el vector
                    printf("\nIngrese el ID del administrador a modificar: ");
                    scanf("%d", &validarId);
                    for(int contador = 0; contador < tamanoVectorAdmins; contador++){
                        if(validarId != admins[contador].id){
                            printf("\nEl ID ingresado no corresponde a ningun administrador!\n");
                            break;
                        }else if(validarId == admins[contador].id){
                            printf("\nEstudiante encontrado!\n");
                            admins[contador] = actualizarAdmin(admins, contador);
                            guardararchivoAdmin(admins, tamanoVectorAdmins);
                        }
                    }
                }
                break;
            case 4:
            if(tamanoVectorAdmins == 0){
                    printf("\nNo hay administradores para eliminar!\n");
                    break;
                }else{
                    //Validamos la existencia del estudiante en el vector
                    printf("\nIngrese el ID del administrador a eliminar: ");
                    scanf("%d", &validarId);
                    for(int contador = 0; contador < tamanoVectorAdmins; contador++){
                        if(validarId != admins[contador].id){
                            printf("\nEl ID ingresado no corresponde a ningun administrador!\n");
                            break;
                        }else if(validarId == admins[contador].id){
                            printf("\nAdministrador encontrado!\n");
                            eliminarAdmin(admins, &tamanoVectorAdmins, validarId);
                            guardararchivoAdmin(admins, tamanoVectorAdmins); //Guardamos el estudiante después de crearlo
                            break;
                        }
                    }
                }
                break;
            case 0:
                printf("\nHas salido del menu de administrador\n");
                break;
            default:
                break;
        }
    }
}

void menuGestionCruds(){
    int opcion = 1;
    while(opcion != 0){
        printf("\nMenú Administrador\n");
        printf("1. Gestionar administrador\n");
        printf("2. Gestionar docente\n");
        printf("3. Gestionar estudiante\n");
        printf("4. Gestionar asignatura\n");
        printf("5. Gestionar calificación\n");
        printf("6. Volver al menú principal\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                menuPrincipalAdmin();
                break;
            case 2:
                menuPrincipalDocente();
                break;
            case 3:
                menuPrincipalEstudiante();
                break;
            case 4:
                menuPrincipalAsignatura();
                break;
            case 0:
                salir();
                break;
            default:
                printf("opcion no válida\n");
        }    
    }
}

#endif
