/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   op_archivos.h
 * Author: marvin
 *
 * Created on 16 de diciembre de 2017, 05:57 PM
 */

#ifndef OP_ARCHIVOS_H
#define OP_ARCHIVOS_H

#ifdef __cplusplus
extern "C" {
#endif

    void crear_directorio();
    int get_posicion_subcarpetas(char * path);
    int crear_carpeta(char * path, int posicion_tabla, char * nombre_carpeta, int padre);

#ifdef __cplusplus
}
#endif

#endif /* OP_ARCHIVOS_H */

