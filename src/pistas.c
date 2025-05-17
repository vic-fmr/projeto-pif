#include <stdio.h>
#include <string.h>
#include "pistas.h"
#include "dados.h"

void criar_pista(Pista* pista, TipoPista tipo, const char* formato, const char* s1, const char* s2) {
    pista->tipo = tipo;
    if (s2)
        snprintf(pista->texto, sizeof(pista->texto), formato, s1, s2);
    else
        snprintf(pista->texto, sizeof(pista->texto), formato, s1);
}

void gerar_pistas(Pista pistas[12], ItensUsados itens) {
    criar_pista(&pistas[0], TIPO_NEGACAO, "O local não foi %s.", NOMES_LOCAIS[itens.locais[2]], NULL);
    criar_pista(&pistas[1], TIPO_NEGACAO, "O assassino não foi %s.", NOMES_SUSPEITOS[itens.suspeitos[1]], NULL);
    criar_pista(&pistas[2], TIPO_NEGACAO, "A arma não foi %s.", NOMES_ARMAS[itens.armas[1]], NULL);

    criar_pista(&pistas[3], TIPO_OU, "O assassino é %s ou a arma foi %s.", NOMES_SUSPEITOS[itens.suspeitos[0]], NOMES_ARMAS[itens.armas[2]]);
    criar_pista(&pistas[4], TIPO_OU, "A arma foi %s ou o local foi %s.", NOMES_ARMAS[itens.armas[0]], NOMES_LOCAIS[itens.locais[1]]);

    criar_pista(&pistas[5], TIPO_SE_ENTAO, "Se o assassino é %s, então a arma não foi %s.", NOMES_SUSPEITOS[itens.suspeitos[0]], NOMES_ARMAS[itens.armas[1]]);
    criar_pista(&pistas[6], TIPO_SE_ENTAO, "Se o local foi %s, então o assassino não foi %s.", NOMES_LOCAIS[itens.locais[1]], NOMES_SUSPEITOS[itens.suspeitos[2]]);
    criar_pista(&pistas[7], TIPO_SE_ENTAO, "Se a arma foi %s, então o local foi %s.", NOMES_ARMAS[itens.armas[0]], NOMES_LOCAIS[itens.locais[0]]);
    criar_pista(&pistas[8], TIPO_SE_ENTAO, "Se o local foi %s, então o assassino foi %s.", NOMES_LOCAIS[itens.locais[0]], NOMES_SUSPEITOS[itens.suspeitos[0]]);
    criar_pista(&pistas[9], TIPO_SE_ENTAO, "Se o assassino foi %s, então a arma foi %s.", NOMES_SUSPEITOS[itens.suspeitos[2]], NOMES_ARMAS[itens.armas[1]]);
    criar_pista(&pistas[10], TIPO_SE_ENTAO, "Se a arma foi %s, então o local não foi %s.", NOMES_ARMAS[itens.armas[2]], NOMES_LOCAIS[itens.locais[1]]);
    criar_pista(&pistas[11], TIPO_SE_ENTAO, "Se o local foi %s, então a arma não foi %s.", NOMES_LOCAIS[itens.locais[2]], NOMES_ARMAS[itens.armas[0]]);
}