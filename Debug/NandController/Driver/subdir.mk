################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NandController/Driver/Nand_Dri_Erase.c \
../NandController/Driver/Nand_Dri_Program.c \
../NandController/Driver/Nand_Dri_Protect.c \
../NandController/Driver/Nand_Dri_Read.c \
../NandController/Driver/Nand_Dri_ReadID.c \
../NandController/Driver/Nand_Dri_Reset.c \
../NandController/Driver/Nand_Dri_StatusRegister.c 

OBJS += \
./NandController/Driver/Nand_Dri_Erase.o \
./NandController/Driver/Nand_Dri_Program.o \
./NandController/Driver/Nand_Dri_Protect.o \
./NandController/Driver/Nand_Dri_Read.o \
./NandController/Driver/Nand_Dri_ReadID.o \
./NandController/Driver/Nand_Dri_Reset.o \
./NandController/Driver/Nand_Dri_StatusRegister.o 

C_DEPS += \
./NandController/Driver/Nand_Dri_Erase.d \
./NandController/Driver/Nand_Dri_Program.d \
./NandController/Driver/Nand_Dri_Protect.d \
./NandController/Driver/Nand_Dri_Read.d \
./NandController/Driver/Nand_Dri_ReadID.d \
./NandController/Driver/Nand_Dri_Reset.d \
./NandController/Driver/Nand_Dri_StatusRegister.d 


# Each subdirectory must supply rules for building sources it contributes
NandController/Driver/%.o NandController/Driver/%.su NandController/Driver/%.cyclo: ../NandController/Driver/%.c NandController/Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_DIRECT_SMPS_SUPPLY -DUSE_HAL_DRIVER -DSTM32H735xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Driver" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Hal" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Services" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-NandController-2f-Driver

clean-NandController-2f-Driver:
	-$(RM) ./NandController/Driver/Nand_Dri_Erase.cyclo ./NandController/Driver/Nand_Dri_Erase.d ./NandController/Driver/Nand_Dri_Erase.o ./NandController/Driver/Nand_Dri_Erase.su ./NandController/Driver/Nand_Dri_Program.cyclo ./NandController/Driver/Nand_Dri_Program.d ./NandController/Driver/Nand_Dri_Program.o ./NandController/Driver/Nand_Dri_Program.su ./NandController/Driver/Nand_Dri_Protect.cyclo ./NandController/Driver/Nand_Dri_Protect.d ./NandController/Driver/Nand_Dri_Protect.o ./NandController/Driver/Nand_Dri_Protect.su ./NandController/Driver/Nand_Dri_Read.cyclo ./NandController/Driver/Nand_Dri_Read.d ./NandController/Driver/Nand_Dri_Read.o ./NandController/Driver/Nand_Dri_Read.su ./NandController/Driver/Nand_Dri_ReadID.cyclo ./NandController/Driver/Nand_Dri_ReadID.d ./NandController/Driver/Nand_Dri_ReadID.o ./NandController/Driver/Nand_Dri_ReadID.su ./NandController/Driver/Nand_Dri_Reset.cyclo ./NandController/Driver/Nand_Dri_Reset.d ./NandController/Driver/Nand_Dri_Reset.o ./NandController/Driver/Nand_Dri_Reset.su ./NandController/Driver/Nand_Dri_StatusRegister.cyclo ./NandController/Driver/Nand_Dri_StatusRegister.d ./NandController/Driver/Nand_Dri_StatusRegister.o ./NandController/Driver/Nand_Dri_StatusRegister.su

.PHONY: clean-NandController-2f-Driver

