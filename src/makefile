CC = gcc
CFLAGS = -Wall -I./header

SRC_DIR = .
SRC_C_DIR = ./c
HEADER_DIR = ./header
BUILD_DIR = ./build

SRCS = $(wildcard $(SRC_C_DIR)/*.c)
OBJS = $(patsubst $(SRC_C_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
MAIN = main.c
TARGET = main

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_C_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)