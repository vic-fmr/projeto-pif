#include <stdio.h>
#include "screen.h"  
#include "keyboard.h" 
#include "timer.h"   

#define MAP_WIDTH  80
#define MAP_HEIGHT 20


char map[MAP_HEIGHT][MAP_WIDTH];

int playerX = 40;
int playerY = 12;

struct tamanhoSala {
    int Xinicial;
    int Xfinal;
    int Yinicial;
    int Yfinal;
} typedef tamanhoSala;


void showDialog(const char* text) {
    screenSetColor(WHITE, BLUE); // Texto branco sobre fundo azul
    // Limpa a área de diálogo (3 linhas abaixo do mapa)
    for (int y = MAP_HEIGHT; y < MAP_HEIGHT + 3; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            screenGotoxy(x, y);
            printf(" ");
        }
    }

    screenGotoxy(1, MAP_HEIGHT + 1);
    printf("%s", text);
   
}

void drawPlayer() {
    screenGotoxy(playerX, playerY);
    screenSetColor(RED, BLACK);
    printf("o");
}

void clearPlayer() {
    screenGotoxy(playerX, playerY);
    // Define a cor de volta para a cor do tile do mapa antes de redesenhar
    char tile = map[playerY][playerX];
    if (tile == '|' || tile == '_') {
        screenSetColor(WHITE, BLACK);
    } else if (tile == 'A' || tile == 'B' || tile == 'L' || tile == 'G' || tile == 'C' || tile == 'U' || tile == '4' || tile == 'P') {
        screenSetColor(YELLOW, BLACK);
    } else {
        screenSetColor(WHITE, BLACK); // Cor padrão para espaços vazios
    }
    printf("%c", map[playerY][playerX]);  // desenha o que tinha ali antes
}

void initMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 1; x < MAP_WIDTH; x++) {
            // Bordas e algumas paredes internas (mantendo a lógica original)
            if (x == 20 || x == MAP_WIDTH - 20) { // Paredes verticais internas
                map[y][x] = '|';
            } else if (y == 5 || y == MAP_HEIGHT - 5) { // Paredes horizontais internas
                map[y][x] = '-';
            }
            else {
                map[y][x] = ' '; // Espaço vazio
            }

            // Setar portas na matriz do mapa
            if (x == 5 || x == 6 || x == 31 || x == 32 ||x == MAP_WIDTH - 4 || x == MAP_WIDTH - 5) {
                map[y][x] = ' ';
            }
            // Setar portas na matriz do mapa
            if (y == 2 || y == 10 || y == MAP_HEIGHT - 2) {
                map[y][x] = ' ';
            }
        }
    }
}

void drawMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            screenGotoxy(x, y);
            char tile = map[y][x];

            if (tile == '|' || tile == '-') { // Paredes
                screenSetColor(WHITE, BLACK);
            } else { // Espaço vazio
                screenSetColor(WHITE, BLACK);
            }

            
            printf("%c", tile);
        }
    }
}

