#include "dialogo.h"
#include "screen.h"
#include <stdio.h>
#include <string.h>
#include "mapa.h"

void showDialog(const char *clue1, const char *clue2) {
  screenSetColor(WHITE, BLACK);
  for (int y = MAP_HEIGHT; y < MAP_HEIGHT + 5; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      screenGotoxy(x, y);
      if (y == MAP_HEIGHT) {
        if (x == 2)
          printf("| Dicas encontradas no local |");
        else if (x < 2 || x > 1 + strlen("| Dicas encontradas no local |"))
          printf("=");
        continue;
      }
      if (y == MAP_HEIGHT + 4) {
        printf("=");
        continue;
      };
      if (x == 1 || x == MAP_WIDTH - 1) {
        printf("|");
        continue;
      }
      printf(" ");
    }
  }
  screenGotoxy(3, MAP_HEIGHT + 2);
  printf("%s", clue1);
  screenGotoxy(3, MAP_HEIGHT + 3);
  printf("%s", clue2);
}
