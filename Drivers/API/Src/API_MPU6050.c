/*
 *  API_MPU6050.c
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

#include "API_MPU6050.h"


//REGISTROS I2C, fueron extraidos del Register Map propinados por el fabricante
#define MPU6050_ADDRESS 0xD0 				//Direccion I2C del MPU6050
#define MPU6050_WHO_AM_I 0x75 				//Pag 45
#define MPU6050_POWER_MGM_REGISTER 0x6B 	//Pag 40
#define MPU6050_SAMPLING_DIV_REGISTER 0x19 	//Pag 11
#define MPU6050_ACC_CONFIG_REGISTER 0x1c 	//Pag 15
#define MPU6050_GYRO_CONFIG_REGISTER 0x1B
#define MPU6050_ALLDATA_READ_REGISTER 0x3B 	//Todos los parametros estan en registros sucesivos, asi que puedo recorrer de aca para delante y obtener todos los parametros, se puede ver en la pag

/*
 * @brief Inicializa la comunicacion i2c con el MPU6050 y lo configura
 * @param [in] hi2c: Puntero al delegado i2c donde esta conectado el mpu
 * @return true si inicializo correctamente, false caso contrario
 */
bool mpuInit(void* hi2c){

	/*Las configuraciones por ahora son fijas, pero posteriormente se podrian introducir como argumento de funcion
	 *Lo ideal seria crear una estructura de configuracion, esto es porque cuando recibo, las conversiones dependen
	 *de como ha sido configurado el mpu6050. Por ahora es fijo para simplificar el driver.
	 */

	uint8_t data;
	uint8_t powerManagementData = 0x00;
	uint8_t updateDataRate = 0x07; //divisor para el muestreo
	uint8_t accConfig = 0b00000000; //Pag 15
	uint8_t gyroConfig = 0b00000000; //Pag 14

	readI2C(hi2c,MPU6050_ADDRESS,MPU6050_WHO_AM_I,1,&data,1,MPU6050_I2C_TIMEOUT);


	//Si todo va bien tiene que devolver un 0x68
	if (data == 0x68){
		//Ahora vamos a configurar el MPU6050
		writeI2C(hi2c, MPU6050_ADDRESS, MPU6050_POWER_MGM_REGISTER, 1, &powerManagementData, 1, MPU6050_I2C_TIMEOUT);
		writeI2C(hi2c, MPU6050_ADDRESS, MPU6050_SAMPLING_DIV_REGISTER, 1, &updateDataRate, 1, MPU6050_I2C_TIMEOUT);
		writeI2C(hi2c, MPU6050_ADDRESS, MPU6050_ACC_CONFIG_REGISTER, 1, &accConfig, 1, MPU6050_I2C_TIMEOUT);
		writeI2C(hi2c, MPU6050_ADDRESS, MPU6050_GYRO_CONFIG_REGISTER, 1, &gyroConfig, 1, MPU6050_I2C_TIMEOUT);
		return true;
	}
	else{
		return false;
	}
	return true;
}

/*
 * @brief Actualiza la estructura de datos del mpu6050
 * @param [in] hi2c: Puntero al delegado i2c donde esta conectado el mpu
 * @param [in] mpu: Puntero a la estructura de datos del mpu6050
 */
void mpuUpdate(void* hi2c, mpu6050_t * mpu){

	uint8_t data[14];

	readI2C(hi2c, MPU6050_ADDRESS, MPU6050_ALLDATA_READ_REGISTER, 1, data, 14, MPU6050_I2C_TIMEOUT);
	//Es importante que la RAW DATA sea con signo, porque sino, para valores menores a cero no se le interpreta el modulo a 2 y salta de 0 a 65365
	int16_t accX = ((uint16_t)data[0]<<8)+data[1];
	int16_t accY = ((uint16_t)data[2]<<8)+data[3];
	int16_t accZ = ((uint16_t)data[4]<<8)+data[5];
	int16_t Temp = ((uint16_t)data[6]<<8)+data[7];
	int16_t angX = ((uint16_t)data[8]<<8)+data[9];
	int16_t angY = ((uint16_t)data[10]<<8)+data[11];
	int16_t angZ = ((uint16_t)data[12]<<8)+data[13];

	mpu -> accX = accX/16384.0; //Ahora convierto la informacion cruda (RAW DATA) en valores medidos en G, el valor con el que divido depende del FS_SEL en el ACCEL_CONFIG
	mpu -> accY = accY/16384.0;
	mpu -> accZ = accZ/16384.0;
	mpu -> temperature = (Temp/340.0) + 36.53; //Pag 30
	mpu -> angX = angX/131.0;
	mpu -> angY = angY/131.0;
	mpu -> angZ = angZ/131.0;

}
