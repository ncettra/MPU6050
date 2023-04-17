/*
 *  API_delay.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Nicolas Cettra
 *
 *	Paquete de funciones para controlar retardos no bloqueantes
 */


#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t tick_t;

typedef struct{
	tick_t startTime;
	tick_t duration;
	bool running;
} delay_t;

//Inicializa el delay ingresando la estructura del temporizador
void delayInit( delay_t * delay, tick_t duration );

//Realiza la lectura del temporizador, retornando true si se cumplio o false si aun no
bool delayRead( delay_t * delay );

//Actualiza la estructura del temporizador
void delayWrite( delay_t * delay, tick_t duration );

//Reinicia la temporizacion
void delayRestart( delay_t * delay);


#endif /* API_INC_API_DELAY_H_ */
