#ifndef LOGIN_H
#define LOGIN_H

void saludoBienvenida();
int esAdmin(char *usuario, char *contrasena);
int login(char *usuario, char *contrasena);
void manejarLogin();


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <windows.h>
#include <stdlib.h>
#include "admin.h"



void saludoBienvenida(){
    printf("\n-----Bienvenido a CalifiC-----\n");
}

void manejarLogin() { 
    char usuario[50]; 
    char contrasena[50]; 
    int tipoUsuario; 

    printf("Ingrese su usuario:\n"); 
    scanf("%s", usuario); 
    printf("Ingrese su contraseña:\n"); 
    scanf("%s", contrasena); 

    tipoUsuario = login(usuario, contrasena);

    if(tipoUsuario == 1){ 
        printf("Bienvenido Administrador\n"); 
        menuPrincipalAdmin(); 
        }else{ 
        printf("Usuario o contraseña incorrectos\n"); 
    }
}

// Función para verificar si un usuario es administrador
int esAdmin(char *usuario, char *contrasena){ 
    if (usuario == NULL || contrasena == NULL){ 
        printf("Usuario o contraseña no pueden ser nulos\n"); 
        return 0; 
    }
    
    FILE *punteroArchivo = fopen("data/admin.txt", "r"); 
    if (punteroArchivo == NULL) { 
        printf("Error al abrir la base de datos en admin.txt: %s\n", strerror(errno)); 
    return 0; }

    char linea[256];
    while (fgets(linea, sizeof(linea), punteroArchivo)) {
        char tipo[10], id[10], nombre[50], contrasena[50];
        sscanf(linea, "Tipo:%[^;];ID:%[^;];Nombre:%[^;];contrasena:%[^;];", tipo, id, nombre, contrasena);
        
        // Asegúrate de que la contraseña se lea correctamente
        nombre[strcspn(nombre, "\n")] = 0; // Eliminar salto de línea
        contrasena[strcspn(contrasena, "\n")] = 0; // Eliminar salto de línea
        
        if (strcmp(nombre, usuario) == 0 && strcmp(contrasena, contrasena) == 0) {
            fclose(punteroArchivo);
            return 1; // Admin encontrado
        }
    }
    fclose(punteroArchivo);
    return 0; // Admin no encontrado
}

// Implementación de la función de login para administradores
int login(char *usuario, char *contrasena) {
    if (esAdmin(usuario, contrasena)) {
        return 1; // Administrador
    } else {
        return 0; // Usuario no encontrado
    }
}

void cerrarSesion() {
    printf("Cerrando sesion...\n");
    Sleep(2000);
    saludoBienvenida();
    // Aquí puedes agregar cualquier limpieza adicional si es necesario
    manejarLogin();
}

#endif // LOGIN_H
