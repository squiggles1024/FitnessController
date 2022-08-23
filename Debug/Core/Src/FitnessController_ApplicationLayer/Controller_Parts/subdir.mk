################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/FitnessController_ApplicationLayer/Controller_Parts/analog_stick.c \
../Core/Src/FitnessController_ApplicationLayer/Controller_Parts/button.c \
../Core/Src/FitnessController_ApplicationLayer/Controller_Parts/trigger.c 

OBJS += \
./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/analog_stick.o \
./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/button.o \
./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/trigger.o 

C_DEPS += \
./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/analog_stick.d \
./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/button.d \
./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/trigger.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/FitnessController_ApplicationLayer/Controller_Parts/%.o Core/Src/FitnessController_ApplicationLayer/Controller_Parts/%.su: ../Core/Src/FitnessController_ApplicationLayer/Controller_Parts/%.c Core/Src/FitnessController_ApplicationLayer/Controller_Parts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Core/Inc/FitnessController/BatteryService -I../Core/Inc/FitnessController/Controller_Parts -I../Core/Inc/FitnessController/DeviceInfoService -I../Core/Inc/FitnessController/HIDService -I../Core/Inc/FitnessController -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../BlueNRG-MS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Middlewares/ST/BlueNRG-MS/utils -I../Middlewares/ST/BlueNRG-MS/includes -I../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-FitnessController_ApplicationLayer-2f-Controller_Parts

clean-Core-2f-Src-2f-FitnessController_ApplicationLayer-2f-Controller_Parts:
	-$(RM) ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/analog_stick.d ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/analog_stick.o ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/analog_stick.su ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/button.d ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/button.o ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/button.su ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/trigger.d ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/trigger.o ./Core/Src/FitnessController_ApplicationLayer/Controller_Parts/trigger.su

.PHONY: clean-Core-2f-Src-2f-FitnessController_ApplicationLayer-2f-Controller_Parts

