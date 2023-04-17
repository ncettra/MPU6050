/*
 *	API_delay.c
 *
 *  Created on: Apr 14, 2023
 *      Author: Nicolas Cettra
 *
 *	Paquete de funciones para controlar retardos no bloqueantes
 */


#include "API_delay.h"
#include "stm32f1xx_hal.h"

/*
 * @brief Inicializa la temporizacion
 * @param [in] delay: Puntero a donde se guarda la estructura del temporizador
 * @param [in] duration: Duracion de la temporizacion
 */
void delayInit( delay_t * delay, tick_t duration ) {
	if(delay == NULL) return;
	delay->duration = duration;
	delay->running = false;
}

/*
 * @brief Lee la estructura del temporizado y comprueba si se ha cumplido
 * @param [in] delay: Puntero a donde se guarda la estructura del temporizador
 * @param [in] duration: Duracion de la temporizacion
 * @return true si se cumplio la temporizacion, false si no se cumplio la temporizacion
 */
bool delayRead( delay_t * delay ) {
	if(delay == NULL) return false;
	if(!delay->running) {
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else if(HAL_GetTick() - delay->startTime >= delay->duration) {
		delay->running = false;
		delay->startTime = HAL_GetTick();
		return true;
	}
	return false;
}

/*
 * @brief Modifica la estructura del temporizado
 * @param [in] delay: Puntero a donde se guarda la estructura del temporizador
 * @param [in] duration: Duracion de la temporizacion
 */
void delayWrite( delay_t * delay, tick_t duration ) {
	if(delay == NULL) return;
	delay->duration = duration;
}

/*
 * @brief Reinicia el temporizado
 * @param [in] delay: Puntero a donde se guarda la estructura del temporizador
 */
void delayRestart( delay_t * delay) {
	delay->startTime = HAL_GetTick();
}