int main() {
    int ch = 0;
    screenInit(1);    // Inicializa a tela
    keyboardInit();   // Inicializa o teclado
    timerInit(50);    // Inicializa o timer (para loop de jogo, se necessário)

    initMap();
    drawMap();
    drawPlayer();
    screenUpdate();   // Atualiza a tela para mostrar o estado inicial

   // Sala A

tamanhoSala tamanhoA;
tamanhoA.Xinicial = 1;
tamanhoA.Xfinal   = 19;
tamanhoA.Yinicial = 1;
tamanhoA.Yfinal   = 4;

// // Sala B
// tamanhoSala tamanhoB;
// tamanhoB.Xinicial = 1;
// tamanhoB.Xfinal   = 19;
// tamanhoB.Yinicial = 6;
// tamanhoB.Yfinal   = 14;

// // Sala C
// tamanhoSala tamanhoC;
// tamanhoC.Xinicial = 1;
// tamanhoC.Xfinal   = 19;
// tamanhoC.Yinicial = 16;
// tamanhoC.Yfinal   = 18;

// // Sala L (Biblioteca)
// tamanhoSala tamanhoBiblioteca;
// tamanhoBiblioteca.Xinicial = 21;
// tamanhoBiblioteca.Xfinal   = 49;
// tamanhoBiblioteca.Yinicial = 1;
// tamanhoBiblioteca.Yfinal   = 4;

// // Sala G (Garagem)
// tamanhoSala tamanhoGaragino;
// tamanhoGaragino.Xinicial = 21;
// tamanhoGaragino.Xfinal   = 49;
// tamanhoGaragino.Yinicial = 6;
// tamanhoGaragino.Yfinal   = 14;

// // Sala 401
// tamanhoSala tamanhoSala401;
// tamanhoSala401.Xinicial = 21;
// tamanhoSala401.Xfinal   = 49;
// tamanhoSala401.Yinicial = 16;
// tamanhoSala401.Yfinal   = 18;

// // Sala P (Professores)
// tamanhoSala tamanhoSalaProf;
// tamanhoSalaProf.Xinicial = 51;
// tamanhoSalaProf.Xfinal   = 78;
// tamanhoSalaProf.Yinicial = 1;
// tamanhoSalaProf.Yfinal   = 4;

// // Sala U (Auditório)
// tamanhoSala tamanhoAuditorio;
// tamanhoAuditorio.Xinicial = 51;
// tamanhoAuditorio.Xfinal   = 78;
// tamanhoAuditorio.Yinicial = 6;
// tamanhoAuditorio.Yfinal   = 14;



    while (ch != 27) { // Loop principal até a tecla ESC (código ASCII 27) ser pressionada
        if (keyhit()) { // Se uma tecla foi pressionada
            ch = readch(); // Lê a tecla


            int newX = playerX;
            int newY = playerY;

            if (ch == 'w' || ch == 'W') newY--;
            if (ch == 's' || ch == 'S') newY++;
            if (ch == 'a' || ch == 'A') newX--;
            if (ch == 'd' || ch == 'D') newX++;

            // Verifica se a nova posição está dentro dos limites do mapa
            if (newX < 0) newX = 0;
            if (newX >= MAP_WIDTH) newX = MAP_WIDTH - 1;
            if (newY < 0) newY = 0;
            if (newY >= MAP_HEIGHT) newY = MAP_HEIGHT - 1;

            // Verifica colisão com paredes ('|' ou '-')
            if (map[newY][newX] != '|' && map[newY][newX] != '-') {
                clearPlayer();
playerX = newX;
playerY = newY;
drawPlayer();

char tile = map[playerY][playerX];

if (playerX >= tamanhoA.Xinicial && playerX <= tamanhoA.Xfinal &&
    playerY >= tamanhoA.Yinicial && playerY <= tamanhoA.Yfinal) {
    showDialog("Voce entrou no auditorio.");
} else if (tile == 'B') {
    showDialog("Voce encontrou uma biblioteca secreta.");
} else if (tile == 'L') {
    showDialog("Voce entrou na Biblioteca.");
} else if (tile == 'G') {
    showDialog("Voce entrou na Garagem.");
} else if (tile == 'C') {
    showDialog("Voce entrou na Copa.");
} else if (tile == 'U') {
    showDialog("Voce entrou no Auditorio.");
} else if (tile == '4') {
    showDialog("Voce entrou na Sala 401.");
} else if (tile == 'P') {
    showDialog("Voce entrou na Sala dos Professores.");
} else {
    showDialog(" ");
}

            } else {
                // Se colidiu, o jogador não se move, apenas redesenha na posição antiga
                // para garantir que ele fique visível e o diálogo seja limpo se necessário
                drawPlayer(); // Garante que o jogador ainda esteja desenhado
                // showDialog("Voce bateu na parede!"); // Opcional: mensagem de colisão
            }
            screenUpdate(); // Atualiza a tela após cada movimento/interação
        }

        // Pausa pequena para não sobrecarregar a CPU, se timerSleep existir
        // if (timerSleep) timerSleep(10); // Ex: dorme por 10ms
    }

    keyboardDestroy(); // Libera recursos do teclado
    screenDestroy();   // Libera recursos da tela
    timerDestroy();    // Libera recursos do timer
    return 0;
}