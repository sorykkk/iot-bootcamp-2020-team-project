################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\dd_keypad\keypad_lcd.cpp 

LINK_OBJ += \
.\dd_keypad\keypad_lcd.cpp.o 

CPP_DEPS += \
.\dd_keypad\keypad_lcd.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
dd_keypad\keypad_lcd.cpp.o: ..\dd_keypad\keypad_lcd.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\mega" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\DallasTemperature\3.8.0" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\HCSR04\1.1.0\src" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\Keypad\3.1.1\src" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"D:\Sloeber_files\Sloeber\arduinoPlugin\libraries\OneWire\2.3.5" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


