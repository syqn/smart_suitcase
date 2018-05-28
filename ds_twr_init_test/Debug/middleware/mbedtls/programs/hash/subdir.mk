################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/hash/generic_sum.c \
../middleware/mbedtls/programs/hash/hello.c 

OBJS += \
./middleware/mbedtls/programs/hash/generic_sum.o \
./middleware/mbedtls/programs/hash/hello.o 

C_DEPS += \
./middleware/mbedtls/programs/hash/generic_sum.d \
./middleware/mbedtls/programs/hash/hello.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/hash/%.o: ../middleware/mbedtls/programs/hash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


