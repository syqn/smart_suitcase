################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/test/benchmark.c \
../middleware/mbedtls/programs/test/selftest.c \
../middleware/mbedtls/programs/test/ssl_cert_test.c \
../middleware/mbedtls/programs/test/udp_proxy.c 

OBJS += \
./middleware/mbedtls/programs/test/benchmark.o \
./middleware/mbedtls/programs/test/selftest.o \
./middleware/mbedtls/programs/test/ssl_cert_test.o \
./middleware/mbedtls/programs/test/udp_proxy.o 

C_DEPS += \
./middleware/mbedtls/programs/test/benchmark.d \
./middleware/mbedtls/programs/test/selftest.d \
./middleware/mbedtls/programs/test/ssl_cert_test.d \
./middleware/mbedtls/programs/test/udp_proxy.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/test/%.o: ../middleware/mbedtls/programs/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


