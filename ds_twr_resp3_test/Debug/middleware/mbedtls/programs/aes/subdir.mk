################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/aes/aescrypt2.c \
../middleware/mbedtls/programs/aes/crypt_and_hash.c 

OBJS += \
./middleware/mbedtls/programs/aes/aescrypt2.o \
./middleware/mbedtls/programs/aes/crypt_and_hash.o 

C_DEPS += \
./middleware/mbedtls/programs/aes/aescrypt2.d \
./middleware/mbedtls/programs/aes/crypt_and_hash.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/aes/%.o: ../middleware/mbedtls/programs/aes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


