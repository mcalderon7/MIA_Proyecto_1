/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   verificadores.h
 * Author: marvin
 *
 * Created on 17 de diciembre de 2017, 03:45 PM
 */

#ifndef VERIFICADORES_H
#define VERIFICADORES_H

#ifdef __cplusplus
extern "C" {
#endif

    int verificar_existencia_carpeta(char * path, int posicion_tabla, char * nombre_carpeta);
    int verificar_posicion_subcarpeta_disponible(char * path);

#ifdef __cplusplus
}
#endif

#endif /* VERIFICADORES_H */

