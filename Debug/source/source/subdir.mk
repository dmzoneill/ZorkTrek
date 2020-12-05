################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/source/Battle.cpp \
../source/source/CelestialBody.cpp \
../source/source/Command.cpp \
../source/source/CommandWords.cpp \
../source/source/Main.cpp \
../source/source/Maze.cpp \
../source/source/Moon.cpp \
../source/source/PVEEntity.cpp \
../source/source/Parser.cpp \
../source/source/Planet.cpp \
../source/source/SdlGLMap.cpp \
../source/source/SolarSystem.cpp \
../source/source/StarTrekEntities.cpp \
../source/source/Starship.cpp \
../source/source/ZorkTrek.cpp \
../source/source/ZorkTrekLib.cpp 

OBJS += \
./source/source/Battle.o \
./source/source/CelestialBody.o \
./source/source/Command.o \
./source/source/CommandWords.o \
./source/source/Main.o \
./source/source/Maze.o \
./source/source/Moon.o \
./source/source/PVEEntity.o \
./source/source/Parser.o \
./source/source/Planet.o \
./source/source/SdlGLMap.o \
./source/source/SolarSystem.o \
./source/source/StarTrekEntities.o \
./source/source/Starship.o \
./source/source/ZorkTrek.o \
./source/source/ZorkTrekLib.o 

CPP_DEPS += \
./source/source/Battle.d \
./source/source/CelestialBody.d \
./source/source/Command.d \
./source/source/CommandWords.d \
./source/source/Main.d \
./source/source/Maze.d \
./source/source/Moon.d \
./source/source/PVEEntity.d \
./source/source/Parser.d \
./source/source/Planet.d \
./source/source/SdlGLMap.d \
./source/source/SolarSystem.d \
./source/source/StarTrekEntities.d \
./source/source/Starship.d \
./source/source/ZorkTrek.d \
./source/source/ZorkTrekLib.d 


# Each subdirectory must supply rules for building sources it contributes
source/source/%.o: ../source/source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


