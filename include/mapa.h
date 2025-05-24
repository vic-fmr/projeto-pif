#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 80
#define MAP_HEIGHT 20

extern char map[MAP_HEIGHT][MAP_WIDTH];

void initMap();
void drawMap();
void desenharNomeNoMapa(int x, int y, const char *nome);

#endif
