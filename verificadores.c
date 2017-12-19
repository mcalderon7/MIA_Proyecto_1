#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "limpiar.h"
#include "estructuras.h"
#include "op_disco.h"
#include "op_archivos.h"

#define BOLD  "\e[1m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define MAG  "\x1B[35m"
#define END   "\e[0m"

int verificar_existencia_carpeta(char * path, int posicion_tabla, char * nombre_carpeta){
    
    int cnt = 0;
    int respuesta = -1;
    int pos = posicion_tabla;
    
    XTABLA tabla;
    
    FILE * fp = fopen(path, "r+b");
    
    while(cnt != 10){
        
        fseek(fp, pos, SEEK_SET);
        fread(&tabla, sizeof(XTABLA), 1, fp);
        
        if(strcmp(tabla.tabla_nombre, nombre_carpeta) == 0){
            respuesta = tabla.tabla_bloque_inicial;
            break;
        }else{
            pos += sizeof(XTABLA);
            cnt += 1;
        }
        
    }
    
    fclose(fp);
    
    return respuesta;
    
}

int verificar_posicion_subcarpeta_disponible(char * path){
    
    int posicion = sizeof(XMBR) + (10*sizeof(XNODO));
    
    XARREGLO arreglo;
    FILE * fp = fopen(path, "r+b");
    
    while(posicion != -1){
        
        fseek(fp, posicion, SEEK_SET);
        fread(&arreglo, sizeof(XARREGLO), 1, fp);
        
        if(arreglo.reg_1.tabla_bloque_inicial != -1){
            posicion = arreglo.reg_1.tabla_bloque_inicial;
        }else{
            break; 
        }
        
    }
    
    posicion += sizeof(XARREGLO);
    
    return posicion;
    
}