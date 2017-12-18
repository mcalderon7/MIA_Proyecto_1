#include <stdio.h>
#include <stdlib.h>
#include "op_disco.h"
#include "op_archivos.h"

#define KBLU  "\x1B[34m"
#define RED  "\x1B[31m"
#define END "\e[0m"

int x = 0;

int main() {

    x = -1;
    int entrada = -1;

    while(x != 0){

        printf(KBLU "******************* ADMINISTRADOR DE DISCOS *************************\n");
        printf(KBLU "1 - Crear disco duro     ----------   8 - Crear archivo\n");
        printf(KBLU "2 - Montar disco duro    ----------   9 - Eliminar archivo\n");
        printf(KBLU "3 - Desmontar disco duro ----------  10 - Copiar archivo\n");
        printf(KBLU "4 - Crear directorio     ----------  11 - Buscar archivos\n");
        printf(KBLU "5 - Eliminar directorio  ----------  12 - Reporte de DataNode\n");
        printf(KBLU "6 - Copiar directorios   ----------  13 - Reporte de Archivos\n");
        printf(KBLU "7 - Buscar directorio    ----------  14 - Reporte de Tabla de Nombres\n");
        printf(KBLU "0 - Salir\n");
        printf(KBLU "*********************************************************************\n");
        printf(KBLU "Selecciona una opción:\n");
        scanf("%d", &entrada);

        if(entrada == 0){
            x = 0;
        }else if(entrada == 1){
            printf("***************************************************************\n");
            crear_disco();
        }else if(entrada == 2){
            printf("***************************************************************\n");
            //crear_disco();
        }else if(entrada == 3){
            printf("***************************************************************\n");
            //crear_disco();
        }else if(entrada == 4){
            printf("***************************************************************\n");
            crear_directorio();
        }else if(entrada == 5){
            printf("***************************************************************\n");
            //crear_disco();
        }else{
            printf(RED "***************************************************************\n" END);
            printf(RED "OPCION INGRESADA INVALIDA.\n" END);
            printf(RED "***************************************************************\n" END);
        }

    }

    return 0;
    
}

