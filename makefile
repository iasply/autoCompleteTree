# Compiler selection
CC := clang
CXX := clang++

# Directories
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

# Flags
CFLAGS := -Wall -Wextra -O2 -I./$(INCLUDE_DIR)
CXXFLAGS := -Wall -Wextra -std=c++17 -O2 -I./$(INCLUDE_DIR)

# Find all source and header files
C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
CPP_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
C_HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
CPP_HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
SOURCES := $(C_SOURCES) $(CPP_SOURCES)
HEADERS := $(C_HEADERS) $(CPP_HEADERS)

# Generate object files for C and C++ sources separately
C_OBJECTS := $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CPP_OBJECTS := $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Combine both C and C++ object files
OBJECTS := $(C_OBJECTS) $(CPP_OBJECTS)

# Select compiler based on source files
ifeq ($(strip $(CPP_SOURCES)),)
    TARGET := $(BUILD_DIR)/app_c
    LINKER := $(CC)
    FLAGS := $(CFLAGS)
else
    TARGET := $(BUILD_DIR)/app_cpp
    LINKER := $(CXX)
    FLAGS := $(CXXFLAGS)
endif

# Default target
all: $(TARGET)

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

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
