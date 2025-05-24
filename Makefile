CC = gcc
CFLAGS = -Wall -I./include
SRC = $(wildcard src/**/*.c) $(wildcard src/*.c)
TARGET = jogo

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
