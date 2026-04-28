
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -finstrument-functions


SRC_DIR = src
BUILD_DIR = build


TARGET = $(BUILD_DIR)/app


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


all: build run


build: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


run: build
	./$(TARGET)


clean:
	rm -rf $(BUILD_DIR)
