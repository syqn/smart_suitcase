################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/ssl/dtls_client.c \
../middleware/mbedtls/programs/ssl/dtls_server.c \
../middleware/mbedtls/programs/ssl/mini_client.c \
../middleware/mbedtls/programs/ssl/ssl_client1.c \
../middleware/mbedtls/programs/ssl/ssl_client2.c \
../middleware/mbedtls/programs/ssl/ssl_fork_server.c \
../middleware/mbedtls/programs/ssl/ssl_mail_client.c \
../middleware/mbedtls/programs/ssl/ssl_pthread_server.c \
../middleware/mbedtls/programs/ssl/ssl_server.c \
../middleware/mbedtls/programs/ssl/ssl_server2.c 

OBJS += \
./middleware/mbedtls/programs/ssl/dtls_client.o \
./middleware/mbedtls/programs/ssl/dtls_server.o \
./middleware/mbedtls/programs/ssl/mini_client.o \
./middleware/mbedtls/programs/ssl/ssl_client1.o \
./middleware/mbedtls/programs/ssl/ssl_client2.o \
./middleware/mbedtls/programs/ssl/ssl_fork_server.o \
./middleware/mbedtls/programs/ssl/ssl_mail_client.o \
./middleware/mbedtls/programs/ssl/ssl_pthread_server.o \
./middleware/mbedtls/programs/ssl/ssl_server.o \
./middleware/mbedtls/programs/ssl/ssl_server2.o 

C_DEPS += \
./middleware/mbedtls/programs/ssl/dtls_client.d \
./middleware/mbedtls/programs/ssl/dtls_server.d \
./middleware/mbedtls/programs/ssl/mini_client.d \
./middleware/mbedtls/programs/ssl/ssl_client1.d \
./middleware/mbedtls/programs/ssl/ssl_client2.d \
./middleware/mbedtls/programs/ssl/ssl_fork_server.d \
./middleware/mbedtls/programs/ssl/ssl_mail_client.d \
./middleware/mbedtls/programs/ssl/ssl_pthread_server.d \
./middleware/mbedtls/programs/ssl/ssl_server.d \
./middleware/mbedtls/programs/ssl/ssl_server2.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/ssl/%.o: ../middleware/mbedtls/programs/ssl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


