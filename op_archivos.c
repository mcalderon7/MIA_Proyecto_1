#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "limpiar.h"
#include "estructuras.h"
#include "op_disco.h"
#include "op_archivos.h"
#include "verificadores.h"

#define BOLD  "\e[1m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define MAG  "\x1B[35m"
#define END   "\e[0m"

void crear_directorio(){
    
    char path[] = "/home/marvin/mia_proyecto_1/";
    
    char directorio[100];
    limpiar(directorio, 100);
    
    printf(BOLD "Indique el path del directorio que desea crear \n-> " END);
    scanf("%s", directorio);
    
    //Si el directorio tiene la diagonal al inicio significa que hay que crearlo en la raiz
    if(directorio[0] == '/'){
        
        //Este es el path del disco que debo obtener por medio del montaje
        char dname[] = "DNAME_tuputamadre.dsk";
        
        char fullpath[200];
        limpiar(fullpath, 200);
        
        strcat(fullpath, path);
        strcat(fullpath, dname);
        
        // posicion_tablas en este punto es el apuntador al bloque de tablas que contiene a la raiz (/)
        int posicion_tablas = sizeof(XMBR) + (sizeof(XNODO)*10);
        // padre en este punto es tambien un apuntador que hace referencia a la misma raiz ya que ella es su mismo padre
        int padre = posicion_tablas;
        // bandera que me sirve para identificar la existencia o creacion de una carpeta
        int flag = 0;
        
        XARREGLO testArreglo;
        
        FILE * fp = fopen(fullpath, "r+b");
        fseek(fp, posicion_tablas, SEEK_SET);
        fread(&testArreglo, sizeof(XARREGLO), 1, fp);
        
        // posicion_tablas en este punto es el apuntador al bloque de tablas (subcarpetas) de raiz (/)
        posicion_tablas = testArreglo.reg_1.tabla_bloque_inicial;
        
        char * pch = strtok (directorio, "/");
        while (pch != NULL)
        {
            
            int resp = verificar_existencia_carpeta(fullpath, posicion_tablas, pch);
            
            if(resp != -1){
                padre = posicion_tablas;
                posicion_tablas = resp;
                flag = 1;
            }else{
                int resp_cc = crear_carpeta(fullpath, posicion_tablas, pch, padre);
                padre = posicion_tablas;
                posicion_tablas = resp_cc;
                flag = 0;
            }
            
            if(posicion_tablas == -1){
                
                printf(RED "------------------------------------------------------------------------\n" END);
                printf(RED "No se pudo crear la carpeta: %s\n", pch);
                printf(RED "------------------------------------------------------------------------\n" END);
                
                break;
                
            }else{
                
                if(flag == 0){
                    printf(GRN "------------------------------------------------------------------------\n" END);
                    printf(GRN "Carpeta %s creada exitosamente!\n", pch);
                    printf(GRN "------------------------------------------------------------------------\n" END);
                }else{
                    printf(GRN "------------------------------------------------------------------------\n" END);
                    printf(GRN "No se crea la carpeta %s porque ya existe!\n", pch);
                    printf(GRN "------------------------------------------------------------------------\n" END);
                }
                
                
                //printf ("%s\n",pch);
                pch = strtok (NULL, "/");
            }
            
        }
        
        fclose(fp);
        
    }else{
        
    }
    
}

int crear_carpeta(char * path, int posicion_tabla, char * nombre_carpeta, int padre){
    
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% INICIA CREACION DE CARPETA %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    printf("VALORES RECIBIDOS:\n");
    printf("Path: %s\n", path);
    printf("Posicion tabla: %d\n", posicion_tabla);
    printf("Nombre carpeta: %s\n", nombre_carpeta);
    printf("Padre: %d\n", padre);
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    
    XTABLA testTabla;
    FILE * fp = fopen(path, "r+b");
    
    int cnt = 0;
    int respuesta = -1;
    int posicion = posicion_tabla;
    
    while(cnt != 10){
        
        fseek(fp, posicion, SEEK_SET);
        fread(&testTabla, sizeof(XTABLA), 1, fp);
        
        if(testTabla.tabla_estado == 0){
            
            limpiar(testTabla.tabla_nombre, sizeof(testTabla.tabla_nombre));
            strcat(testTabla.tabla_nombre, nombre_carpeta);
            
            testTabla.tabla_tipo = 1;
            testTabla.tabla_fecha_creacion = time(0);
            testTabla.tabla_bloque_inicial = get_posicion_subcarpetas(path);
            testTabla.tabla_datanode = -1;
            testTabla.tabla_padre = padre;
            testTabla.tabla_estado = 1;
            
            fseek(fp, posicion, SEEK_SET);
            fwrite(&testTabla, sizeof(XTABLA), 1, fp);
            
            respuesta = testTabla.tabla_bloque_inicial;
            
            break;
            
        }else{
            posicion += sizeof(XTABLA);
        }
        
    }
    
    fclose(fp);
    
    printf(" %%%%%%%%%%%%%%%%%%%%%%%%%%%% FINALIZA CREACION DE CARPETA %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    
    return respuesta;
    
}

// La funcion get_posicion_subcarpetas se encarga de obtener la posicion en donde se encuentra el proximo
// arreglo de tablas vacio.
int get_posicion_subcarpetas(char * path){
    
    int posicion_inicial = sizeof(XMBR) + (sizeof(XNODO)*10);
    
    XARREGLO testArreglo;
    FILE * fp = fopen(path, "r+b");
    fseek(fp, posicion_inicial, SEEK_SET);
    fread(&testArreglo, sizeof(XARREGLO), 1, fp);
    
    int auxiliar = testArreglo.reg_1.tabla_bloque_inicial;
    int respuesta = 0;
    
    while(auxiliar != -1){
        
        fseek(fp, auxiliar, SEEK_SET);
        fread(&testArreglo, sizeof(XARREGLO), 1, fp);
        
        if(testArreglo.reg_1.tabla_bloque_inicial != -1){
            auxiliar = testArreglo.reg_1.tabla_bloque_inicial;
        }else{
            respuesta = auxiliar + sizeof(XARREGLO);
            auxiliar = -1;
        }
        
    }
    
    fclose(fp);
    
    return respuesta;
    
}