################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/deca_mutex.c \
../platform/deca_sleep.c \
../platform/deca_spi.c \
../platform/port.c 

OBJS += \
./platform/deca_mutex.o \
./platform/deca_sleep.o \
./platform/deca_spi.o \
./platform/port.o 

C_DEPS += \
./platform/deca_mutex.d \
./platform/deca_sleep.d \
./platform/deca_spi.d \
./platform/port.d 


# Each subdirectory must supply rules for building sources it contributes
platform/%.o: ../platform/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


