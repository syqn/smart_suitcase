################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/x509/cert_app.c \
../middleware/mbedtls/programs/x509/cert_req.c \
../middleware/mbedtls/programs/x509/cert_write.c \
../middleware/mbedtls/programs/x509/crl_app.c \
../middleware/mbedtls/programs/x509/req_app.c 

OBJS += \
./middleware/mbedtls/programs/x509/cert_app.o \
./middleware/mbedtls/programs/x509/cert_req.o \
./middleware/mbedtls/programs/x509/cert_write.o \
./middleware/mbedtls/programs/x509/crl_app.o \
./middleware/mbedtls/programs/x509/req_app.o 

C_DEPS += \
./middleware/mbedtls/programs/x509/cert_app.d \
./middleware/mbedtls/programs/x509/cert_req.d \
./middleware/mbedtls/programs/x509/cert_write.d \
./middleware/mbedtls/programs/x509/crl_app.d \
./middleware/mbedtls/programs/x509/req_app.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/x509/%.o: ../middleware/mbedtls/programs/x509/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


