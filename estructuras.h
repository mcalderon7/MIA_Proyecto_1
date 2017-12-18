/* 
 * File:   estructuras.h
 * Author: DEV01
 *
 * Created on 14 de diciembre de 2017, 09:11 PM
 */

#ifndef ESTRUCTURAS_H
#define	ESTRUCTURAS_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct mbr {
        int mbr_cantidad_nodos;
        int mbr_numero_magico;
        int mbr_tabla_nodos;
        int mbr_tabla_nombres;
    } XMBR;
    
    typedef struct nodo {
        char nodo_ruta_nodo[100];
        int nodo_tamano_nodo;
        int nodo_tamano_nodo_m;
    } XNODO;
    
    typedef struct tabla {
        char tabla_nombre[20];
        int tabla_tipo; // Carpeta = 1 ** Archivo = 0
        time_t tabla_fecha_creacion;
        int tabla_bloque_inicial;
        int tabla_datanode;
        int tabla_padre;
        int tabla_estado; // Ocupado = 1 ** Libre = 0
    } XTABLA;
    
    typedef struct arreglo{
        XTABLA reg_1;
        XTABLA reg_2;
        XTABLA reg_3;
        XTABLA reg_4;
        XTABLA reg_5;
        XTABLA reg_6;
        XTABLA reg_7;
        XTABLA reg_8;
        XTABLA reg_9;
        XTABLA reg_10;
    } XARREGLO;
    
    typedef struct bloque {
        char bd_data[50];
        int bd_numero;
        int bd_siguiente;
        int bd_datanode;
        int bd_estado; // Ocupado = 1 ** Libre = 0
    } XBLOQUE;


#ifdef	__cplusplus
}
#endif

#endif	/* ESTRUCTURAS_H */

