################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src\LiquidCrystal.cpp 

LINK_OBJ += \
.\libraries\LiquidCrystal\src\LiquidCrystal.cpp.o 

CPP_DEPS += \
.\libraries\LiquidCrystal\src\LiquidCrystal.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\LiquidCrystal\src\LiquidCrystal.cpp.o: D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src\LiquidCrystal.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\mega" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\DallasTemperature\3.8.0" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\HCSR04\1.1.0\src" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\Keypad\3.1.1\src" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\OneWire\2.3.5" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


