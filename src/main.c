#include "player.h"
#include "jogo.h"
#include "mapa.h"
#include "salas.h"
#include "dialogo.h"
#include "pistas.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "ui.h"
#include "chute.h"

int main() {
  int ch = 0;
  char nome[50];

  tela_inicial();
  mostrar_instrucoes(nome);

  screenInit(1);
  keyboardInit();
  timerInit(50);

  initMap();
  drawMap();
  drawPlayer();
  screenUpdate();

  ItensUsados itens;
  Pista pistas[12];
  gerar_rodada(&itens);
  gerar_pistas(pistas, itens);

  while (ch != 27) {
    if (keyhit()) {
      ch = readch();

      if (ch == 'c') { // Tecla para abrir o chute
        ItensChute chute = obter_chute_jogador(&itens);
        if (chute.suspeitos != -1) { // Se não cancelou
          int acertos = validar_resultado(&chute, &itens);
          mostrar_resultado_chute(acertos);

          if (acertos == 3) {
            // Vitória!
            break;
          }
        }

        // Redesenha o jogo após chute
        screenClear();
        drawMap();
        drawPlayer();
        screenUpdate();
      }

      int newX = playerX;
      int newY = playerY;

      if (ch == 'w') newY--;
      if (ch == 's') newY++;
      if (ch == 'a') newX--;
      if (ch == 'd') newX++;

      if (map[newY][newX] != '|' && map[newY][newX] != '-') {
        clearPlayer();
        playerX = newX;
        playerY = newY;
        drawPlayer();

        if (!(verificarSala(tamanhoAuditorio, pistas[0].texto, pistas[8].texto) ||
              verificarSala(tamanhoBiblioteca, pistas[1].texto, "") ||
              verificarSala(tamanhoSala401, pistas[2].texto, pistas[9].texto) ||
              verificarSala(tamanhoCopa, pistas[3].texto, "") || verificarSala(tamanhoGaragino, pistas[4].texto, "") ||
              verificarSala(tamanhoSalaProf, pistas[5].texto, pistas[10].texto) ||
              verificarSala(tamanhoSalaTI, pistas[6].texto, "") ||
              verificarSala(tamanhoPraca, pistas[7].texto, pistas[11].texto))) {
          showDialog(" ", " ");
        }
      } else {
        drawPlayer();
      }
      screenUpdate();
    }
  }

  keyboardDestroy();
  screenDestroy();
  timerDestroy();
  return 0;
}
