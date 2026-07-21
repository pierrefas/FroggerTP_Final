/*
 * Display Driver
 *
 * Copyright 2019  Catedra Programacion I - ITBA
 *
 * Author(s):
 *  Daniel Jacoby
 *  Nicolas Magliola
 *  Pablo Vacatello
 *(Comentario modificado para entender )
 * Maneja el panel de LEDs de 16x16 de la Raspberry Pi a bajo nivel: un
 * buffer en memoria que se va prendiendo/apagando punto por punto con
 * disp_write(), y recien se manda al hardware de una vez con
 * disp_update(). El resto del proyecto (drawleds.c) nunca escribe LEDs
 * directo: siempre pasa por esta interfaz. Provisto por la catedra: no
 * hay .c en este repo, solo el objeto ya compilado (Debug/disdrv.o).
 */

#ifndef DISDRV_H
#define DISDRV_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define DISP_CANT_X_DOTS    16
#define DISP_CANT_Y_DOTS    16

#define DISP_MIN        0
#define DISP_MAX_X      (DISP_MIN+DISP_CANT_X_DOTS-1)		// = 15
#define DISP_MAX_Y      (DISP_MIN+DISP_CANT_Y_DOTS-1)		// = 15


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct {
    uint8_t x;		//coordenada x del display  
    uint8_t y;		//coordenada y del display 
} dcoord_t;

typedef enum {D_OFF, D_ON} dlevel_t;	//Valores posibles para cada LED


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// Display Services

/**
 * @brief Inicializa el display. Debe llamarse UNA SOLA VEZ al empezar a usar el display. 
*/
void disp_init(void);

/**
 * @brief Borra enteramente el buffer, NO el display.
*/
void disp_clear(void);

/**
 * @brief Escribe al buffer, NO al display. 
 * @param coord Estructura de tipo dcoord_t, que contiene las coordenadas del punto al que se quiere escribir. 
				Recordar que (DISP_MIN < x < DISP_MAX_X) y que (DISP_MIN < y < DISP_MAX_Y). 
 * @param val	valor que se escribirá para el punto indicado por coord. Puede ser D_OFF o D_ON.
 * @return Descripcion valor que devuelve
*/
void disp_write(dcoord_t coord, dlevel_t val);

/**
 * @brief Actualiza todo el display con el contenido del buffer.
*/
void disp_update(void);

/*******************************************************************************
 ******************************************************************************/

#endif // DISDRV_H
