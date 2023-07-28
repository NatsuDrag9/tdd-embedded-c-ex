UNITY_DIR := .
PROD_CODE_SRC_DIR := $(UNITY_DIR)/src
TEST_DIR := $(UNITY_DIR)/test

BUILD_DIR := build

PROD_CODE_SRC_FILES := $(wildcard $(PROD_CODE_SRC_DIR)/*.c)
PROD_CODE_OBJ_FILES := $(patsubst $(PROD_CODE_SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(PROD_CODE_SRC_FILES))

UNITY_SRC_FILES := $(wildcard $(UNITY_DIR)/*.c)
UNITY_OBJ_FILES := $(patsubst $(UNITY_DIR)/%.c, $(BUILD_DIR)/%.o, $(UNITY_SRC_FILES))

TEST_SRC_FILES := $(wildcard $(TEST_DIR)/**/*.c) $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRC_FILES))

TARGET := tdd_ex2.out

CC := gcc
CFLAGS := -Wall -Wextra -I $(UNITY_DIR) -g

# Run clean each time make executes on terminal
.PHONY: clean

all: $(TARGET)
	@echo "********	Compiled successfully! Target: $< created at $(CURDIR)	********\n"
	@echo "********	Running Unity tests on Led Driver	********\n"
	./$(TARGET) -v

# Rule to build $(TARGET) by first linking the production code's object file
# followed by object files of UNITY and test cases
$(TARGET): $(PROD_CODE_OBJ_FILES) $(UNITY_OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "********	Successfully linked object files.	********\n"

$(BUILD_DIR)/%.o: $(PROD_CODE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "********	Successfully built object files for production code at $@	********\n"

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "********	Successfully built object files for UNITY at $@.	********\n"

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "********	Successfully built object files for tests at $@.	********\n"

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(TARGET)