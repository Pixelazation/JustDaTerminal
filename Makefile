# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN = JustDaTerminal

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(BIN)

# Linking the final binary
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild
