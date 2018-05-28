################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/util/pem2der.c \
../middleware/mbedtls/programs/util/strerror.c 

OBJS += \
./middleware/mbedtls/programs/util/pem2der.o \
./middleware/mbedtls/programs/util/strerror.o 

C_DEPS += \
./middleware/mbedtls/programs/util/pem2der.d \
./middleware/mbedtls/programs/util/strerror.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/util/%.o: ../middleware/mbedtls/programs/util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


