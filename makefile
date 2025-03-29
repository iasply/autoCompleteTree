CC := clang

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

DEBUG_FLAG := -DDEBUG_ON
CURL_FLAG := -lcurl -lcjson -DCURL_ON 

CFLAGS := -Wall -Wextra -O1 -I./$(INCLUDE_DIR) -v -L/usr/lib  $(CURL_FLAG)

C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
C_HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
SOURCES := $(C_SOURCES) 
HEADERS := $(C_HEADERS) 

C_OBJECTS := $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

OBJECTS := $(C_OBJECTS) 

TARGET := $(BUILD_DIR)/dic
LINKER := $(CC)
FLAGS := $(CFLAGS)

# Default target
all: $(TARGET)

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the final binary
$(TARGET): $(OBJECTS)
	$(LINKER) $(FLAGS) -o $@ $^

# Run the program
run: all
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Format source and header files
format:
	clang-format -i $(SOURCES) $(HEADERS)

.PHONY: all run clean format
