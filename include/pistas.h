#ifndef PISTAS_H
#define PISTAS_H

#include "jogo.h"

typedef enum { TIPO_NEGACAO, TIPO_OU, TIPO_SE_ENTAO } TipoPista;

typedef struct {
  TipoPista tipo;
  char texto[128];
  int id;
} Pista;

// Recebe um vetor de pistas e a lista dos itens sorteados para a rodada e retorna a lista de pistas.
void gerar_pistas(Pista pistas[12], ItensUsados itens);

void embaralhar_pistas(Pista pistas[12]);

#endif