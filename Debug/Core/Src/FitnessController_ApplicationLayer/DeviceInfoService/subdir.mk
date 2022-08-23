################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/DeviceInfoService.c 

OBJS += \
./Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/DeviceInfoService.o 

C_DEPS += \
./Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/DeviceInfoService.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/%.o Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/%.su: ../Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/%.c Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Core/Inc/FitnessController/BatteryService -I../Core/Inc/FitnessController/Controller_Parts -I../Core/Inc/FitnessController/DeviceInfoService -I../Core/Inc/FitnessController/HIDService -I../Core/Inc/FitnessController -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../BlueNRG-MS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Middlewares/ST/BlueNRG-MS/utils -I../Middlewares/ST/BlueNRG-MS/includes -I../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-FitnessController_ApplicationLayer-2f-DeviceInfoService

clean-Core-2f-Src-2f-FitnessController_ApplicationLayer-2f-DeviceInfoService:
	-$(RM) ./Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/DeviceInfoService.d ./Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/DeviceInfoService.o ./Core/Src/FitnessController_ApplicationLayer/DeviceInfoService/DeviceInfoService.su

.PHONY: clean-Core-2f-Src-2f-FitnessController_ApplicationLayer-2f-DeviceInfoService

