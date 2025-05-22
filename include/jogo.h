#ifndef JOGO_H
#define JOGO_H

#include "dados.h"

typedef struct {
    int suspeitos[USADOS_POR_CATEGORIA]; 
    int armas[USADOS_POR_CATEGORIA];
    int locais[USADOS_POR_CATEGORIA];
} ItensUsados;

typedef struct {
    int suspeitos; 
    int armas;
    int locais;
} ItensChute;

void gerar_rodada(ItensUsados *itens);

int validar_resultado(ItensChute *chute, ItensUsados *itens);

#endif
