CC = gcc
CFLAGS = -Wall
TARGET = jogo_detetive

all: $(TARGET)

$(TARGET): main.o ranking.o temporizador.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c ranking.h temporizador.h
	$(CC) $(CFLAGS) -c main.c

ranking.o: ranking.c ranking.h
	$(CC) $(CFLAGS) -c ranking.c

temporizador.o: temporizador.c temporizador.h
	$(CC) $(CFLAGS) -c temporizador.c

clean:
	rm -f *.o $(TARGET)