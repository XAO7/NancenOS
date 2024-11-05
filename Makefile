export TARGET_CPU ?= arm_cm4
export TARGET_MCU ?= stm32f411ret6
export TARGET_BOARD ?= frypi

export ROOT_DIR = $(shell pwd)
export BUILD_DIR = build
SUB_DIRS = kernel board mcu

INCLUDE_DIRS += . mcu/$(TARGET_MCU)/-- board/$(TARGET_BOARD)/--
INCLUDE_DIRS += kernel kernel/include
INCLUDE_DIRS += kernel/portable/$(TARGET_CPU)
INCLUDE_DIRS += kernel/portable/$(TARGET_CPU)/$(TARGET_MCU)
INCLUDE_DIRS += kernel/portable/$(TARGET_CPU)/$(TARGET_MCU)/$(TARGET_BOARD)
INCLUDE_DIRS += utils

EXPANDED_INCLUDE_DIRS := $(shell \
	for includeDir in $(INCLUDE_DIRS); do \
		if echo "$$includeDir" | grep -q '/--$$'; then \
			baseDir=$${includeDir%/--}; \
			find "$$baseDir" -type d; \
		else \
			echo "$$includeDir"; \
		fi; \
	done | tr '\n' ' ' \
)

INCLUDES = $(foreach dir, $(EXPANDED_INCLUDE_DIRS), -I$(ROOT_DIR)/$(dir))

SOURCES_ROOT = $(shell echo *.c)
OBJECTS_ROOT = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCES_ROOT))

OUTPUT = $(BUILD_DIR)/program
OBJECTS = $(shell find $(BUILD_DIR) -type f -name "*.o")

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CC_FLAGS += -Werror -mcpu=cortex-m4 -mthumb -Os -nostdlib -fno-builtin
CC_FLAGS += $(INCLUDES)
AS_FLAGS += -mcpu=cortex-m4 -mthumb
LD_FLAGS += -nostdlib -Map=$(OUTPUT).map
LD_FLAGS += -T kernel/portable/$(TARGET_CPU)/$(TARGET_MCU)/linker.ld 

.PHONY: auto_clean all subdirs clean flash cat gdb-server gdb

auto_clean:
	@trap 'make clean' ERR; make all

all: $(OUTPUT).bin

$(OUTPUT).bin: $(OUTPUT).elf
	$(OBJCOPY) -O binary $(OUTPUT).elf $(OUTPUT).bin
	arm-none-eabi-objdump -d $(OUTPUT).elf > dump.txt

$(OUTPUT).elf: subdirs $(OBJECTS_ROOT)
	$(LD) -o $@ $(LD_FLAGS) $(OBJECTS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CC_FLAGS)

subdirs:
	for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir SUB_DIR="$$dir" \
		CC="$(CC)" CC_FLAGS="$(CC_FLAGS)" AS="$(AS)" AS_FLAGS="$(AS_FLAGS)"; \
	done

clean:
	rm -rf $(BUILD_DIR)

flash: $(OUTPUT).bin
	# @st-flash --reset write $(OUTPUT).bin 0x08000000
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(OUTPUT).bin 0x08000000 verify reset exit"

cat:
	echo 2288 | sudo -S stty -F /dev/ttyUSB0 115200
	echo 2288 | sudo -S cat /dev/ttyUSB0

gdb-server:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init;reset halt"

gdb:
	gdb-multiarch $(OUTPUT).elf -ex 'target extended-remote :3333'

