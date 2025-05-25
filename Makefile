# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Project name
PROJ_NAME = logica-fatal

# Target directories
BUILD_DIR   = build
OBJ_DIR     = $(BUILD_DIR)/obj
SRC_DIR     = src
INCLUDE_DIR = include

# Source and object files
SRC_FILES = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Build target
all: $(OBJ_DIR) $(BUILD_DIR)/$(PROJ_NAME)

$(BUILD_DIR)/$(PROJ_NAME): $(OBJ_FILES)
	@echo Linking $(PROJ_NAME)...
	@$(CC) $(CFLAGS) -o $@ $^

# Ensure build directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR): $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $<...
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	@echo Cleaning build...
	rm -rf $(BUILD_DIR)

# Run target
run: all
	@echo Running $(PROJ_NAME)...
	@./$(BUILD_DIR)/$(PROJ_NAME)
