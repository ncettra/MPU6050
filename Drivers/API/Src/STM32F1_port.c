/*
 * STM32F103C8_port.c
 *
 *  Created on: 17 abr. 2023
 *      Author: Nicolas
 */
#include "STM32F1_port.h"

void readI2C(void * hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize,uint8_t* pData,uint16_t Size,uint32_t Timeout){

	HAL_I2C_Mem_Read((I2C_HandleTypeDef*) hi2c,DevAddress,MemAddress,MemAddSize,pData,Size,Timeout);

};
void writeI2C(void * hi2c,uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout){

	HAL_I2C_Mem_Write((I2C_HandleTypeDef*) hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
}
