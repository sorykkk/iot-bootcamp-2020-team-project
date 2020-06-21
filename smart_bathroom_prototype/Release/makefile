################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := -del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\OneWire\subdir.mk
-include libraries\LiquidCrystal\src\subdir.mk
-include libraries\Keypad\src\subdir.mk
-include libraries\HCSR04\src\subdir.mk
-include libraries\DallasTemperature\subdir.mk
-include dd_ultrasonic\subdir.mk
-include dd_pump\subdir.mk
-include dd_keypad\subdir.mk
-include dd_ds18b20_temp\subdir.mk
-include core\core\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
D:\Sloeber_files\sloeber-workspace\smart_bathroom_prototype\Release\arduino.ar \

ELF += \
smart_bathroom_prototype.elf \

HEX += \
smart_bathroom_prototype.hex \


# All Target
all: smart_bathroom_prototype

# Tool invocations
smart_bathroom_prototype: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-size" -A "D:\Sloeber_files\sloeber-workspace\smart_bathroom_prototype\Release/smart_bathroom_prototype.elf"
	@echo 'Finished building target: $@'
	@echo ' '

D:\Sloeber_files\sloeber-workspace\smart_bathroom_prototype\Release\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-gcc-ar" rcs     D:\Sloeber_files\sloeber-workspace\smart_bathroom_prototype\Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

smart_bathroom_prototype.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"D:\Sloeber_files\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-gcc" -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections,--relax -mmcu=atmega2560  -o "D:\Sloeber_files\sloeber-workspace\smart_bathroom_prototype\Release/smart_bathroom_prototype.elf"   $(LINK_OBJ)   D:\Sloeber_files\sloeber-workspace\smart_bathroom_prototype\Release/arduino.ar  "-LD:\Sloeber_files\sloeber-workspace\smart_bathroom_prototype\Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

smart_bathroom_prototype.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ..\makefile.targets
