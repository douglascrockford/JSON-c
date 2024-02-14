# Compile and run unit tests
SRC_DIR := ..
TEST_DIR := .
TEST_SUPPORT_DIR := .
OBJ_DIR := $(TEST_DIR)/obj
BIN_DIR := $(TEST_DIR)/bin

SRC_FILES := \
	$(SRC_DIR)/JSON_checker.c

TEST_FILES := \
	$(TEST_DIR)/test_JSON_checker.c

CC := gcc
CFLAGS := -Wall -g

TEST_SUPPORT_FILES := \
	$(TEST_SUPPORT_DIR)/unity.c

SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES) $(CORE_FILES))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_FILES))
TEST_SUPPORT_OBJS := $(patsubst $(TEST_SUPPORT_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SUPPORT_FILES))
EXECUTABLES := $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_FILES))

# Prevent makefile from automatically deleting object files
.SECONDARY: $(SRC_OBJS) $(TEST_OBJS) $(TEST_SUPPORT_OBJS)

$(info SRC_OBJS = $(SRC_OBJS))
$(info TEST_OBJS = $(TEST_OBJS))
$(info TEST_SUPPORT_OBJS = $(TEST_SUPPORT_OBJS))
$(info EXECUTABLES = $(EXECUTABLES))

.PHONY: all tests clean

all: $(EXECUTABLES)

tests: all
	@for test in $(EXECUTABLES) ; do \
		echo "Running $$test..."; \
		./$$test; \
	done

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(COVERAGE_DIR)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(CORE_DIR) -I$(TEST_SUPPORT_DIR) -c $< -o $@

# Compile test support files
$(OBJ_DIR)/%.o: $(TEST_SUPPORT_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

# Link object files to create executables
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(SRC_OBJS) $(TEST_SUPPORT_OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(LFLAGS) $^ -o $@
