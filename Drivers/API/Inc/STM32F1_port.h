/*
 * STM32F103C8_port.h
 *
 *  Created on: 17 abr. 2023
 *      Author: Nicolas
 */

#ifndef API_INC_STM32F1_PORT_H_
#define API_INC_STM32F1_PORT_H_

#include "stm32f1xx_hal.h"

void readI2C(void * hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize,uint8_t* pData,uint16_t Size,uint32_t Timeout);
void writeI2C(void * hi2c,uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#endif /* API_INC_STM32F1_PORT_H_ */
