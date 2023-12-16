################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Leeson_4_lab_1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Leeson_4_lab_1.list \

OBJCOPY_BIN += \
Leeson_4_lab_1.bin \


# All Target
all: Leeson_4_lab_1.elf secondary-outputs

# Tool invocations
Leeson_4_lab_1.elf: $(OBJS) $(USER_OBJS) D:\Keroll\Git\Embedded-Systems-Diploma\Unit\ 6\ MCU\ Architecture\Lesson\ 4\Lab\ 1\Leeson_4_lab_1\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Leeson_4_lab_1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Keroll\Git\Embedded-Systems-Diploma\Unit 6 MCU Architecture\Lesson 4\Lab 1\Leeson_4_lab_1\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Leeson_4_lab_1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Leeson_4_lab_1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Leeson_4_lab_1.list"
	@echo 'Finished building: $@'
	@echo ' '

Leeson_4_lab_1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Leeson_4_lab_1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
