SOURCES_C += $(shell find $(TARGET_BOARD) -name "*.c")

SOURCES_ASM += $(shell find $(TARGET_BOARD) -name "*.s")

OBJECTS_C = $(patsubst %.c, $(ROOT_DIR)/$(BUILD_DIR)/$(SUB_DIR)/%.o, $(SOURCES_C))
OBJECTS_ASM = $(patsubst %.s, $(ROOT_DIR)/$(BUILD_DIR)/$(SUB_DIR)/%.o, $(SOURCES_ASM))

.PHONY: all

all: $(OBJECTS_C) $(OBJECTS_ASM)

$(ROOT_DIR)/$(BUILD_DIR)/$(SUB_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(ROOT_DIR)/$(BUILD_DIR)/$(SUB_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) -c $< -o $@  $(AS_FLAGS)
