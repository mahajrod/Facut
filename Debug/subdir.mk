################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../argp.c \
../main\ (copy).c \
../main.c 

OBJS += \
./argp.o \
./main\ (copy).o \
./main.o 

C_DEPS += \
./argp.d \
./main\ (copy).d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -O0 -g -lz -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main\ (copy).o: ../main\ (copy).c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -O0 -g -lz -MMD -MP -MF"main (copy).d" -MT"main\ (copy).d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


