#include "player.h"
#include "mapa.h"
#include "screen.h"

int playerX = 40;
int playerY = 12;

void drawPlayer() {
  screenGotoxy(playerX, playerY);
  screenSetColor(YELLOW, BLACK);
  printf("o");
}

void clearPlayer() {
  screenGotoxy(playerX, playerY);
  char tile = map[playerY][playerX];
  screenSetColor(WHITE, BLACK);
  printf("%c", tile);
}
