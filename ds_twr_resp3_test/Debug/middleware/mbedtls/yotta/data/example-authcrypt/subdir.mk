################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../middleware/mbedtls/yotta/data/example-authcrypt/main.cpp 

OBJS += \
./middleware/mbedtls/yotta/data/example-authcrypt/main.o 

CPP_DEPS += \
./middleware/mbedtls/yotta/data/example-authcrypt/main.d 


# Each subdirectory must supply rules for building sources it contributes
middleware/mbedtls/yotta/data/example-authcrypt/%.o: ../middleware/mbedtls/yotta/data/example-authcrypt/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C++ Compiler'
	arc-elf32-g++ -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -fno-exceptions -fno-rtti -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


