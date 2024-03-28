################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/FPEC/FPEC_program.c 

OBJS += \
./Core/FPEC/FPEC_program.o 

C_DEPS += \
./Core/FPEC/FPEC_program.d 


# Each subdirectory must supply rules for building sources it contributes
Core/FPEC/%.o Core/FPEC/%.su Core/FPEC/%.cyclo: ../Core/FPEC/%.c Core/FPEC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Mahmoud/Downloads/CAN/Core/GPIO" -I"C:/Users/Mahmoud/Downloads/CAN/Core/LIB" -I"C:/Users/Mahmoud/Downloads/CAN/Core/NVIC" -I"C:/Users/Mahmoud/Downloads/CAN/Core/UART" -I"C:/Users/Mahmoud/Downloads/CAN/Core/CAN" -I"C:/Users/Mahmoud/Downloads/CAN/Core/AFIO" -I"C:/Users/Mahmoud/Downloads/CAN/Core/CAN_TP" -I"C:/Users/Mahmoud/Downloads/CAN/Core/USRT_MANAGE" -I"C:/Users/Mahmoud/Downloads/CAN/Core/UDSM" -I"C:/Users/Mahmoud/Downloads/CAN/Core/SYSTICK" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-FPEC

clean-Core-2f-FPEC:
	-$(RM) ./Core/FPEC/FPEC_program.cyclo ./Core/FPEC/FPEC_program.d ./Core/FPEC/FPEC_program.o ./Core/FPEC/FPEC_program.su

.PHONY: clean-Core-2f-FPEC

