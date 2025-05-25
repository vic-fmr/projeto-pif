#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include <string.h>
#include "keyboard.h"
#include <ctype.h>

void pintar_fundo(int largura, int altura, int cor_fundo) {
  screenSetColor(cor_fundo, cor_fundo);
  for (int y = 0; y < altura; y++) {
    screenGotoxy(0, y);
    for (int x = 0; x < largura; x++) {
      printf(" ");
    }
  }
}

void tela_inicial() {
  const char *arte[] = {"░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░       "
                        "░▒▓████████▓▒░▒▓██████▓▒░▒▓████████▓▒░▒▓██████▓▒░░▒▓█▓▒░        ",
                        "░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░     "
                        "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ",
                        "░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░     "
                        "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ",
                        "░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒▒▓███▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓████████▓▒░      "
                        "░▒▓██████▓▒░░▒▓████████▓▒░ ░▒▓█▓▒░  ░▒▓████████▓▒░▒▓█▓▒░        ",
                        "░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░     "
                        "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ",
                        "░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░     "
                        "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ",
                        "░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░     "
                        "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░   ",
                        "",
                        "                          Um jogo de dedução e assassinatos acadêmicos.",
                        "                              Pressione ENTER para começar..."};

  screenClear();
  pintar_fundo(150, 25, BLACK);
  screenSetColor(WHITE, BLACK);

  int linhas = sizeof(arte) / sizeof(arte[0]);
  int y = 3;

  for (int i = 0; i < linhas; i++) {
    int x = (80 - strlen(arte[i])) / 2;
    if (x < 0) x = 0;
    screenGotoxy(x, y++);
    printf("%s", arte[i]);
  }
  getchar();
}

int nome_valido(const char *nome) {
  for (int i = 0; nome[i] != '\0'; i++) {
    if (!isspace(nome[i])) return 1;
  }
  return 0;
}

void mostrar_instrucoes(char *nome_jogador) {
  screenClear();
  pintar_fundo(150, 25, BLACK);
  screenSetColor(WHITE, BLACK);

  screenGotoxy(20, 2);
  printf("====================================================");
  screenGotoxy(20, 3);
  printf("              LÓGICA FATAL - MISSÃO                ");
  screenGotoxy(20, 4);
  printf("====================================================");

  screenSetColor(LIGHTGRAY, BLACK);
  screenGotoxy(10, 6);
  printf("Um terrível assassinato aconteceu na CESAR School...");

  screenGotoxy(10, 8);
  printf("O Professor Diego foi encontrado sem vida em uma das salas.");
  screenGotoxy(10, 10);
  printf("Cabe a VOCÊ descobrir quem cometeu esse crime, com qual");
  screenGotoxy(10, 11);
  printf("arma e em qual local. Use as pistas lógicas para resolver!");

  screenGotoxy(10, 14);
  screenSetColor(CYAN, BLACK);
  printf(">> COMANDOS DO JOGO:");

  screenSetColor(LIGHTGRAY, BLACK);
  screenGotoxy(12, 16);
  printf("W - mover para cima");
  screenGotoxy(12, 17);
  printf("A - mover para esquerda");
  screenGotoxy(12, 18);
  printf("S - mover para baixo");
  screenGotoxy(12, 19);
  printf("D - mover para direita");
  screenGotoxy(12, 20);
  printf("C - chutar uma solução");

  int tentativa = 0;
  do {
    if (tentativa) {
      screenSetColor(WHITE, BLACK);
      screenGotoxy(10, 24);
      printf("                                                    ");
      screenGotoxy(10, 25);
      printf("                                                    ");
    }

    screenSetColor(WHITE, BLACK);
    screenGotoxy(10, 23);
    printf("Digite seu nome para começar:                     ");
    screenGotoxy(10, 24);
    fgets(nome_jogador, 50, stdin);
    nome_jogador[strcspn(nome_jogador, "\n")] = '\0';

    if (!nome_valido(nome_jogador)) {
      screenSetColor(RED, BLACK);
      screenGotoxy(10, 25);
      printf("Nome inválido. Tente novamente.");
    }

    tentativa = 1;
  } while (!nome_valido(nome_jogador));

  screenSetColor(WHITE, BLACK);
  screenGotoxy(10, 27);
  printf("Bem-vindo, %s! Pressione ENTER para iniciar a investigação!", nome_jogador);
  getchar();
}