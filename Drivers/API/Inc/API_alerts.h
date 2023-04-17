/*
 * API_alerts.h
 *
 *  Created on: Apr 15, 2023
 *      Author: Nicolas
 */

#ifndef API_INC_API_ALERTS_H_
#define API_INC_API_ALERTS_H_

#include "API_delay.h"
#include "API_MPU6050.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOA
#define BUTTON1_Pin GPIO_PIN_3
#define BUTTON1_GPIO_Port GPIOA

typedef enum{
	ADQUIRIENDO_DATOS,
	ALERTA
} alertState_t;


void initAlertControl(float accMax, uint16_t buttonDelay,UART_HandleTypeDef* uart);
void checkAlertControl(mpu6050_t* mpu, UART_HandleTypeDef * uart);

#endif /* API_INC_API_ALERTS_H_ */
