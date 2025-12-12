CC=gcc
CFLAGS=-Wall -O2 -pthread -lncurses -lm
TARGET=performance_analyzer
SRC_DIR=src
OBJ_DIR=obj

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: directories $(TARGET)

directories:
	@mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) data/*.log

install:
	cp $(TARGET) /usr/local/bin/

run: all
	sudo ./$(TARGET)

.PHONY: all clean install run directories
