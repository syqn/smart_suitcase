################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/peripheral/adc/ad7991/ad7991.c 

OBJS += \
./device/peripheral/adc/ad7991/ad7991.o 

C_DEPS += \
./device/peripheral/adc/ad7991/ad7991.d 


# Each subdirectory must supply rules for building sources it contributes
device/peripheral/adc/ad7991/%.o: ../device/peripheral/adc/ad7991/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


