UNITY_DIR := .

# BUILD_DIR := $(shell mkdir -p $(UNITY_DIR)/build && $$(pwd)/build)
BUILD_DIR := build
TEST_DIR := $(UNITY_DIR)/test

UNITY_SRC_FILES := $(wildcard $(UNITY_DIR)/*.c)
UNITY_OBJ_FILES := $(patsubst $(UNITY_DIR)/%.c, $(BUILD_DIR)/%.o, $(UNITY_SRC_FILES))
TEST_SRC_FILES := $(wildcard $(TEST_DIR)/**/*.c) $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRC_FILES))

TARGET := tdd_ex1.out

CC := gcc
CFLAGS := -Wall -Wextra -I $(UNITY_DIR) -g
# LFLAGS := lm

# Default rule
all: $(TARGET)
#	@echo "Unity Root: $(UNITY_DIR)"
#	@echo "SRC_FILES: $(SRC_FILES)"
	@echo "Successfully compiled! Generated executable $^"

# Rule to build the target executable
$(TARGET): $(UNITY_OBJ_FILES) $(TEST_OBJ_FILES)
	@echo "in rule $@"
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from unity source files
$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
	@echo "in rule $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files from test source files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@echo "in rule $@ for $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)


################################################################
# The differences between the top and bottom make file are:
# 
# 1.) Test dir and its .c files are separated and stored in another variable in the top file
# but Unity dir and Test dir are combined into one variable in the bottom one. 

# 2.) The issue with this is that recursive folder search using wildcard needs to be
# repeated twice in the bottom file
#
################################################################

# UNITY_DIR := .

# # BUILD_DIR := $(shell mkdir -p $(UNITY_DIR)/build && $$(pwd)/build)
# BUILD_DIR := build
# TEST_DIR := $(UNITY_DIR)/test

# SRC_FILES := $(wildcard $(UNITY_DIR)/*.c) $(wildcard $(UNITY_DIR)/**/*.c) $(wildcard $(UNITY_DIR)/**/**/*.c)
# OBJ_FILES := $(patsubst $(UNITY_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# TARGET := tdd_ex1.out

# CC := gcc
# CFLAGS := -Wall -Wextra -I $(UNITY_DIR) -g
# # LFLAGS := lm

# # Default rule
# all: $(TARGET)
# #	@echo "Unity Root: $(UNITY_DIR)"
# #	@echo "SRC_FILES: $(SRC_FILES)"
# 	@echo "Successfully compiled! Generated executable $^"

# # Rule to build the target executable
# $(TARGET): $(OBJ_FILES)
# 	@echo "in rule $@"
# 	$(CC) $(CFLAGS) -o $@ $^

# # Rule to build object files from unity source files
# $(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
# 	@echo "in rule $@"
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Clean
# clean:
# 	rm -rf $(BUILD_DIR) $(TARGET)