################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/mbedtls/library/aes.c \
../middleware/mbedtls/library/aesni.c \
../middleware/mbedtls/library/arc4.c \
../middleware/mbedtls/library/asn1parse.c \
../middleware/mbedtls/library/asn1write.c \
../middleware/mbedtls/library/base64.c \
../middleware/mbedtls/library/bignum.c \
../middleware/mbedtls/library/blowfish.c \
../middleware/mbedtls/library/camellia.c \
../middleware/mbedtls/library/ccm.c \
../middleware/mbedtls/library/certs.c \
../middleware/mbedtls/library/cipher.c \
../middleware/mbedtls/library/cipher_wrap.c \
../middleware/mbedtls/library/cmac.c \
../middleware/mbedtls/library/ctr_drbg.c \
../middleware/mbedtls/library/debug.c \
../middleware/mbedtls/library/des.c \
../middleware/mbedtls/library/dhm.c \
../middleware/mbedtls/library/ecdh.c \
../middleware/mbedtls/library/ecdsa.c \
../middleware/mbedtls/library/ecjpake.c \
../middleware/mbedtls/library/ecp.c \
../middleware/mbedtls/library/ecp_curves.c \
../middleware/mbedtls/library/entropy.c \
../middleware/mbedtls/library/entropy_poll.c \
../middleware/mbedtls/library/error.c \
../middleware/mbedtls/library/gcm.c \
../middleware/mbedtls/library/havege.c \
../middleware/mbedtls/library/hmac_drbg.c \
../middleware/mbedtls/library/md.c \
../middleware/mbedtls/library/md2.c \
../middleware/mbedtls/library/md4.c \
../middleware/mbedtls/library/md5.c \
../middleware/mbedtls/library/md_wrap.c \
../middleware/mbedtls/library/memory_buffer_alloc.c \
../middleware/mbedtls/library/net_sockets.c \
../middleware/mbedtls/library/oid.c \
../middleware/mbedtls/library/padlock.c \
../middleware/mbedtls/library/pem.c \
../middleware/mbedtls/library/pk.c \
../middleware/mbedtls/library/pk_wrap.c \
../middleware/mbedtls/library/pkcs11.c \
../middleware/mbedtls/library/pkcs12.c \
../middleware/mbedtls/library/pkcs5.c \
../middleware/mbedtls/library/pkparse.c \
../middleware/mbedtls/library/pkwrite.c \
../middleware/mbedtls/library/platform.c \
../middleware/mbedtls/library/ripemd160.c \
../middleware/mbedtls/library/rsa.c \
../middleware/mbedtls/library/sha1.c \
../middleware/mbedtls/library/sha256.c \
../middleware/mbedtls/library/sha512.c \
../middleware/mbedtls/library/ssl_cache.c \
../middleware/mbedtls/library/ssl_ciphersuites.c \
../middleware/mbedtls/library/ssl_cli.c \
../middleware/mbedtls/library/ssl_cookie.c \
../middleware/mbedtls/library/ssl_srv.c \
../middleware/mbedtls/library/ssl_ticket.c \
../middleware/mbedtls/library/ssl_tls.c \
../middleware/mbedtls/library/threading.c \
../middleware/mbedtls/library/timing.c \
../middleware/mbedtls/library/version.c \
../middleware/mbedtls/library/version_features.c \
../middleware/mbedtls/library/x509.c \
../middleware/mbedtls/library/x509_create.c \
../middleware/mbedtls/library/x509_crl.c \
../middleware/mbedtls/library/x509_crt.c \
../middleware/mbedtls/library/x509_csr.c \
../middleware/mbedtls/library/x509write_crt.c \
../middleware/mbedtls/library/x509write_csr.c \
../middleware/mbedtls/library/xtea.c 

OBJS += \
./middleware/mbedtls/library/aes.o \
./middleware/mbedtls/library/aesni.o \
./middleware/mbedtls/library/arc4.o \
./middleware/mbedtls/library/asn1parse.o \
./middleware/mbedtls/library/asn1write.o \
./middleware/mbedtls/library/base64.o \
./middleware/mbedtls/library/bignum.o \
./middleware/mbedtls/library/blowfish.o \
./middleware/mbedtls/library/camellia.o \
./middleware/mbedtls/library/ccm.o \
./middleware/mbedtls/library/certs.o \
./middleware/mbedtls/library/cipher.o \
./middleware/mbedtls/library/cipher_wrap.o \
./middleware/mbedtls/library/cmac.o \
./middleware/mbedtls/library/ctr_drbg.o \
./middleware/mbedtls/library/debug.o \
./middleware/mbedtls/library/des.o \
./middleware/mbedtls/library/dhm.o \
./middleware/mbedtls/library/ecdh.o \
./middleware/mbedtls/library/ecdsa.o \
./middleware/mbedtls/library/ecjpake.o \
./middleware/mbedtls/library/ecp.o \
./middleware/mbedtls/library/ecp_curves.o \
./middleware/mbedtls/library/entropy.o \
./middleware/mbedtls/library/entropy_poll.o \
./middleware/mbedtls/library/error.o \
./middleware/mbedtls/library/gcm.o \
./middleware/mbedtls/library/havege.o \
./middleware/mbedtls/library/hmac_drbg.o \
./middleware/mbedtls/library/md.o \
./middleware/mbedtls/library/md2.o \
./middleware/mbedtls/library/md4.o \
./middleware/mbedtls/library/md5.o \
./middleware/mbedtls/library/md_wrap.o \
./middleware/mbedtls/library/memory_buffer_alloc.o \
./middleware/mbedtls/library/net_sockets.o \
./middleware/mbedtls/library/oid.o \
./middleware/mbedtls/library/padlock.o \
./middleware/mbedtls/library/pem.o \
./middleware/mbedtls/library/pk.o \
./middleware/mbedtls/library/pk_wrap.o \
./middleware/mbedtls/library/pkcs11.o \
./middleware/mbedtls/library/pkcs12.o \
./middleware/mbedtls/library/pkcs5.o \
./middleware/mbedtls/library/pkparse.o \
./middleware/mbedtls/library/pkwrite.o \
./middleware/mbedtls/library/platform.o \
./middleware/mbedtls/library/ripemd160.o \
./middleware/mbedtls/library/rsa.o \
./middleware/mbedtls/library/sha1.o \
./middleware/mbedtls/library/sha256.o \
./middleware/mbedtls/library/sha512.o \
./middleware/mbedtls/library/ssl_cache.o \
./middleware/mbedtls/library/ssl_ciphersuites.o \
./middleware/mbedtls/library/ssl_cli.o \
./middleware/mbedtls/library/ssl_cookie.o \
./middleware/mbedtls/library/ssl_srv.o \
./middleware/mbedtls/library/ssl_ticket.o \
./middleware/mbedtls/library/ssl_tls.o \
./middleware/mbedtls/library/threading.o \
./middleware/mbedtls/library/timing.o \
./middleware/mbedtls/library/version.o \
./middleware/mbedtls/library/version_features.o \
./middleware/mbedtls/library/x509.o \
./middleware/mbedtls/library/x509_create.o \
./middleware/mbedtls/library/x509_crl.o \
./middleware/mbedtls/library/x509_crt.o \
./middleware/mbedtls/library/x509_csr.o \
./middleware/mbedtls/library/x509write_crt.o \
./middleware/mbedtls/library/x509write_csr.o \
./middleware/mbedtls/library/xtea.o 

