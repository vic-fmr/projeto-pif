#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "dados.h"

static int sortear_unico(int *existentes, int quantidade, int max) {
    int valor, repetido;
    do {
        valor = rand() % max;
        repetido = 0;
        for (int i = 0; i < quantidade; i++) {
            if (existentes[i] == valor) {
                repetido = 1;
                break;
            }
        }
    } while (repetido);
    return valor;
}

void gerar_rodada(ItensUsados *itens) {
    srand(time(NULL));

    for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
        itens->suspeitos[i] = sortear_unico(itens->suspeitos, i, TOTAL_SUSPEITOS);
    }

    for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
        itens->armas[i] = sortear_unico(itens->armas, i, TOTAL_ARMAS);
    }

    for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
        itens->locais[i] = sortear_unico(itens->locais, i, TOTAL_LOCAIS);
    }
}
