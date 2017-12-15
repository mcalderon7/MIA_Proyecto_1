#include <string.h>
#include "limpiar.h"

void limpiar(char* cadena, int tamanio){
    while(tamanio >= 0){
        cadena[tamanio] = '\0';
        tamanio--;
    }
}

void vaciarArreglo(char* entrada){

    int w = strlen(entrada);
    int i;

    for(i = 0; i < w; i++){
        entrada[i] = '\0';
    }
}