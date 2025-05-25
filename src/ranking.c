#include "ranking.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_RANKING "ranking.csv"

int validar_nome(const char *nome) {
  for (int i = 0; nome[i]; i++) {
    if (nome[i] == ',' || !isprint(nome[i]))
      return 0;
  }
  return 1;
}

double calcular_pontuacao(double tempo, int acertou) {
  if (!acertou)
    return 0;
  double base = 1000.0;
  double penalidade = tempo * 10.0;
  double score = base - penalidade;
  return score > 0 ? score : 0;
}

void salvar_ranking(const char *nome, double tempo, int acertou) {
  FILE *f = fopen(ARQUIVO_RANKING, "a");
  if (!f)
    return;

  double pontuacao = calcular_pontuacao(tempo, acertou);
  fprintf(f, "%s,%.2f,%.2f\n", nome, tempo, pontuacao);
  fclose(f);
}

void mostrar_ranking() {
  FILE *f = fopen(ARQUIVO_RANKING, "r");
  if (!f) {
    printf("Ranking vazio ou arquivo não encontrado.\n");
    return;
  }

  printf("\n=== RANKING ===\n");
  printf("%-20s %-10s %-10s\n", "Nome", "Tempo(s)", "Pontuação");

  char linha[100];
  while (fgets(linha, sizeof(linha), f)) {
    char nome[50];
    double tempo, score;
    if (sscanf(linha, "%49[^,],%lf,%lf", nome, &tempo, &score) == 3) {
      printf("%-20s %-10.2f %-10.2f\n", nome, tempo, score);
    }
  }
  fclose(f);
}

void limpar_ranking() {
  FILE *f = fopen(ARQUIVO_RANKING, "w");
  if (f)
    fclose(f);
  printf("Ranking limpo com sucesso.\n");
}
