#include <stdio.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int playerX = 40;
int playerY = 12;

void drawPlayer(int x, int y) {
    screenSetColor(WHITE, BLACK);
    screenGotoxy(x, y);
    printf("@");
}

void clearPlayer(int x, int y) {
    screenGotoxy(x, y);
    printf(" ");
}

int main() {
    int ch = 0;

    screenInit(1);       
    keyboardInit();      
    timerInit(50);      

    drawPlayer(playerX, playerY); 
    screenUpdate();

    while (ch != 27) {  
        if (keyhit()) {
            ch = readch();

            int newX = playerX;
            int newY = playerY;

            if (ch == 'w' || ch == 'W') newY--;
            if (ch == 's' || ch == 'S') newY++;
            if (ch == 'a' || ch == 'A') newX--;
            if (ch == 'd' || ch == 'D') newX++;

            
            if (newX > MINX && newX < MAXX && newY > MINY && newY < MAXY) {
                clearPlayer(playerX, playerY);
                playerX = newX;
                playerY = newY;
                drawPlayer(playerX, playerY);
                screenUpdate();
            }
        }

        if (timerTimeOver()) {
            
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
