################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/CCSTheia/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/Administrator/workspace_ccstheia/IIC_OLED" -I"C:/Users/Administrator/workspace_ccstheia/IIC_OLED/Debug" -I"D:/CCSTheia/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/CCSTheia/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-838690529: ../IIC_OLED.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/CCSTheia/ccs/utils/sysconfig_1.20.0/sysconfig_cli.bat" --script "C:/Users/Administrator/workspace_ccstheia/IIC_OLED/IIC_OLED.syscfg" -o "." -s "D:/CCSTheia/mspm0_sdk_2_01_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-838690529 ../IIC_OLED.syscfg
device.opt: build-838690529
device.cmd.genlibs: build-838690529
ti_msp_dl_config.c: build-838690529
ti_msp_dl_config.h: build-838690529

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/CCSTheia/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/Administrator/workspace_ccstheia/IIC_OLED" -I"C:/Users/Administrator/workspace_ccstheia/IIC_OLED/Debug" -I"D:/CCSTheia/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/CCSTheia/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: D:/CCSTheia/mspm0_sdk_2_01_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/CCSTheia/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/Administrator/workspace_ccstheia/IIC_OLED" -I"C:/Users/Administrator/workspace_ccstheia/IIC_OLED/Debug" -I"D:/CCSTheia/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"D:/CCSTheia/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


