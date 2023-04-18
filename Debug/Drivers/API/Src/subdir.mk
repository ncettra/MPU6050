################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_MPU6050.c \
../Drivers/API/Src/API_alerts.c \
../Drivers/API/Src/API_delay.c \
../Drivers/API/Src/STM32F1_port.c \
../Drivers/API/Src/STM32F4_port.c 

OBJS += \
./Drivers/API/Src/API_MPU6050.o \
./Drivers/API/Src/API_alerts.o \
./Drivers/API/Src/API_delay.o \
./Drivers/API/Src/STM32F1_port.o \
./Drivers/API/Src/STM32F4_port.o 

C_DEPS += \
./Drivers/API/Src/API_MPU6050.d \
./Drivers/API/Src/API_alerts.d \
./Drivers/API/Src/API_delay.d \
./Drivers/API/Src/STM32F1_port.d \
./Drivers/API/Src/STM32F4_port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Nicolas/STM32CubeIDE/workspace_1.12.0/TP_FINAL_PDM/Drivers/API" -I"C:/Users/Nicolas/STM32CubeIDE/workspace_1.12.0/TP_FINAL_PDM/Drivers/API/Inc" -I"C:/Users/Nicolas/STM32CubeIDE/workspace_1.12.0/TP_FINAL_PDM/Drivers/API/Src" -I"C:/Users/Nicolas/STM32CubeIDE/workspace_1.12.0/TP_FINAL_PDM/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_MPU6050.cyclo ./Drivers/API/Src/API_MPU6050.d ./Drivers/API/Src/API_MPU6050.o ./Drivers/API/Src/API_MPU6050.su ./Drivers/API/Src/API_alerts.cyclo ./Drivers/API/Src/API_alerts.d ./Drivers/API/Src/API_alerts.o ./Drivers/API/Src/API_alerts.su ./Drivers/API/Src/API_delay.cyclo ./Drivers/API/Src/API_delay.d ./Drivers/API/Src/API_delay.o ./Drivers/API/Src/API_delay.su ./Drivers/API/Src/STM32F1_port.cyclo ./Drivers/API/Src/STM32F1_port.d ./Drivers/API/Src/STM32F1_port.o ./Drivers/API/Src/STM32F1_port.su ./Drivers/API/Src/STM32F4_port.cyclo ./Drivers/API/Src/STM32F4_port.d ./Drivers/API/Src/STM32F4_port.o ./Drivers/API/Src/STM32F4_port.su

.PHONY: clean-Drivers-2f-API-2f-Src

