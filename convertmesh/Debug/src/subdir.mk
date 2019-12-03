################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/convert.cpp \
../src/error.cpp \
../src/matrix.cpp \
../src/mesh.cpp 

OBJS += \
./src/convert.o \
./src/error.o \
./src/matrix.o \
./src/mesh.o 

CPP_DEPS += \
./src/convert.d \
./src/error.d \
./src/matrix.d \
./src/mesh.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


