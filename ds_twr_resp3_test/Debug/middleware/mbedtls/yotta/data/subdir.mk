################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/yotta/data/entropy_hardware_poll.c 

OBJS += \
./middleware/mbedtls/yotta/data/entropy_hardware_poll.o 

C_DEPS += \
./middleware/mbedtls/yotta/data/entropy_hardware_poll.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/yotta/data/%.o: ../middleware/mbedtls/yotta/data/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


