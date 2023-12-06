################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Drivers/MCAL/STM32F103C6_EXTI_Drivers.c \
../STM32F103C6_Drivers/MCAL/STM32F103C6_GPIO_Drivers.c \
../STM32F103C6_Drivers/MCAL/STM32F103C6_I2C_Drivers.c \
../STM32F103C6_Drivers/MCAL/STM32F103C6_RCC_Drivers.c \
../STM32F103C6_Drivers/MCAL/STM32F103C6_SPI_Drivers.c \
../STM32F103C6_Drivers/MCAL/STM32F103C6_USART_Drivers.c 

OBJS += \
./STM32F103C6_Drivers/MCAL/STM32F103C6_EXTI_Drivers.o \
./STM32F103C6_Drivers/MCAL/STM32F103C6_GPIO_Drivers.o \
./STM32F103C6_Drivers/MCAL/STM32F103C6_I2C_Drivers.o \
./STM32F103C6_Drivers/MCAL/STM32F103C6_RCC_Drivers.o \
./STM32F103C6_Drivers/MCAL/STM32F103C6_SPI_Drivers.o \
./STM32F103C6_Drivers/MCAL/STM32F103C6_USART_Drivers.o 

C_DEPS += \
./STM32F103C6_Drivers/MCAL/STM32F103C6_EXTI_Drivers.d \
./STM32F103C6_Drivers/MCAL/STM32F103C6_GPIO_Drivers.d \
./STM32F103C6_Drivers/MCAL/STM32F103C6_I2C_Drivers.d \
./STM32F103C6_Drivers/MCAL/STM32F103C6_RCC_Drivers.d \
./STM32F103C6_Drivers/MCAL/STM32F103C6_SPI_Drivers.d \
./STM32F103C6_Drivers/MCAL/STM32F103C6_USART_Drivers.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Drivers/MCAL/STM32F103C6_EXTI_Drivers.o: ../STM32F103C6_Drivers/MCAL/STM32F103C6_EXTI_Drivers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/MCAL/STM32F103C6_EXTI_Drivers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/MCAL/STM32F103C6_GPIO_Drivers.o: ../STM32F103C6_Drivers/MCAL/STM32F103C6_GPIO_Drivers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/MCAL/STM32F103C6_GPIO_Drivers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/MCAL/STM32F103C6_I2C_Drivers.o: ../STM32F103C6_Drivers/MCAL/STM32F103C6_I2C_Drivers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/MCAL/STM32F103C6_I2C_Drivers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/MCAL/STM32F103C6_RCC_Drivers.o: ../STM32F103C6_Drivers/MCAL/STM32F103C6_RCC_Drivers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/MCAL/STM32F103C6_RCC_Drivers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/MCAL/STM32F103C6_SPI_Drivers.o: ../STM32F103C6_Drivers/MCAL/STM32F103C6_SPI_Drivers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/MCAL/STM32F103C6_SPI_Drivers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/MCAL/STM32F103C6_USART_Drivers.o: ../STM32F103C6_Drivers/MCAL/STM32F103C6_USART_Drivers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Keroll/Second term/Unit 8 MCU Interfacing/Labs/Lab Finals/STM32_I2C_Driver/Drivers/STM32F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/MCAL/STM32F103C6_USART_Drivers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

