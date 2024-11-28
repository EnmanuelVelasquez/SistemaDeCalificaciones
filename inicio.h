//Definimos la macro INICIO_H:
#ifndef INICIO_H
#define INICIO_H
//Incluímos las librerías y otros archivos.h que vamos a utilizar:
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "admin.h"
#include "docente.h"
#include "estudiante.h"
#include "utilidades.h"

typedef enum {
    Salir,
    MenuPrincipalAdmin,
    MenuPrincipalDocente,
    MenuPrincipalEstudiante 
} Menu;

// Implementación del menú principal
Menu menuPrincipal() {
    Menu opcion;

    printf("\n-----Bienvenido a CalifiC-----\n");
    printf("\nTipo de usuario: \n");
    printf("1. Administrador\n");
    printf("2. Docente\n");
    printf("3. Estudiante\n");
    printf("0. Salir\n");
    printf("\nSelecciona una opcion: ");
    scanf("%d", (int*)&opcion); // Lee la opción y la convierte a tipo Menu

    switch (opcion) {
        case MenuPrincipalAdmin:
            menuGestionCruds();
            break;
        case MenuPrincipalDocente:
            menuInteraccionDocente();
            break;
        case MenuPrincipalEstudiante:
            menuInteraccionEstudiante();
            break;
        case Salir:
            printf("Saliendo del menú principal.\n");
            Sleep(2000);
            break;
        default:
            printf("Opcion no valida.\n");
            menuPrincipal();
    }

    return opcion; // Retorna la opción seleccionada
}

#endif // INICIO_H