C_DEPS += \
./middleware/mbedtls/library/aes.d \
./middleware/mbedtls/library/aesni.d \
./middleware/mbedtls/library/arc4.d \
./middleware/mbedtls/library/asn1parse.d \
./middleware/mbedtls/library/asn1write.d \
./middleware/mbedtls/library/base64.d \
./middleware/mbedtls/library/bignum.d \
./middleware/mbedtls/library/blowfish.d \
./middleware/mbedtls/library/camellia.d \
./middleware/mbedtls/library/ccm.d \
./middleware/mbedtls/library/certs.d \
./middleware/mbedtls/library/cipher.d \
./middleware/mbedtls/library/cipher_wrap.d \
./middleware/mbedtls/library/cmac.d \
./middleware/mbedtls/library/ctr_drbg.d \
./middleware/mbedtls/library/debug.d \
./middleware/mbedtls/library/des.d \
./middleware/mbedtls/library/dhm.d \
./middleware/mbedtls/library/ecdh.d \
./middleware/mbedtls/library/ecdsa.d \
./middleware/mbedtls/library/ecjpake.d \
./middleware/mbedtls/library/ecp.d \
./middleware/mbedtls/library/ecp_curves.d \
./middleware/mbedtls/library/entropy.d \
./middleware/mbedtls/library/entropy_poll.d \
./middleware/mbedtls/library/error.d \
./middleware/mbedtls/library/gcm.d \
./middleware/mbedtls/library/havege.d \
./middleware/mbedtls/library/hmac_drbg.d \
./middleware/mbedtls/library/md.d \
./middleware/mbedtls/library/md2.d \
./middleware/mbedtls/library/md4.d \
./middleware/mbedtls/library/md5.d \
./middleware/mbedtls/library/md_wrap.d \
./middleware/mbedtls/library/memory_buffer_alloc.d \
./middleware/mbedtls/library/net_sockets.d \
./middleware/mbedtls/library/oid.d \
./middleware/mbedtls/library/padlock.d \
./middleware/mbedtls/library/pem.d \
./middleware/mbedtls/library/pk.d \
./middleware/mbedtls/library/pk_wrap.d \
./middleware/mbedtls/library/pkcs11.d \
./middleware/mbedtls/library/pkcs12.d \
./middleware/mbedtls/library/pkcs5.d \
./middleware/mbedtls/library/pkparse.d \
./middleware/mbedtls/library/pkwrite.d \
./middleware/mbedtls/library/platform.d \
./middleware/mbedtls/library/ripemd160.d \
./middleware/mbedtls/library/rsa.d \
./middleware/mbedtls/library/sha1.d \
./middleware/mbedtls/library/sha256.d \
./middleware/mbedtls/library/sha512.d \
./middleware/mbedtls/library/ssl_cache.d \
./middleware/mbedtls/library/ssl_ciphersuites.d \
./middleware/mbedtls/library/ssl_cli.d \
./middleware/mbedtls/library/ssl_cookie.d \
./middleware/mbedtls/library/ssl_srv.d \
./middleware/mbedtls/library/ssl_ticket.d \
./middleware/mbedtls/library/ssl_tls.d \
./middleware/mbedtls/library/threading.d \
./middleware/mbedtls/library/timing.d \
./middleware/mbedtls/library/version.d \
./middleware/mbedtls/library/version_features.d \
./middleware/mbedtls/library/x509.d \
./middleware/mbedtls/library/x509_create.d \
./middleware/mbedtls/library/x509_crl.d \
./middleware/mbedtls/library/x509_crt.d \
./middleware/mbedtls/library/x509_csr.d \
./middleware/mbedtls/library/x509write_crt.d \
./middleware/mbedtls/library/x509write_csr.d \
./middleware/mbedtls/library/xtea.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/library/%.o: ../middleware/mbedtls/library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


