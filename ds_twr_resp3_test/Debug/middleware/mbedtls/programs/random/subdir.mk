################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/random/gen_entropy.c \
../middleware/mbedtls/programs/random/gen_random_ctr_drbg.c \
../middleware/mbedtls/programs/random/gen_random_havege.c 

OBJS += \
./middleware/mbedtls/programs/random/gen_entropy.o \
./middleware/mbedtls/programs/random/gen_random_ctr_drbg.o \
./middleware/mbedtls/programs/random/gen_random_havege.o 

C_DEPS += \
./middleware/mbedtls/programs/random/gen_entropy.d \
./middleware/mbedtls/programs/random/gen_random_ctr_drbg.d \
./middleware/mbedtls/programs/random/gen_random_havege.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/random/%.o: ../middleware/mbedtls/programs/random/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


