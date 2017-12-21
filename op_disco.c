#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "limpiar.h"
#include "estructuras.h"
#include "op_disco.h"

#define BOLD  "\e[1m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define MAG  "\x1B[35m"
#define END   "\e[0m"

void crear_disco(){
    
    char path[] = "C:/Users/DEV01/Desktop/mia_proyecto_1/";
    //char path[] = "/home/marvin/mia_proyecto_1/";
    
    int cantidad = 0;
    
    char nombre[50];
    limpiar(nombre, 50);
    
    printf(BOLD "¿Cual sera el nombre del disco?\n-> " END);
    scanf("%s", nombre);
    printf(BOLD "¿Cuántos DataNodes desea crear?\n-> " END);
    scanf("%d", &cantidad);
    
    if(cantidad >= 3 && cantidad <= 10){
        
        // Inicio de creación del archivo de DataName
            
            char dname_path[100];
            limpiar(dname_path, 100);
            
            int tamano_real = 2 * 1000000;
            
            strcat(dname_path, path);
            strcat(dname_path, "DNAME_");
            strcat(dname_path, nombre);
            strcat(dname_path, ".dsk");
            
            // Creo el MBR
            XMBR mbr;
            mbr.mbr_cantidad_nodos = cantidad;
            mbr.mbr_numero_magico = 100;
            mbr.mbr_tabla_nodos = sizeof(XMBR);
            mbr.mbr_tabla_nombres = mbr.mbr_tabla_nodos + sizeof(XTABLA) * cantidad;
            
            FILE * fp = fopen(dname_path, "wb");
            fseek(fp, 0, SEEK_SET);
            fwrite(&mbr, sizeof(XMBR), 1, fp);
            
            int i;
            int j;
            int posicion = sizeof(XMBR);
            for( i = 1; i < cantidad + 1; i++){
                
                // Inicio de creación del archivo de DataNode 
                    XNODO nodo;
                    char numero[2];
                    limpiar(numero, 2);
                    sprintf(numero, "%d", i);
                    
                    limpiar(nodo.nodo_ruta_nodo, sizeof(nodo.nodo_ruta_nodo));
                    strcat(nodo.nodo_ruta_nodo, path);
                    strcat(nodo.nodo_ruta_nodo, "DNODE_");
                    strcat(nodo.nodo_ruta_nodo, numero);
                    strcat(nodo.nodo_ruta_nodo, "_");
                    strcat(nodo.nodo_ruta_nodo, nombre);
                    strcat(nodo.nodo_ruta_nodo, ".dsk");

                    nodo.nodo_tamano_nodo = sizeof(XNODO);
                    nodo.nodo_tamano_nodo_m = sizeof(XNODO);

                    fseek(fp, posicion, SEEK_SET);
                    fwrite(&nodo, sizeof(XNODO), 1, fp);

                    //Creo de igual forma el archivo fisico del DataNode con la cantidad de bloques de datos vacíos.
                    FILE * dnf = fopen(nodo.nodo_ruta_nodo, "wb");
                    int cantidad_bloques = calcular_bloques(tamano_real);
                    int pos_bloque = 0;

                    for(j = 0; j < cantidad_bloques; j++){

                        XBLOQUE bloque;
                        limpiar(bloque.bd_data, sizeof(bloque.bd_data));
                        strcat(bloque.bd_data, "NULL");
                        bloque.bd_datanode = j;
                        bloque.bd_siguiente = -1;
                        bloque.bd_datanode = -1;
                        bloque.bd_estado = 0;

                        fseek(dnf, pos_bloque, SEEK_SET);
                        fwrite(&bloque, sizeof(XBLOQUE), 1, dnf);

                        pos_bloque += sizeof(XBLOQUE);

                    }

                    fclose(dnf);

                    posicion += sizeof(XNODO);
                    
                // Fin de creación del archivo DataNode
                        
            }
            
            //Si la cantidad de DataNodes a crear es menor a 10, procedo a crear los que faltan con valores nulos.
            if(cantidad < 10){
                
                int faltantes = 10 - cantidad;
                
                for( i = 0; i < faltantes; i++){
                    
                    XNODO nodo;
                    limpiar(nodo.nodo_ruta_nodo, sizeof(nodo.nodo_ruta_nodo));
                    strcat(nodo.nodo_ruta_nodo, "ESPACIOVACIO");
                    nodo.nodo_tamano_nodo = -1;
                    nodo.nodo_tamano_nodo_m = -1;
                    
                    fseek(fp, posicion, SEEK_SET);
                    fwrite(&nodo, sizeof(XNODO), 1, fp);
                    
                    posicion += sizeof(XNODO);
                    
                }
                
            }
            
            // Inicio de creación de las 1000 estructuras de tabla de nombres
                
                for(i = 0; i < 1000; i++){
                    
                    XTABLA tabla;
                    limpiar(tabla.tabla_nombre, sizeof(tabla.tabla_nombre));
                    strcat(tabla.tabla_nombre, "TABLAVACIA");
                    tabla.tabla_tipo = -1;
                    tabla.tabla_fecha_creacion = time(0);
                    tabla.tabla_bloque_inicial = -1;
                    tabla.tabla_datanode = -1;
                    tabla.tabla_padre = -1;
                    tabla.tabla_estado = 0;
                    
                    XARREGLO arreglo;
                    arreglo.reg_1 = tabla;
                    arreglo.reg_2 = tabla;
                    arreglo.reg_3 = tabla;
                    arreglo.reg_4 = tabla;
                    arreglo.reg_5 = tabla;
                    arreglo.reg_6 = tabla;
                    arreglo.reg_7 = tabla;
                    arreglo.reg_8 = tabla;
                    arreglo.reg_9 = tabla;
                    arreglo.reg_10 = tabla;
                    
                    if(i == 0){
                        
                        limpiar(arreglo.reg_1.tabla_nombre, sizeof(arreglo.reg_1.tabla_nombre));
                        strcat(arreglo.reg_1.tabla_nombre, "/");
                        arreglo.reg_1.tabla_tipo = 1;
                        arreglo.reg_1.tabla_fecha_creacion = time(0);
                        arreglo.reg_1.tabla_bloque_inicial = posicion + sizeof(XARREGLO);
                        arreglo.reg_1.tabla_datanode = -1;
                        arreglo.reg_1.tabla_padre = posicion;
                        arreglo.reg_1.tabla_estado = 1;
                        
                        printf("/// RAIZ COMIENZA EN: %d ///\n", posicion);
                        printf("/// SUBCARPETA DE RAIZ COMIENZA EN: %d ///\n", arreglo.reg_1.tabla_bloque_inicial);
                        
                    }
                    
                    fseek(fp, posicion, SEEK_SET);
                    fwrite(&arreglo, sizeof(XARREGLO), 1, fp);
                    
                    posicion += sizeof(XARREGLO);
                    
                }
            
            // Fin de creación de las 1000 estructuras de tabla de nombres
            
            fclose(fp);
            
        // Fin de creación del archivo de DataName
            
        printf(GRN "------------------------------------------------------------------------\n" END);
        printf(GRN "Disco creado correctamente.\n" END);
        printf(GRN "------------------------------------------------------------------------\n" END);
        
    }else{
        
        printf(RED "------------------------------------------------------------------------\n" END);
        printf(RED "Solo se pueden crear como mínimo 3 DataNodes y como máximo 10 DataNodes.\n" END);
        printf(RED "------------------------------------------------------------------------\n" END);
        
    }
    
}

int calcular_bloques(int tamano){
    return (tamano / sizeof(XBLOQUE));
}