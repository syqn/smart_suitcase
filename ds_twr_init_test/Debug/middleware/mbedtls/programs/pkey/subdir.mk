################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/programs/pkey/dh_client.c \
../middleware/mbedtls/programs/pkey/dh_genprime.c \
../middleware/mbedtls/programs/pkey/dh_server.c \
../middleware/mbedtls/programs/pkey/ecdh_curve25519.c \
../middleware/mbedtls/programs/pkey/ecdsa.c \
../middleware/mbedtls/programs/pkey/gen_key.c \
../middleware/mbedtls/programs/pkey/key_app.c \
../middleware/mbedtls/programs/pkey/key_app_writer.c \
../middleware/mbedtls/programs/pkey/mpi_demo.c \
../middleware/mbedtls/programs/pkey/pk_decrypt.c \
../middleware/mbedtls/programs/pkey/pk_encrypt.c \
../middleware/mbedtls/programs/pkey/pk_sign.c \
../middleware/mbedtls/programs/pkey/pk_verify.c \
../middleware/mbedtls/programs/pkey/rsa_decrypt.c \
../middleware/mbedtls/programs/pkey/rsa_encrypt.c \
../middleware/mbedtls/programs/pkey/rsa_genkey.c \
../middleware/mbedtls/programs/pkey/rsa_sign.c \
../middleware/mbedtls/programs/pkey/rsa_sign_pss.c \
../middleware/mbedtls/programs/pkey/rsa_verify.c \
../middleware/mbedtls/programs/pkey/rsa_verify_pss.c 

OBJS += \
./middleware/mbedtls/programs/pkey/dh_client.o \
./middleware/mbedtls/programs/pkey/dh_genprime.o \
./middleware/mbedtls/programs/pkey/dh_server.o \
./middleware/mbedtls/programs/pkey/ecdh_curve25519.o \
./middleware/mbedtls/programs/pkey/ecdsa.o \
./middleware/mbedtls/programs/pkey/gen_key.o \
./middleware/mbedtls/programs/pkey/key_app.o \
./middleware/mbedtls/programs/pkey/key_app_writer.o \
./middleware/mbedtls/programs/pkey/mpi_demo.o \
./middleware/mbedtls/programs/pkey/pk_decrypt.o \
./middleware/mbedtls/programs/pkey/pk_encrypt.o \
./middleware/mbedtls/programs/pkey/pk_sign.o \
./middleware/mbedtls/programs/pkey/pk_verify.o \
./middleware/mbedtls/programs/pkey/rsa_decrypt.o \
./middleware/mbedtls/programs/pkey/rsa_encrypt.o \
./middleware/mbedtls/programs/pkey/rsa_genkey.o \
./middleware/mbedtls/programs/pkey/rsa_sign.o \
./middleware/mbedtls/programs/pkey/rsa_sign_pss.o \
./middleware/mbedtls/programs/pkey/rsa_verify.o \
./middleware/mbedtls/programs/pkey/rsa_verify_pss.o 

C_DEPS += \
./middleware/mbedtls/programs/pkey/dh_client.d \
./middleware/mbedtls/programs/pkey/dh_genprime.d \
./middleware/mbedtls/programs/pkey/dh_server.d \
./middleware/mbedtls/programs/pkey/ecdh_curve25519.d \
./middleware/mbedtls/programs/pkey/ecdsa.d \
./middleware/mbedtls/programs/pkey/gen_key.d \
./middleware/mbedtls/programs/pkey/key_app.d \
./middleware/mbedtls/programs/pkey/key_app_writer.d \
./middleware/mbedtls/programs/pkey/mpi_demo.d \
./middleware/mbedtls/programs/pkey/pk_decrypt.d \
./middleware/mbedtls/programs/pkey/pk_encrypt.d \
./middleware/mbedtls/programs/pkey/pk_sign.d \
./middleware/mbedtls/programs/pkey/pk_verify.d \
./middleware/mbedtls/programs/pkey/rsa_decrypt.d \
./middleware/mbedtls/programs/pkey/rsa_encrypt.d \
./middleware/mbedtls/programs/pkey/rsa_genkey.d \
./middleware/mbedtls/programs/pkey/rsa_sign.d \
./middleware/mbedtls/programs/pkey/rsa_sign_pss.d \
./middleware/mbedtls/programs/pkey/rsa_verify.d \
./middleware/mbedtls/programs/pkey/rsa_verify_pss.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/programs/pkey/%.o: ../middleware/mbedtls/programs/pkey/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


