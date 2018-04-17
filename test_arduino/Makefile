
APP_NAME= test

SOURCE_DIR= ./src
INCLUDES_DIR= ./src
BUILD_DIR= ./build
OBJ_DIR= ./obj

TARG= $(BUILD_DIR)/$(APP_NAME)
OUTPUT_DIR_CREATED= $(OBJ_DIR)/created

 
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
 
SOURCES_LIST = main.c uart.c timer.c adc.c

INCLUDES_LIST = test.h config.h

SRCS = $(addprefix $(SOURCE_DIR)/,$(SOURCES_LIST))
INCS = $(addprefix -I$(INCLUDES_DIR)/,$(INCLUDES_LIST))

OBJECTS_LIST = $(addprefix $(OBJ_DIR)/,$(SOURCES_LIST)) 
OBJS = $(OBJECTS_LIST:.c=.o)
 
MCU=atmega168
 
CFLAGS = \
	-mmcu=$(MCU) \
	-Wall \
	-g \
	-Os \
	-Werror \
	-lm  \
	-mcall-prologues \
	-DF_CPU=16000000
	
LDFLAGS = -mmcu=$(MCU)  \
	-Wall \
	-g \
	-Os  \
	-Werror 
 
all: $(TARG).hex
#@echo
#@echo "Build finished\n"
 
$(TARG).hex: $(TARG).elf
	@$(OBJCOPY) -O ihex -R .eeprom -R .nwram  $< $@

$(TARG).elf: $(OBJS)
	@$(CC) $(LDFLAGS) -o $@  $(OBJS) -lm
#	$(OBJCOPY) -O binary -R .eeprom -R .nwram  $@.elf $@.bin
	@echo "\n\n"
	@$(SIZE) $@ -C --mcu=$(MCU)

 
$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@
 
clean:
	rm  $(BUILD_DIR)/* 
	rm  $(OBJ_DIR)/*

burn: $(TARG).hex
	avrdude -c usbasp -p m168 -U flash:w:$(TARG).hex

disasm: $(TARG).elf
	$(OBJDUMP) -S  --disassemble $(TARG).elf > $(TARG).lst


$(OUTPUT_DIR_CREATED):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR)
	@touch $(OUTPUT_DIR_CREATED)
	@echo "Created directories for objects and binaries"
