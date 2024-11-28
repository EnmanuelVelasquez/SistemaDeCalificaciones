//DEFINIMOS LA MACRO "UTILIDADES_H":
#ifndef UTILIDADES_H
#define UTILIDADES_H
//Incluímos las librerías y otros archivos.h que vamos a utilizar:
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "admin.h"

// Definimos las macros para las constantes:
#define MAXADMINS 10
#define MAXESTUDIANTES 10
#define MAXDOCENTES 10
#define MAXASIGNATURAS 10
#define MAXCALIFICACIONES 6

//macros funcionales:
#define FILE_ERROR(mensaje) fprintf(stderr, "Error: %s\n", mensaje); exit(EXIT_FAILURE)


//enumerador para notas:
typedef enum{
    MUYBAJO,
    MUYBAJO,
    BAJO,
    ACEPTABLE,
    ALTO,
    EXCELENTE
}NOTAS;


void salir();

void salir() {
    printf("Saliendo...\n");
    Sleep(2000);  // Espera 2 segundos 
    exit(0); // esto cierra (detiene) en su totalidad el programa.
}

#endif