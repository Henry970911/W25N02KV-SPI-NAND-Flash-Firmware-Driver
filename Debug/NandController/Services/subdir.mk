################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NandController/Services/BBT_Services.c \
../NandController/Services/BlockErase_Services.c \
../NandController/Services/OTP_Services.c \
../NandController/Services/Program_Services.c \
../NandController/Services/Protect_Services.c \
../NandController/Services/ReadID_Services.c \
../NandController/Services/Read_Services.c \
../NandController/Services/Reset_Services.c \
../NandController/Services/StatusRegister_Services.c 

OBJS += \
./NandController/Services/BBT_Services.o \
./NandController/Services/BlockErase_Services.o \
./NandController/Services/OTP_Services.o \
./NandController/Services/Program_Services.o \
./NandController/Services/Protect_Services.o \
./NandController/Services/ReadID_Services.o \
./NandController/Services/Read_Services.o \
./NandController/Services/Reset_Services.o \
./NandController/Services/StatusRegister_Services.o 

C_DEPS += \
./NandController/Services/BBT_Services.d \
./NandController/Services/BlockErase_Services.d \
./NandController/Services/OTP_Services.d \
./NandController/Services/Program_Services.d \
./NandController/Services/Protect_Services.d \
./NandController/Services/ReadID_Services.d \
./NandController/Services/Read_Services.d \
./NandController/Services/Reset_Services.d \
./NandController/Services/StatusRegister_Services.d 


# Each subdirectory must supply rules for building sources it contributes
NandController/Services/%.o NandController/Services/%.su NandController/Services/%.cyclo: ../NandController/Services/%.c NandController/Services/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_DIRECT_SMPS_SUPPLY -DUSE_HAL_DRIVER -DSTM32H735xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Driver" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Hal" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Services" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-NandController-2f-Services

clean-NandController-2f-Services:
	-$(RM) ./NandController/Services/BBT_Services.cyclo ./NandController/Services/BBT_Services.d ./NandController/Services/BBT_Services.o ./NandController/Services/BBT_Services.su ./NandController/Services/BlockErase_Services.cyclo ./NandController/Services/BlockErase_Services.d ./NandController/Services/BlockErase_Services.o ./NandController/Services/BlockErase_Services.su ./NandController/Services/OTP_Services.cyclo ./NandController/Services/OTP_Services.d ./NandController/Services/OTP_Services.o ./NandController/Services/OTP_Services.su ./NandController/Services/Program_Services.cyclo ./NandController/Services/Program_Services.d ./NandController/Services/Program_Services.o ./NandController/Services/Program_Services.su ./NandController/Services/Protect_Services.cyclo ./NandController/Services/Protect_Services.d ./NandController/Services/Protect_Services.o ./NandController/Services/Protect_Services.su ./NandController/Services/ReadID_Services.cyclo ./NandController/Services/ReadID_Services.d ./NandController/Services/ReadID_Services.o ./NandController/Services/ReadID_Services.su ./NandController/Services/Read_Services.cyclo ./NandController/Services/Read_Services.d ./NandController/Services/Read_Services.o ./NandController/Services/Read_Services.su ./NandController/Services/Reset_Services.cyclo ./NandController/Services/Reset_Services.d ./NandController/Services/Reset_Services.o ./NandController/Services/Reset_Services.su ./NandController/Services/StatusRegister_Services.cyclo ./NandController/Services/StatusRegister_Services.d ./NandController/Services/StatusRegister_Services.o ./NandController/Services/StatusRegister_Services.su

.PHONY: clean-NandController-2f-Services

