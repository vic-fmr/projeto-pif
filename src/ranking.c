#include "ranking.h"
#include "screen.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_RANKING "ranking.csv"

int validar_nome(const char *nome) {
  for (int i = 0; nome[i]; i++) {
    if (nome[i] == ',' || !isprint(nome[i])) return 0;
  }
  return 1;
}

// double calcular_pontuacao(double tempo) {
//   double base = 1000.0;
//   double penalidade = tempo * 10.0;
//   double score = base - penalidade;
//   return score > 0 ? score : 0;
// }

void salvar_ranking(const char *nome, double tempo) {
  FILE *f = fopen(ARQUIVO_RANKING, "a");
  if (!f) return;

  fprintf(f, "%s,%.2f,%.2f\n", nome, tempo);
  fclose(f);
}

void mostrar_ranking() {
  screenClear();
  FILE *f = fopen(ARQUIVO_RANKING, "r");
  if (!f) {
    printf("Ranking vazio ou arquivo não encontrado.\n");
    getchar();
    return;
  }

  printf("\n======== RANKING ========\n");
  printf("%-20s %-10s\n", "Nome", "Tempo(s)");

  char linha[100];
  while (fgets(linha, sizeof(linha), f)) {
    char nome[50];
    double tempo;
    if (sscanf(linha, "%49[^,],%lf", nome, &tempo) == 2) {
      printf("%-20s %.2fs\n", nome, tempo);
    }
  }

  fclose(f);
  printf("\nPressione ENTER para voltar...\n");
  getchar(); // Espera usuário antes de sair da tela
}

// void limpar_ranking() {
//   FILE *f = fopen(ARQUIVO_RANKING, "w");
//   if (f) fclose(f);
//   printf("Ranking limpo com sucesso.\n");
// }