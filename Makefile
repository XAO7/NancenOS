TARGET_MCU ?= stm32f411ret6
TARGET_BOARD ?= frypi

BUILD_DIR = build

SRC_DIRS = . kernel mcu/$(TARGET_MCU) drivers/$(TARGET_MCU) board/$(TARGET_BOARD) utils utils/$(TARGET_MCU)

INCLUDES = -I. -Ikernel -Imcu/$(TARGET_MCU) -Idrivers/$(TARGET_MCU) -Iboard/$(TARGET_BOARD) -Iutils -Iutils/$(TARGET_MCU)

OUTPUT = $(BUILD_DIR)/program

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CC_FLAGS = -Werror -mcpu=cortex-m4 -mthumb -Os -nostdlib -fno-builtin $(INCLUDES)
AS_FLAGS = -mcpu=cortex-m4 -mthumb
LD_FLAGS = -nostdlib -T mcu/$(TARGET_MCU)/linker.ld -Map=$(OUTPUT).map -Llib

SOURCES_C = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))
SOURCES_ASM = $(wildcard $(addsuffix /*.s, $(SRC_DIRS)))

OBJECTS_C = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCES_C))
OBJECTS_ASM = $(patsubst %.s, $(BUILD_DIR)/%.o, $(SOURCES_ASM))

OBJECTS = $(OBJECTS_C) $(OBJECTS_ASM)

.PHONY: auto_clean all clean flash cat gdb-server gdb

auto_clean:
	@trap 'make clean' ERR; make all

all: $(OUTPUT).bin

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) $< -o $@

$(OUTPUT).elf: $(OBJECTS)
	$(LD) -o $@ $^ $(LD_FLAGS)

$(OUTPUT).bin: $(OUTPUT).elf
	$(OBJCOPY) -O binary $(OUTPUT).elf $(OUTPUT).bin
	arm-none-eabi-objdump -d $(OUTPUT).elf > dump.txt

clean:
	rm -rf $(BUILD_DIR)/*

flash: $(OUTPUT).bin
	# @st-flash --reset write $(OUTPUT).bin 0x08000000
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(OUTPUT).bin 0x08000000 verify reset exit"

cat:
	echo 2288 | sudo -S cat /dev/ttyUSB0

gdb-server:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init;reset halt"

gdb:
	gdb-multiarch $(OUTPUT).elf
