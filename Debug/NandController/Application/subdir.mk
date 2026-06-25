################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NandController/Application/Test_Endurance.c \
../NandController/Application/Test_FactoryInvalidBlockScan.c \
../NandController/Application/Test_Pattern.c \
../NandController/Application/Test_SinglePage(MultiplePattern).c \
../NandController/Application/Test_SinglePage(RandomLoadProgram).c \
../NandController/Application/Test_SinglePage.c 

OBJS += \
./NandController/Application/Test_Endurance.o \
./NandController/Application/Test_FactoryInvalidBlockScan.o \
./NandController/Application/Test_Pattern.o \
./NandController/Application/Test_SinglePage(MultiplePattern).o \
./NandController/Application/Test_SinglePage(RandomLoadProgram).o \
./NandController/Application/Test_SinglePage.o 

C_DEPS += \
./NandController/Application/Test_Endurance.d \
./NandController/Application/Test_FactoryInvalidBlockScan.d \
./NandController/Application/Test_Pattern.d \
./NandController/Application/Test_SinglePage(MultiplePattern).d \
./NandController/Application/Test_SinglePage(RandomLoadProgram).d \
./NandController/Application/Test_SinglePage.d 


# Each subdirectory must supply rules for building sources it contributes
NandController/Application/%.o NandController/Application/%.su NandController/Application/%.cyclo: ../NandController/Application/%.c NandController/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_DIRECT_SMPS_SUPPLY -DUSE_HAL_DRIVER -DSTM32H735xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Driver" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Hal" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Services" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
NandController/Application/Test_SinglePage(MultiplePattern).o: ../NandController/Application/Test_SinglePage(MultiplePattern).c NandController/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_DIRECT_SMPS_SUPPLY -DUSE_HAL_DRIVER -DSTM32H735xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Driver" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Hal" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Services" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"NandController/Application/Test_SinglePage(MultiplePattern).d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
NandController/Application/Test_SinglePage(RandomLoadProgram).o: ../NandController/Application/Test_SinglePage(RandomLoadProgram).c NandController/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_DIRECT_SMPS_SUPPLY -DUSE_HAL_DRIVER -DSTM32H735xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Driver" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Hal" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Services" -I"C:/Users/CPC/STM32CubeIDE/workspace1.20.0/W25N02 Firmware/NandController/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"NandController/Application/Test_SinglePage(RandomLoadProgram).d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-NandController-2f-Application

clean-NandController-2f-Application:
	-$(RM) ./NandController/Application/Test_Endurance.cyclo ./NandController/Application/Test_Endurance.d ./NandController/Application/Test_Endurance.o ./NandController/Application/Test_Endurance.su ./NandController/Application/Test_FactoryInvalidBlockScan.cyclo ./NandController/Application/Test_FactoryInvalidBlockScan.d ./NandController/Application/Test_FactoryInvalidBlockScan.o ./NandController/Application/Test_FactoryInvalidBlockScan.su ./NandController/Application/Test_Pattern.cyclo ./NandController/Application/Test_Pattern.d ./NandController/Application/Test_Pattern.o ./NandController/Application/Test_Pattern.su ./NandController/Application/Test_SinglePage(MultiplePattern).cyclo ./NandController/Application/Test_SinglePage(MultiplePattern).d ./NandController/Application/Test_SinglePage(MultiplePattern).o ./NandController/Application/Test_SinglePage(MultiplePattern).su ./NandController/Application/Test_SinglePage(RandomLoadProgram).cyclo ./NandController/Application/Test_SinglePage(RandomLoadProgram).d ./NandController/Application/Test_SinglePage(RandomLoadProgram).o ./NandController/Application/Test_SinglePage(RandomLoadProgram).su ./NandController/Application/Test_SinglePage.cyclo ./NandController/Application/Test_SinglePage.d ./NandController/Application/Test_SinglePage.o ./NandController/Application/Test_SinglePage.su

.PHONY: clean-NandController-2f-Application

