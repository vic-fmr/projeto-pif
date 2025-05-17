#ifndef PISTAS_H
#define PISTAS_H

#include "jogo.h"

typedef enum {
    TIPO_NEGACAO,
    TIPO_OU,
    TIPO_SE_ENTAO
} TipoPista;

typedef struct {
    TipoPista tipo;
    char texto[128];
} Pista;

void gerar_pistas(Pista pistas[12], ItensUsados itens);

#endif