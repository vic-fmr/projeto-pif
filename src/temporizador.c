// Inclui o arquivo de cabeçalho "temporizador.h".
// Este arquivo deve conter as declarações (protótipos) das funções
// iniciar_temporizador e parar_temporizador.
// Também deve incluir <time.h> se o tipo time_t for usado nos protótipos.
#include "temporizador.h"
// Nota: "temporizador.h" deve incluir <time.h> para que o tipo time_t seja conhecido.
// Se não incluir, a linha abaixo seria necessária aqui ou em "temporizador.h".
// #include <time.h> // Para time_t, time(), difftime()

/**
 * @brief Inicia um temporizador, registrando o tempo de início.
 *
 * Armazena o tempo atual (obtido de time(NULL)) na variável
 * apontada por 'inicio'.
 *
 * @param inicio Ponteiro para uma variável do tipo time_t onde o tempo
 * de início será armazenado.
 */
void iniciar_temporizador(time_t *inicio) {
  // time(NULL) retorna o tempo atual do calendário como um valor time_t.
  // O valor retornado é atribuído à variável para a qual 'inicio' aponta.
  // Isso marca o ponto de partida da contagem do tempo.
  *inicio = time(NULL);
}

/**
 * @brief Para um temporizador e calcula a duração em segundos desde o início.
 *
 * Calcula a diferença entre o tempo atual e o tempo de 'inicio' fornecido.
 *
 * @param inicio O valor time_t que representa o momento em que o temporizador foi iniciado.
 * @return double A duração em segundos como um valor double.
 */
double parar_temporizador(time_t inicio) {
  // Obtém o tempo atual do calendário, marcando o ponto final da contagem.
  time_t fim = time(NULL);

  // difftime(fim, inicio) calcula a diferença em segundos entre 'fim' e 'inicio'.
  // Retorna a diferença como um valor do tipo double.
  return difftime(fim, inicio); // Retorna o tempo decorrido em segundos.
}
