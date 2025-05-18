#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef RANKING_H
#define RANKING_H

typedef struct {
    char nome[50];
    double tempo;
    int acertou;
} RankingEntry;

void salvar_ranking(const char *nome, double tempo, int acertou);
void mostrar_ranking();
void limpar_ranking();
int validar_nome(const char *nome);

#endif