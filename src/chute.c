#include "chute.h"
#include <string.h>

void limpar_area_modal(int x, int y, int width, int height) {
  screenSetColor(WHITE, BLACK);
  for (int j = 0; j < height; j++) {
    screenGotoxy(x, y + j);
    for (int i = 0; i < width; i++) {
      printf(" ");
    }
  }
}

static void desenhar_moldura(int x, int y, int width, int height) {
  screenGotoxy(x, y);
  printf("┌");
  screenGotoxy(x + width - 1, y);
  printf("┐");
  screenGotoxy(x, y + height - 1);
  printf("└");
  screenGotoxy(x + width - 1, y + height - 1);
  printf("┘");

  for (int i = x + 1; i < x + width - 1; i++) {
    screenGotoxy(i, y);
    printf("-");
    screenGotoxy(i, y + height - 1);
    printf("-");
  }

  for (int j = y + 1; j < y + height - 1; j++) {
    screenGotoxy(x, j);
    printf("|");
    screenGotoxy(x + width - 1, j);
    printf("|");
  }
}

static void centralizar_texto(int y, const char *texto, int modal_x) {
  int len = strlen(texto);
  int x = modal_x + (MODAL_WIDTH - len) / 2;
  screenGotoxy(x, y);
  printf("%s", texto);
}

ItensChute obter_chute_jogador(const ItensUsados *itens) {

  ItensChute chute = {-1, -1, -1};
  int categoria_atual = 0;
  int selecao = 0;
  int tecla;

  while (categoria_atual < 3) {
    int screen_width = MAXX - MINX;
    int modal_x = MINX + (screen_width - MODAL_WIDTH) / 2;
    int modal_y = 2;

    limpar_area_modal(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);
    desenhar_moldura(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);

    const char *titulo;
    const char **opcoes;
    const int *indices;

    switch (categoria_atual) {
    case 0:
      titulo = "SELECIONE O SUSPEITO";
      opcoes = NOMES_SUSPEITOS;
      indices = itens->suspeitos;
      break;
    case 1:
      titulo = "SELECIONE A ARMA";
      opcoes = NOMES_ARMAS;
      indices = itens->armas;
      break;
    case 2:
      titulo = "SELECIONE O LOCAL";
      opcoes = NOMES_LOCAIS;
      indices = itens->locais;
      break;
    }

    centralizar_texto(modal_y + 1, titulo, modal_x);

    for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
      screenGotoxy(modal_x + 2, modal_y + 3 + i);
      if (i == selecao)
        screenSetColor(BLACK, WHITE);
      else
        screenSetColor(WHITE, BLACK);
      printf("%s", opcoes[indices[i]]);
    }
    screenSetColor(WHITE, BLACK);

    screenGotoxy(modal_x + 2, modal_y + MODAL_HEIGHT - 2);
    printf("Setas: Navegar   Enter: Selecionar");
    screenGotoxy(modal_x + 2, modal_y + MODAL_HEIGHT - 1);
    printf("ESC: Voltar");

    screenUpdate();

    // Leitura de tecla
    while (1) {
      if (keyhit()) {
        tecla = readch();

        if (tecla == 27) {
          if (keyhit() && readch() == 91) {
            tecla = readch();
            if (tecla == 65 && selecao > 0)
              selecao--;
            else if (tecla == 66 && selecao < USADOS_POR_CATEGORIA - 1)
              selecao++;
          } else {
            // Tecla ESC real
            if (categoria_atual > 0) {
              categoria_atual--;
              break;
            } else {
              return chute;
            }
          }
        } else if (tecla == '\n' || tecla == 10 || tecla == 13) {
          switch (categoria_atual) {
          case 0:
            chute.suspeitos = indices[selecao];
            break;
          case 1:
            chute.armas = indices[selecao];
            break;
          case 2:
            chute.locais = indices[selecao];
            break;
          }
          categoria_atual++;
          selecao = 0;
          break;
        }
        break;
      }
    }
  }

  return chute;
}

void mostrar_resultado_chute(int acertos) {
  int modal_x = MINX + (MAXX - MINX - MODAL_WIDTH) / 2;
  int modal_y = 2;

  limpar_area_modal(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);
  desenhar_moldura(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);
  centralizar_texto(modal_y + 1, "RESULTADO", modal_x);

  if (acertos == 3) {
    screenSetColor(GREEN, BLACK);
    screenGotoxy(modal_x + 5, modal_y + 3);
    printf("Parabéns! Caso resolvido!");
  } else {
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(modal_x + 5, modal_y + 3);
    printf("Acertou %d/3. Continue!", acertos);
  }

  screenSetColor(WHITE, BLACK);
  screenGotoxy(modal_x + 5, modal_y + MODAL_HEIGHT - 2);
  printf("Pressione qualquer tecla...");
  screenUpdate();

  while (!keyhit())
    ;
  readch();
}
