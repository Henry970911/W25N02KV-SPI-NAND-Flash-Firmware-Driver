################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NandController/Hal/Nand_Hal.c 

OBJS += \
./NandController/Hal/Nand_Hal.o 

C_DEPS += \
./NandController/Hal/Nand_Hal.d 


# Each subdirectory must supply rules for building sources it contributes
NandController/Hal/%.o NandController/Hal/%.su NandController/Hal/%.cyclo: ../NandController/Hal/%.c NandController/Hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_DIRECT_SMPS_SUPPLY -DUSE_HAL_DRIVER -DSTM32H735xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Driver" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Hal" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Services" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-NandController-2f-Hal

clean-NandController-2f-Hal:
	-$(RM) ./NandController/Hal/Nand_Hal.cyclo ./NandController/Hal/Nand_Hal.d ./NandController/Hal/Nand_Hal.o ./NandController/Hal/Nand_Hal.su

.PHONY: clean-NandController-2f-Hal

