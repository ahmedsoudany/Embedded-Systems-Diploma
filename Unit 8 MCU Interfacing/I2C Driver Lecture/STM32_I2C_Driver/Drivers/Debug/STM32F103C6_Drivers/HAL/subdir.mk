################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Drivers/HAL/I2C_Slave_EEPROM.c \
../STM32F103C6_Drivers/HAL/KEYPAD.c \
../STM32F103C6_Drivers/HAL/LCD.c \
../STM32F103C6_Drivers/HAL/S7_Segment.c 

OBJS += \
./STM32F103C6_Drivers/HAL/I2C_Slave_EEPROM.o \
./STM32F103C6_Drivers/HAL/KEYPAD.o \
./STM32F103C6_Drivers/HAL/LCD.o \
./STM32F103C6_Drivers/HAL/S7_Segment.o 

C_DEPS += \
./STM32F103C6_Drivers/HAL/I2C_Slave_EEPROM.d \
./STM32F103C6_Drivers/HAL/KEYPAD.d \
./STM32F103C6_Drivers/HAL/LCD.d \
./STM32F103C6_Drivers/HAL/S7_Segment.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Drivers/HAL/I2C_Slave_EEPROM.o: ../STM32F103C6_Drivers/HAL/I2C_Slave_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/HAL/I2C_Slave_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/HAL/KEYPAD.o: ../STM32F103C6_Drivers/HAL/KEYPAD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/HAL/KEYPAD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/HAL/LCD.o: ../STM32F103C6_Drivers/HAL/LCD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/HAL/LCD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/HAL/S7_Segment.o: ../STM32F103C6_Drivers/HAL/S7_Segment.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/HAL/S7_Segment.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

