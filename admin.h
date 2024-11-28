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
int buscarAdminPorId(Admin *admins, int tamanoVectorAdmins, int idAdmin);
Admin crearAdmin();
void mostrarAdmin();
Admin actualizarAdmin(Admin *admins, int tamanoVectorAdmins, int idAdmin); 
void guardarAdmins(Admin *admins, int tamanoVectorAdmin);
void leerArchvivosAdmin(Admin *admins, int *tamanoVectorAdminAdmins);
void eliminarAdmin();
void menuPrincipalAdmin();
void menuGestionCruds();
void menuGestionAdmin();
void manejarAdmin();
void cerrarSesion();

//Inicialización de las funciones:
int buscarAdminPorId(Admin *admins, int tamanoVectorAdmins, int idAdmin){//Función recursiva
    if (tamanoVectorAdmins == 0) {
        return -1; // No encontrado
    }
    if (admins[tamanoVectorAdmins - 1].id == idAdmin) {
        return tamanoVectorAdmins - 1; // Retorna el índice encontrado
    }
    return buscarAdminPorId(admins, tamanoVectorAdmins - 1, idAdmin);
}

Admin crearAdmin(Admin *admins, int tamanoVectorAdmins){
    Admin admin;
    printf("Ingrese ID del administrador: ");
    scanf("%d", &admin.id);
    if(buscarAdminPorId(admins, tamanoVectorAdmins, admin.id) != -1){
        printf("El ID ya está en uso. Intente nuevamente.\n");
        return crearAdmin(admins, tamanoVectorAdmins);
    }
    printf("Ingrese nombre del administrador: ");
    scanf("%49s", admin.nombre);
    printf("Ingrese contrasena del administrador: ");
    scanf("%49s", admin.contrasena);
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

Admin actualizarAdmin(Admin *admins, int tamanoVectorAdmins, int idAdmin){
    int indice = buscarAdminPorId(admins, tamanoVectorAdmins, idAdmin);
    if (indice == -1) {
        printf("Administrador no encontrado.\n");
        return admins[indice];
    }
    int opcion = 1;
    while (opcion != 0) {
        menuActualizarAdmin();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Ingrese el nuevo ID del administrador: ");
                scanf("%d", &admins[indice].id);
                break;
            case 2:
                printf("Ingrese el nuevo nombre del administrador: ");
                scanf("%49s", admins[indice].nombre);
                break;
            case 3:
                printf("Ingrese la nueva contraseña del administrador: ");
                scanf("%49s", admins[indice].contrasena);
                break;
            case 0:
                printf("Saliendo del menu de actualización.\n");
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
    return admins[indice];
}

void guardararchivoAdmin(Admin *admins, int tamanoVectorAdmins){
    FILE *archivoAdmins = ABRIR_ARCHIVO("data/admins.bat", "wb"); //Modifica todo el archivoEstudiantes en binario, cargando y actualizando todo el vector
    if(archivoAdmins == NULL){
        FILE_ERROR("Error al crear el archivo de estudiantes");// Retorna un código de error
    }
    fwrite(admins, sizeof(Admin), tamanoVectorAdmins, archivoAdmins);
    CERRAR_ARCHIVO(archivoAdmins);
}

void leerArchivosAdmin(Admin *admins, int *tamanoVectorAdmins){
    // Lee el archivo admins en binario
    FILE *archivoAdmins = ABRIR_ARCHIVO("data/admins.bat", "Rb"); 
    // Evaluamos si no está creado
    if (archivoAdmins == NULL) {
        // En caso que no esté creado, lo creamos de tipo binario
        archivoAdmins = ABRIR_ARCHIVO("data/admins.bat", "wb");  

        // Validamos nuevamente que esté creado
        if (archivoAdmins == NULL) {
            FILE_ERROR("Error al crear el archivo de admins"); // La macro finaliza el programa y muestra el mensaje
        }

        // Inicializa el tamaño del vector de admins en 0 para indicar que no hay nadie
        *tamanoVectorAdmins = 0; 
        CERRAR_ARCHIVO(archivoAdmins); // Cierra el archivo creado
        return;
    }
    // Inicializa el contador
    *tamanoVectorAdmins = 0; 
    // Lee los datos de los admins hasta el límite MAXADMINS o hasta que no haya más datos
    while (*tamanoVectorAdmins < MAXADMINS && fread(&admins[*tamanoVectorAdmins], sizeof(Admin), 1, archivoAdmins)) {
        (*tamanoVectorAdmins)++;
    }
    CERRAR_ARCHIVO(archivoAdmins); // Cierra el archivo al final
}

void eliminarAdmin(Admin *admins, int *tamanoVectorAdmins, int idAdmin){
    int indice = buscarAdminPorId(admins, *tamanoVectorAdmins, idAdmin);
    int confirmacion;
    if (indice == -1) {
        printf("Administrador con ID %d no encontrado.\n", idAdmin);
        return;
    }
    printf("\nEsta seguro de que desea eliminar al adiministrador con ID %d?\n", idAdmin);
    printf("\n1. Si");
    printf("\n0. No");
    printf("\nSeleccione una opcion: ");
    scanf("%d", &confirmacion);
    if (confirmacion != 1) {
        printf("\nEliminacion cancelada.\n");
        return;
    }
    for (int contador = indice; contador < *tamanoVectorAdmins - 1; contador++) {
        admins[contador] = admins[contador + 1];
    }
    (*tamanoVectorAdmins)--;
    printf("Administrador con ID %d eliminado exitosamente.\n", idAdmin);
}

void menuPrincipalAdmin() {
    Admin admins[MAXADMINS];
    int tamanoVectorAdmins;
    int opcion = 1;

    leerArchivosAdmin(admins, &tamanoVectorAdmins);
    
    while (opcion != 0) {
        printf("\nMenu principal administradores\n");
        printf("1. Crear administrador\n");
        printf("2. Mostrar administradores\n");
        printf("3. Modificar administrador\n");
        printf("4. Eliminar administrador\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                if (tamanoVectorAdmins < MAXADMINS) {
                    admins[tamanoVectorAdmins] = crearAdmin(admins, tamanoVectorAdmins);
                    tamanoVectorAdmins++;
                    guardararchivoAdmin(admins, tamanoVectorAdmins);
                } else {
                    printf("No se pueden agregar mas administradores.\n");
                }
                break;
            case 2:
                if (tamanoVectorAdmins == 0) {
                    printf("No hay administradores registrados.\n");
                } else {
                    for (int contador = 0; contador < tamanoVectorAdmins; contador++){
                        printf("\nAdmin %d:\n", contador + 1);
                        mostrarAdmin(admins[contador]);
                    }
                }
                break;
            case 3:
                printf("Ingrese el ID del administrador a modificar: ");
                int idModificar;
                scanf("%d", &idModificar);
                actualizarAdmin(admins, tamanoVectorAdmins, idModificar);
                guardararchivoAdmin(admins, tamanoVectorAdmins);
                break;
            case 4:
                printf("Ingrese el ID del administrador a eliminar: ");
                int idEliminar;
                scanf("%d", &idEliminar);
                eliminarAdmin(admins, &tamanoVectorAdmins, idEliminar);
                guardararchivoAdmin(admins, tamanoVectorAdmins);
                break;
            case 0:
                printf("Saliendo del menu de administradores.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    }
}

void menuGestionCruds(){
    int opcion = 1;
    while(opcion != 0){
        printf("\nMenu Administrador\n");
        printf("\n1. Gestionar administrador\n");
        printf("2. Gestionar docente\n");
        printf("3. Gestionar estudiante\n");
        printf("4. Gestionar asignatura\n");
        printf("0. Salir\n");
        printf("\nSeleccione una opcion: ");
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
                printf("opcion no valida\n");
        }    
    }
}

#endif
