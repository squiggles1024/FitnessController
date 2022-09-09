################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/FitnessController_ApplicationLayer/FitnessController.c \
../Core/Src/FitnessController_ApplicationLayer/MAX30102.c \
../Core/Src/FitnessController_ApplicationLayer/MAX30102_Hardware.c 

OBJS += \
./Core/Src/FitnessController_ApplicationLayer/FitnessController.o \
./Core/Src/FitnessController_ApplicationLayer/MAX30102.o \
./Core/Src/FitnessController_ApplicationLayer/MAX30102_Hardware.o 

C_DEPS += \
./Core/Src/FitnessController_ApplicationLayer/FitnessController.d \
./Core/Src/FitnessController_ApplicationLayer/MAX30102.d \
./Core/Src/FitnessController_ApplicationLayer/MAX30102_Hardware.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/FitnessController_ApplicationLayer/%.o Core/Src/FitnessController_ApplicationLayer/%.su: ../Core/Src/FitnessController_ApplicationLayer/%.c Core/Src/FitnessController_ApplicationLayer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Core/Inc/FitnessController/BatteryService -I../Core/Inc/FitnessController/Controller_Parts -I../Core/Inc/FitnessController/DeviceInfoService -I../Core/Inc/FitnessController/HIDService -I../Core/Inc/FitnessController -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../BlueNRG-MS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Middlewares/ST/BlueNRG-MS/utils -I../Middlewares/ST/BlueNRG-MS/includes -I../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-FitnessController_ApplicationLayer

clean-Core-2f-Src-2f-FitnessController_ApplicationLayer:
	-$(RM) ./Core/Src/FitnessController_ApplicationLayer/FitnessController.d ./Core/Src/FitnessController_ApplicationLayer/FitnessController.o ./Core/Src/FitnessController_ApplicationLayer/FitnessController.su ./Core/Src/FitnessController_ApplicationLayer/MAX30102.d ./Core/Src/FitnessController_ApplicationLayer/MAX30102.o ./Core/Src/FitnessController_ApplicationLayer/MAX30102.su ./Core/Src/FitnessController_ApplicationLayer/MAX30102_Hardware.d ./Core/Src/FitnessController_ApplicationLayer/MAX30102_Hardware.o ./Core/Src/FitnessController_ApplicationLayer/MAX30102_Hardware.su

.PHONY: clean-Core-2f-Src-2f-FitnessController_ApplicationLayer

