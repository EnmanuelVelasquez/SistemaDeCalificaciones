#include <stdio.h>
#include "inicio.h"
#include <string.h>
#include <stdbool.h>
#include "utilidades.h"
#include "admin.h"
#include "estudiante.h"

Menu option;

//INFORME GENERAL ESTUDIANTES VEN ASIGNATURAS Y PROMEDIO FINAL
//INFORME ASIGNATURAS NOTAS DEL ESTUDIANTE / EN DOCENTES
//BOLETÍN

// Declaración de funciones
Menu menuPrincipal();

int main(){  
    option = menuPrincipal(); // Llamar a la función de menu principal
    return 0;
}




