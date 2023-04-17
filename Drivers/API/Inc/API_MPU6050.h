/*
 *  API_MPU6050.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Nicolas Cettra
 *
 *	Paquetes de funciones para controlar el Acelerometro/Giroscopo MPU6050 por i2c
 *
 *	Link al repositorio de GITHUB: https://github.com/ncettra/MPU6050
 *
 *  Link al Register Map del MPU6050 : https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 *
 */

#ifndef API_INC_API_MPU6050_H_
#define API_INC_API_MPU6050_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"

#define MPU6050_I2C_TIMEOUT 1000

//Estructura de datos obtenidas del MPU6050
typedef struct{
 //Aceleraciones
 float accX;
 float accY;
 float accZ;
 //Angulos
 float angX;
 float angY;
 float angZ;
 //Temperatura
 float temperature;
} mpu6050_t;


bool mpuInit(I2C_HandleTypeDef * hi2c1);
void mpuUpdate(I2C_HandleTypeDef * hi2c1, mpu6050_t * mpu);

#endif /* API_INC_API_MPU6050_H_ */
