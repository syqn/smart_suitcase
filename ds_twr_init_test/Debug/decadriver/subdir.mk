################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../decadriver/deca_device.c \
../decadriver/deca_params_init.c \
../decadriver/deca_range_tables.c 

OBJS += \
./decadriver/deca_device.o \
./decadriver/deca_params_init.o \
./decadriver/deca_range_tables.o 

C_DEPS += \
./decadriver/deca_device.d \
./decadriver/deca_params_init.d \
./decadriver/deca_range_tables.d 


# Each subdirectory must supply rules for building sources it contributes
decadriver/%.o: ../decadriver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARC ELF32 GCC C Compiler'
	arc-elf32-gcc -mcpu=em -mlittle-endian -mmpy-option=0 -g3 -gdwarf-2 -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


