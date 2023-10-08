#Set this to @ to keep the makefile quiet
SILENCE = @

# Dynamically generate absolute paths
# From https://matheusmbar.com/bugfree-robot/2019/04/05/makefile-first-test.html
MAKEFILE_DIR=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))
PROJECT_DIR=$(realpath $(MAKEFILE_DIR)../)
TEST_DIR=$(PROJECT_DIR)/ex-unit-tests/

# Location of CPPUTEST_HOME
CPPUTEST_HOME=$(PROJECT_DIR)/cpputest

# Include and source files of the application
INCLUDE_DIRS=$(PROJECT_DIR)/inc
SRC_DIRS=$(PROJECT_DIR)/src

# Includes CppUTest header files
INCLUDE_DIRS += $(CPPUTEST_HOME)/include
INCLUDE_DIRS += $(CPPUTEST_HOME)/include/Platforms/Gcc

# Include MOCKIO files
INCLUDE_DIR += $(PROJECT_DIR)/mocks
SRC_DIRS += $(PROJECT_DIR)/mocks

# Unit test files
TEST_SRC_DIRS=$(TEST_DIR)

# Run MakefileWorker.mk with 
include $(CPPUTEST_HOME)/build/MakefileWorker.mk