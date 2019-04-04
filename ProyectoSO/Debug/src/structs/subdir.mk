################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/structs/Auto.c \
../src/structs/Este.c \
../src/structs/Oeste.c \
../src/structs/Puente.c 

OBJS += \
./src/structs/Auto.o \
./src/structs/Este.o \
./src/structs/Oeste.o \
./src/structs/Puente.o 

C_DEPS += \
./src/structs/Auto.d \
./src/structs/Este.d \
./src/structs/Oeste.d \
./src/structs/Puente.d 


# Each subdirectory must supply rules for building sources it contributes
src/structs/%.o: ../src/structs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


