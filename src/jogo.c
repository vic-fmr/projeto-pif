// Inclui a biblioteca padrão para funções de utilidade geral, como alocação de memória,
// controle de processos, conversões e, neste caso, geração de números aleatórios (rand, srand).
#include <stdlib.h>
// Inclui a biblioteca padrão para manipulação de tempo, usada aqui para obter uma "semente"
// para o gerador de números aleatórios (função time).
#include <time.h>
// Inclui o arquivo de cabeçalho "jogo.h". Este arquivo deve conter definições
// importantes para a lógica do jogo, como:
// - As estruturas ItensUsados (para os itens da rodada) e ItensChute (para o palpite do jogador).
// - Constantes como USADOS_POR_CATEGORIA (número de itens de cada categoria a serem sorteados/usados).
// - Constantes como TOTAL_SUSPEITOS, TOTAL_ARMAS, TOTAL_LOCAIS (número total de itens possíveis em cada categoria).
#include "jogo.h"
// Inclui o arquivo de cabeçalho "screen.h". Embora não usado diretamente neste trecho,
// pode ser necessário para outras partes do módulo ou ser uma inclusão padrão.
#include "screen.h"
// Inclui o arquivo de cabeçalho "dados.h". Poderia conter definições de dados brutos do jogo,
// mas as constantes de totais parecem ser gerenciadas via "jogo.h" neste contexto.
#include "dados.h"
// Inclui a biblioteca padrão de matemática. Não é utilizada neste trecho específico.
#include "math.h"


/**
 * @brief Sorteia um valor inteiro único que não está presente em um array existente.
 *
 * Esta função é usada para garantir que, ao selecionar múltiplos itens para uma categoria
 * (ex: vários suspeitos para mostrar ao jogador), não haja repetições.
 *
 * @param existentes Ponteiro para um array de inteiros contendo os valores já sorteados anteriormente
 * para esta mesma categoria e nesta mesma rodada.
 * @param quantidade O número de elementos válidos atualmente no array `existentes`.
 * @param max        O valor máximo (exclusive) para o sorteio (os valores sorteados serão de 0 a max-1).
 * @return int       Um valor inteiro sorteado que é único em relação ao array `existentes`.
 */
static int sortear_unico(int *existentes, int quantidade, int max) {
  int valor, repetido;
  do {
    // Gera um valor aleatório entre 0 (inclusive) e max (exclusive).
    valor = rand() % max;
    repetido = 0; // Assume inicialmente que o valor não é repetido.
    // Verifica se o valor sorteado já existe no array 'existentes'.
    for (int i = 0; i < quantidade; i++) {
      if (existentes[i] == valor) {
        repetido = 1; // Marca como repetido se encontrar o valor.
        break;        // Interrompe a busca, pois já encontrou uma repetição.
      }
    }
  } while (repetido); // Continua sorteando até encontrar um valor não repetido.
  return valor;
}


/**
 * @brief Gera os itens (suspeitos, armas, locais) para uma nova rodada do jogo.
 *
 * Preenche a estrutura ItensUsados com índices aleatórios e únicos para cada categoria.
 * O primeiro item sorteado para cada categoria ([0]) é considerado o "gabarito" da rodada.
 *
 * @param itens Ponteiro para uma estrutura ItensUsados que será preenchida com os
 * índices dos itens sorteados para a rodada.
 */
void gerar_rodada(ItensUsados *itens) {
  // Inicializa o gerador de números aleatórios usando o tempo atual como semente.
  // NOTA: Idealmente, srand() deve ser chamado apenas UMA VEZ no início do programa
  // para garantir melhor aleatoriedade e evitar sequências repetidas se chamado
  // muitas vezes em curtos períodos.
  srand(time(NULL));


  // Sorteia os suspeitos para a rodada.
  // USADOS_POR_CATEGORIA define quantos suspeitos diferentes serão selecionados.
  for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
    // Para cada um dos 'USADOS_POR_CATEGORIA' suspeitos, sorteia um índice único
    // de 0 até TOTAL_SUSPEITOS-1. O 'i' como 'quantidade' garante que o novo
    // suspeito seja diferente dos 'i' suspeitos já sorteados para esta rodada.
    itens->suspeitos[i] = sortear_unico(itens->suspeitos, i, TOTAL_SUSPEITOS);
  }


  // Sorteia as armas para a rodada, seguindo a mesma lógica dos suspeitos.
  for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
    itens->armas[i] = sortear_unico(itens->armas, i, TOTAL_ARMAS);
  }


  // Sorteia os locais para a rodada, seguindo a mesma lógica.
  for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
    itens->locais[i] = sortear_unico(itens->locais, i, TOTAL_LOCAIS);
  }
}


/**
 * @brief Valida o palpite (chute) do jogador contra o gabarito da rodada.
 *
 * Compara os itens escolhidos pelo jogador com os itens corretos da rodada atual.
 *
 * @param chute Ponteiro para uma estrutura ItensChute contendo os índices dos
 * itens escolhidos pelo jogador.
 * @param itens Ponteiro para uma estrutura ItensUsados contendo os itens da rodada atual,
 * onde o item na posição [0] de cada categoria é o correto (gabarito).
 * @return int  O número de acertos do jogador (0, 1, 2 ou 3).
 */
int validar_resultado(ItensChute *chute, ItensUsados *itens) {
  int acertos = 0; // Inicializa o contador de acertos.


  // OBSERVAÇÃO IMPORTANTE DO CÓDIGO ORIGINAL:
  // "O gabarito sempre será o item zero do vetor de itens usados."
  // Portanto, compara-se o chute do jogador com itens->armas[0], itens->suspeitos[0], etc.


  // Verifica se a arma escolhida pelo jogador é a arma correta da rodada.
  if (chute->armas == itens->armas[0]) {
    acertos++; // Incrementa o número de acertos.
  }
  // Verifica se o suspeito escolhido pelo jogador é o suspeito correto.
  if (chute->suspeitos == itens->suspeitos[0]) {
    acertos++;
  }
  // Verifica se o local escolhido pelo jogador é o local correto.
  if (chute->locais == itens->locais[0]) {
    acertos++;
  }
  return acertos; // Retorna o total de acertos.
}
