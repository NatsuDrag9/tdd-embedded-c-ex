# This makefile is a replica from Shawn Hymel's video series on Intro to CI/CD
# Link - https://youtu.be/lZWFmEhIhpY?t=459

# Build tool definitions
CC ?= gcc
CXX ?= g++

# Settings
SRC_DIR = ./src
INCLUDE_DIR = ./inc
TEST_DIR = ./ex-unit-tests
BUILD_DIR = build
OUTPUT = app.elf

# Search path for header files
CFLAGS += -I $(INCLUDE_DIR)

# Add warnings to compiler flags
CFLAGS += -Wall -Wextra

# Linker flags
LDFLAGS +=

# Source files
CSOURCES = ./main.c
CSOURCES += $(wildcard $(SRC_DIR)/*.c)

# Generate names for output object files (*.o)
COBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(CSOURCES))

# Default rule: Build application
.PHONY: all
all: $(OUTPUT)

# Building components without linking
$(COBJECTS) : $(BUILD_DIR)/%.o : %.c
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build the target application
.PHONY: $(OUTPUT)
$(OUTPUT): $(COBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(COBJECTS) -o $(BUILD_DIR)/$(OUTPUT) $(LDFLAGS)

# Remove build files of source code
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Run Tests
.PHONY: test
test:
	make -C $(TEST_DIR)

.PHONY: clean_test
clean_test:
	make -C $(TEST_DIR) clean