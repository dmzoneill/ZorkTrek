################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/doc/snippets/threading/createJoin.cpp \
../source/doc/snippets/threading/multipleWithJoinMutex.cpp \
../source/doc/snippets/threading/mutexConditionLock.cpp \
../source/doc/snippets/threading/mutexLock.cpp 

OBJS += \
./source/doc/snippets/threading/createJoin.o \
./source/doc/snippets/threading/multipleWithJoinMutex.o \
./source/doc/snippets/threading/mutexConditionLock.o \
./source/doc/snippets/threading/mutexLock.o 

CPP_DEPS += \
./source/doc/snippets/threading/createJoin.d \
./source/doc/snippets/threading/multipleWithJoinMutex.d \
./source/doc/snippets/threading/mutexConditionLock.d \
./source/doc/snippets/threading/mutexLock.d 


# Each subdirectory must supply rules for building sources it contributes
source/doc/snippets/threading/%.o: ../source/doc/snippets/threading/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


