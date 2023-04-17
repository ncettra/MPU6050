/*
 * API_alerts.c
 *
 *  Created on: Apr 15, 2023
 *      Author: Nicolas Cettra
 */

#include "API_alerts.h"

static alertState_t EstadoActual;
static delay_t BuzzerDelay;
static delay_t switchStateDelay;
static float AccMax = 0.5;

const char* FSM_INIT_MSG = "\n\rFSM init";
const char* FSM_TO_ALARM_MSG = "\n\rFSM -> Alarm state";
const char* FSM_TO_DATA_AQ_MSG = "\n\rFSM -> Data acquisition state";

static void buzzerChangeSound();

void initAlertControl(float accMax, uint16_t buttonDelay,UART_HandleTypeDef * uart){

	if(accMax<0.5){accMax=0.5;}
	if(accMax>3.5){accMax=3.5;}
	if(buttonDelay<500){buttonDelay=500;}
	if(buttonDelay>1500){buttonDelay=1500;}

	EstadoActual = ADQUIRIENDO_DATOS;
	AccMax = accMax;
	delayInit(&BuzzerDelay, 700);
	delayInit(&switchStateDelay, buttonDelay);

	/*HAL_UART_Transmit(uart,(uint8_t *)"AT\n\r",strlen("AT\n\r"),10);
	HAL_Delay(1000);
	HAL_UART_Transmit(uart,(uint8_t *)"AT\n\r",strlen("AT\n\r"),10);
	HAL_Delay(1000);
	HAL_UART_Transmit(uart,(uint8_t *)"AT\n\r",strlen("AT\n\r"),10);
	HAL_Delay(1000);
	HAL_UART_Transmit(uart,(uint8_t *)"AT+CMGF=1\n\r",strlen("AT+CMGF=1\n\r"),10);
	HAL_Delay(1000);
	HAL_UART_Transmit(uart,(uint8_t *)"AT+CNMI=2,2,0,0,0\n\r",strlen("AT+CNMI=2,2,0,0,0\n\r"),10);
	HAL_Delay(1000);
	HAL_UART_Transmit(uart,(uint8_t *)"AT+CMGS=\"+543534018863\"\n\r",strlen("AT+CMGS=\"+543534018863\"\n\r"),10);
	HAL_Delay(1000);
	HAL_UART_Transmit(uart,(uint8_t *)"S.O.S.",strlen("S.O.S."),10);
	HAL_Delay(500);
	uint8_t * ctlZ = 0x1a;
	HAL_UART_Transmit(uart,(uint8_t *)ctlZ,1,10);*/

	HAL_UART_Transmit(uart,(uint8_t *)FSM_INIT_MSG,strlen(FSM_INIT_MSG),10);

	//Secuencia led
	for(uint8_t i;i<6;i++){HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);HAL_Delay(100);}


};
void checkAlertControl(mpu6050_t* mpu, UART_HandleTypeDef * uart){

	switch(EstadoActual){
	case ADQUIRIENDO_DATOS:
		HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin,1);
		//Chequeo de aceleracion
		if( abs(mpu->accX) > AccMax || abs(mpu->accY) > AccMax  || abs(mpu->accZ - 1) > AccMax ){
			EstadoActual = ALERTA;
			HAL_UART_Transmit(uart,(uint8_t *)FSM_TO_ALARM_MSG,strlen(FSM_TO_ALARM_MSG),10);
			buzzerChangeSound();

		}
		//Comprobacion de boton con antirebote
		if( !HAL_GPIO_ReadPin(BUTTON1_GPIO_Port,BUTTON1_Pin)){
			//Si es un falso contacto se reinicia el delay
			delayRestart(&switchStateDelay);
		}
		else{

			if(delayRead(&switchStateDelay)){
				EstadoActual = ALERTA;
				HAL_UART_Transmit(uart,(uint8_t *)FSM_TO_ALARM_MSG,strlen(FSM_TO_ALARM_MSG),10);
				buzzerChangeSound();
			}
		}
		break;
	case ALERTA:
		if(delayRead(&BuzzerDelay)){
			HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);
		}
		if( !HAL_GPIO_ReadPin(BUTTON1_GPIO_Port,BUTTON1_Pin)){

			delayRestart(&switchStateDelay);
		}
		else{

			if(delayRead(&switchStateDelay)){EstadoActual = ADQUIRIENDO_DATOS; HAL_UART_Transmit(uart,(uint8_t *)FSM_TO_DATA_AQ_MSG,strlen(FSM_TO_DATA_AQ_MSG),10);}
		}

		break;
	default:
		EstadoActual = ADQUIRIENDO_DATOS;
		break;

	}
};
void buzzerChangeSound(){
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin,0);HAL_Delay(50);
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin,1);HAL_Delay(50);
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin,0);HAL_Delay(50);
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin,1);HAL_Delay(50);
}
