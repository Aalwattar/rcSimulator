################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/argparse.c \
../src/data.c \
../src/dfgTemplate.c \
../src/displayResults.c \
../src/drawTaskAllocation.c \
../src/io.c \
../src/processors.c \
../src/queue.c \
../src/rcsSimulator.c \
../src/reconfiguration.c \
../src/schedulers.c 

OBJS += \
./src/argparse.o \
./src/data.o \
./src/dfgTemplate.o \
./src/displayResults.o \
./src/drawTaskAllocation.o \
./src/io.o \
./src/processors.o \
./src/queue.o \
./src/rcsSimulator.o \
./src/reconfiguration.o \
./src/schedulers.o 

C_DEPS += \
./src/argparse.d \
./src/data.d \
./src/dfgTemplate.d \
./src/displayResults.d \
./src/drawTaskAllocation.d \
./src/io.d \
./src/processors.d \
./src/queue.d \
./src/rcsSimulator.d \
./src/reconfiguration.d \
./src/schedulers.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/export/home/grad/aalwatta/include -I../../include -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


