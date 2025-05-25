#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "screen.h"
#include "dados.h"
#include "math.h"

// função que sorteia valores não repetidos para a rodada
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

// Função que recebe o ponteiro onde serão armazenado os itens da rodada e retorna os itens sorteados
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

// funcao que recebe um objeto com os itens chutados pelo jogador e o gabarito do jogo e compara.
// OBS: O gabarito sempre será o item zero do vetor de itens usados.
int validar_resultado(ItensChute *chute, ItensUsados *itens) {
  int acertos = 0;
  if (chute->armas == itens->armas[0]) {
    acertos++;
  }
  if (chute->suspeitos == itens->suspeitos[0]) {
    acertos++;
  }
  if (chute->locais == itens->locais[0]) {
    acertos++;
  }
  return acertos;
}