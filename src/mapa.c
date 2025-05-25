#include "mapa.h"
#include "salas.h"
#include "screen.h"
#include <stdio.h>

char map[MAP_HEIGHT][MAP_WIDTH];

void desenharNomeNoMapa(int x, int y, const char *nome) {
  for (int i = 0; nome[i] != '\0'; i++) {
    if (x + i < MAP_WIDTH) {
      map[y][x + i] = nome[i];
    }
  }
}

void initMap() {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 1; x < MAP_WIDTH; x++) {
      if (x == 20 || x == MAP_WIDTH - 20) {
        map[y][x] = '|';
      } else if (y == 5 || y == MAP_HEIGHT - 5) {
        map[y][x] = '-';
      } else {
        map[y][x] = ' ';
      }

      if (x == 5 || x == 6 || x == 31 || x == 32 || x == MAP_WIDTH - 4 || x == MAP_WIDTH - 5) {
        map[y][x] = ' ';
      }
      if (y == 2 || y == 10 || y == MAP_HEIGHT - 2) {
        map[y][x] = ' ';
      }
    }
  }
  initNomesNasSalas();
}

void drawMap() {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      screenGotoxy(x, y);
      screenSetColor(WHITE, BLACK);
      printf("%c", map[y][x]);
    }
  }
}
