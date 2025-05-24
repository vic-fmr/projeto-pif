#ifndef JOGO_H
#define JOGO_H

#include "dados.h"

// Struct para os itens usados, sao vetores de inteiros. Os valores das string estão em dados.h, aqui só temos index.
typedef struct {
  int suspeitos[USADOS_POR_CATEGORIA];
  int armas[USADOS_POR_CATEGORIA];
  int locais[USADOS_POR_CATEGORIA];
} ItensUsados;

// Struct para ser preenchido com os chutes. Aqui não são vetores e sim apenas numeros inteiros.
typedef struct {
  int suspeitos;
  int armas;
  int locais;
} ItensChute;

// Função que recebe o ponteiro onde serão armazenado os itens da rodada e retorna os itens sorteados
void gerar_rodada(ItensUsados *itens);

int validar_resultado(ItensChute *chute, ItensUsados *itens);

#endif
