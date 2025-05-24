#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 20

char map[MAP_HEIGHT][MAP_WIDTH];

int playerX = 40;
int playerY = 12;

typedef struct tamanhoSala {
  int Xinicial;
  int Xfinal;
  int Yinicial;
  int Yfinal;
} tamanhoSala;

void showDialog(const char *text) {
  screenSetColor(WHITE, BLACK);
  for (int y = MAP_HEIGHT; y < MAP_HEIGHT + 5; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      screenGotoxy(x, y);
      if (y == MAP_HEIGHT) {
        if (x == 2)
          printf("| Dicas encontradas no local |");

        if (x < 2 || x > 1 + strlen("| Dicas encontradas no local |"))
          printf("=");
        continue;
      }

      printf(" ");
    }
  }
  screenGotoxy(1, MAP_HEIGHT + 2);
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
  } else {
    screenSetColor(WHITE, BLACK); // Cor padrão para espaços vazios
  }
  printf("%c", map[playerY][playerX]); // desenha o que tinha ali antes
}

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
      // Bordas e algumas paredes internas (mantendo a lógica original)
      if (x == 20 || x == MAP_WIDTH - 20) { // Paredes verticais internas
        map[y][x] = '|';
      } else if (y == 5 ||
                 y == MAP_HEIGHT - 5) { // Paredes horizontais internas
        map[y][x] = '-';
      } else {
        map[y][x] = ' '; // Espaço vazio
      }

      // Setar portas na matriz do mapa
      if (x == 5 || x == 6 || x == 31 || x == 32 || x == MAP_WIDTH - 4 ||
          x == MAP_WIDTH - 5) {
        map[y][x] = ' ';
      }
      // Setar portas na matriz do mapa
      if (y == 2 || y == 10 || y == MAP_HEIGHT - 2) {
        map[y][x] = ' ';
      }
    }
  }
  // Definição das salas (repetição aqui porque o escopo local da função precisa
  // delas)
  tamanhoSala tamanhoAuditorio = {1, 19, 1, 4};
  tamanhoSala tamanhoBiblioteca = {21, 59, 1, 4};
  tamanhoSala tamanhoSala401 = {61, MAP_WIDTH - 1, 1, 4};
  tamanhoSala tamanhoCopa = {61, MAP_WIDTH - 1, 6, MAP_HEIGHT - 6};
  tamanhoSala tamanhoGaragino = {61, MAP_WIDTH - 1, MAP_HEIGHT - 4,
                                 MAP_HEIGHT - 1};
  tamanhoSala tamanhoSalaProf = {21, 59, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
  tamanhoSala tamanhoSalaTI = {1, 19, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
  tamanhoSala tamanhoPraca = {1, 19, 6, MAP_HEIGHT - 6};

  // Escreve nomes no centro das salas
  desenharNomeNoMapa(
      tamanhoAuditorio.Xinicial +
          (tamanhoAuditorio.Xfinal - tamanhoAuditorio.Xinicial - 9) / 2,
      tamanhoAuditorio.Yinicial +
          (tamanhoAuditorio.Yfinal - tamanhoAuditorio.Yinicial) / 2,
      "AUDITORIO");

  desenharNomeNoMapa(
      tamanhoBiblioteca.Xinicial +
          (tamanhoBiblioteca.Xfinal - tamanhoBiblioteca.Xinicial - 10) / 2,
      tamanhoBiblioteca.Yinicial +
          (tamanhoBiblioteca.Yfinal - tamanhoBiblioteca.Yinicial) / 2,
      "BIBLIOTECA");

  desenharNomeNoMapa(tamanhoSala401.Xinicial +
                         (tamanhoSala401.Xfinal - tamanhoSala401.Xinicial - 8) /
                             2,
                     tamanhoSala401.Yinicial +
                         (tamanhoSala401.Yfinal - tamanhoSala401.Yinicial) / 2,
                     "SALA 401");

  desenharNomeNoMapa(tamanhoCopa.Xinicial +
                         (tamanhoCopa.Xfinal - tamanhoCopa.Xinicial - 4) / 2,
                     tamanhoCopa.Yinicial +
                         (tamanhoCopa.Yfinal - tamanhoCopa.Yinicial) / 2,
                     "COPA");

  desenharNomeNoMapa(
      tamanhoGaragino.Xinicial +
          (tamanhoGaragino.Xfinal - tamanhoGaragino.Xinicial - 8) / 2,
      tamanhoGaragino.Yinicial +
          (tamanhoGaragino.Yfinal - tamanhoGaragino.Yinicial) / 2,
      "GARAGINO");

  desenharNomeNoMapa(
      tamanhoSalaProf.Xinicial +
          (tamanhoSalaProf.Xfinal - tamanhoSalaProf.Xinicial - 17) / 2,
      tamanhoSalaProf.Yinicial +
          (tamanhoSalaProf.Yfinal - tamanhoSalaProf.Yinicial) / 2,
      "SALA DOS PROFESSORES");

  desenharNomeNoMapa(tamanhoSalaTI.Xinicial +
                         (tamanhoSalaTI.Xfinal - tamanhoSalaTI.Xinicial - 9) /
                             2,
                     tamanhoSalaTI.Yinicial +
                         (tamanhoSalaTI.Yfinal - tamanhoSalaTI.Yinicial) / 2,
                     "SALA DE TI");

  desenharNomeNoMapa(tamanhoPraca.Xinicial +
                         (tamanhoPraca.Xfinal - tamanhoPraca.Xinicial - 5) / 2,
                     tamanhoPraca.Yinicial +
                         (tamanhoPraca.Yfinal - tamanhoPraca.Yinicial) / 2,
                     "PRACA");
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

bool verificarSala(tamanhoSala sala, const char *nomeSala) {
  if (playerX >= sala.Xinicial && playerX <= sala.Xfinal &&
      playerY >= sala.Yinicial && playerY <= sala.Yfinal) {
    showDialog(nomeSala);
    return true;
  }
  showDialog(" ");
  return false;
}

int main() {
  int ch = 0;
  screenInit(1);  // Inicializa a tela
  keyboardInit(); // Inicializa o teclado
  timerInit(50);  // Inicializa o timer (para loop de jogo, se necessário)

  initMap();
  drawMap();
  drawPlayer();
  screenUpdate(); // Atualiza a tela para mostrar o estado inicial

  tamanhoSala tamanhoAuditorio = {1, 19, 1, 4};
  tamanhoSala tamanhoBiblioteca = {21, 59, 1, 4};
  tamanhoSala tamanhoSala401 = {61, MAP_WIDTH - 1, 1, 4};
  tamanhoSala tamanhoCopa = {61, MAP_WIDTH - 1, 6, MAP_HEIGHT - 6};
  tamanhoSala tamanhoGaragino = {61, MAP_WIDTH - 1, MAP_HEIGHT - 4,
                                 MAP_HEIGHT - 1};
  tamanhoSala tamanhoSalaProf = {21, 59, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
  tamanhoSala tamanhoSalaTI = {1, 19, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
  tamanhoSala tamanhoPraca = {1, 19, 6, MAP_HEIGHT - 6};

  while (
      ch !=
      27) { // Loop principal até a tecla ESC (código ASCII 27) ser pressionada
    if (keyhit()) {  // Se uma tecla foi pressionada
      ch = readch(); // Lê a tecla

      int newX = playerX;
      int newY = playerY;

      if (ch == 'w' || ch == 'W')
        newY--;
      if (ch == 's' || ch == 'S')
        newY++;
      if (ch == 'a' || ch == 'A')
        newX--;
      if (ch == 'd' || ch == 'D')
        newX++;

      // Verifica se a nova posição está dentro dos limites do mapa
      if (newX < 0)
        newX = 0;
      if (newX >= MAP_WIDTH)
        newX = MAP_WIDTH - 1;
      if (newY < 0)
        newY = 0;
      if (newY >= MAP_HEIGHT)
        newY = MAP_HEIGHT - 1;

      // Verifica colisão com paredes ('|' ou '-')
      if (map[newY][newX] != '|' && map[newY][newX] != '-') {
        clearPlayer();
        playerX = newX;
        playerY = newY;
        drawPlayer();

        if (verificarSala(tamanhoAuditorio, "Você entrou no auditório")) {
        } else if (verificarSala(tamanhoBiblioteca,
                                 "Você entrou na biblioteca")) {
        } else if (verificarSala(tamanhoSala401, "Você entrou na sala 401")) {
        } else if (verificarSala(tamanhoCopa, "Você entrou na copa")) {
        } else if (verificarSala(tamanhoGaragino, "Você entrou no garagino")) {
        } else if (verificarSala(tamanhoSalaProf,
                                 "Você entrou na sala dos professores")) {
        } else if (verificarSala(tamanhoSalaTI, "Você entrou na sala de TI")) {
        } else if (verificarSala(tamanhoPraca,
                                 "Você entrou na praça de convivência")) {
        } else {
          showDialog(" ");
        }

      } else {
        // Se colidiu, o jogador não se move, apenas redesenha na posição antiga
        // para garantir que ele fique visível e o diálogo seja limpo se
        // necessário
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
