################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/msp430_4.2.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./src/testUART.obj" \
"./src/UCS_INIT.obj" \
"./src/UART.obj" \
"./src/Turbidity.obj" \
"./src/PH-T.obj" \
"./src/LCD1602.obj" \
"./src/LCD12864.obj" \
"./src/KEY_SIG.obj" \
"./src/DS18B20.obj" \
"./src/DAC8571.obj" \
"./src/BLUETOOTH.obj" \
"./src/ADS1118.obj" \
"./src/ADC12_INIT.obj" \
"./main.obj" \
"../lnk_msp430f5529.cmd" \
-l"libmath.a" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: WaterMonitor.out

# Tool invocations
WaterMonitor.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmspx --abi=coffabi --advice:power="all" -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal -z -m"WaterMonitor.map" --heap_size=160 --stack_size=160 --use_hw_mpy=F5 -i"C:/ti/ccsv5/ccs_base/msp430/include" -i"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/lib" -i"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/include" -i"C:/ti/ccsv5/ccs_base/msp430/lib" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="WaterMonitor_linkInfo.xml" --rom_model -o "WaterMonitor.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "WaterMonitor.out"
	-$(RM) "main.pp" "src\ADC12_INIT.pp" "src\ADS1118.pp" "src\BLUETOOTH.pp" "src\DAC8571.pp" "src\DS18B20.pp" "src\KEY_SIG.pp" "src\LCD12864.pp" "src\LCD1602.pp" "src\PH-T.pp" "src\Turbidity.pp" "src\UART.pp" "src\UCS_INIT.pp" "src\testUART.pp" 
	-$(RM) "main.obj" "src\ADC12_INIT.obj" "src\ADS1118.obj" "src\BLUETOOTH.obj" "src\DAC8571.obj" "src\DS18B20.obj" "src\KEY_SIG.obj" "src\LCD12864.obj" "src\LCD1602.obj" "src\PH-T.obj" "src\Turbidity.obj" "src\UART.obj" "src\UCS_INIT.obj" "src\testUART.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

