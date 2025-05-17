#ifndef JOGO_H
#define JOGO_H

#include "dados.h"

typedef struct {
    int suspeitos[USADOS_POR_CATEGORIA]; 
    int armas[USADOS_POR_CATEGORIA];
    int locais[USADOS_POR_CATEGORIA];
} ItensUsados;

void gerar_rodada(ItensUsados *itens);

#endif
