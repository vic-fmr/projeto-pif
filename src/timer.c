/**
 * timer.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */


// Inclui o arquivo de cabeçalho "timer.h".
// Este arquivo deve conter as declarações (protótipos) das funções
// definidas neste arquivo (timerInit, timerDestroy, etc.).
#include "timer.h"


// Inclui <sys/time.h> para a função gettimeofday e a estrutura timeval.
// gettimeofday é usada para obter o tempo atual com precisão de microssegundos.
#include <sys/time.h>


// Inclui <stdio.h> para a função printf, usada em timerPrint.
#include <stdio.h>


// Variáveis estáticas globais (visíveis apenas dentro deste arquivo .c).
// 'timer': Armazena o ponto no tempo a partir do qual o intervalo de tempo é medido (o "início" do timer).
static struct timeval timer;
// 'now': Usada para armazenar o tempo atual ao calcular a diferença.
static struct timeval now;
// 'delay': Armazena o intervalo de tempo em milissegundos que o timer deve medir.
// Um valor de -1 indica que o timer não está ativo ou não foi inicializado.
static int delay = -1;


/**
 * @brief Inicializa o timer com um valor de atraso especificado em milissegundos.
 *
 * Define o intervalo de 'delay' e registra o tempo atual como o ponto de
 * partida para a contagem do tempo.
 *
 * @param valueMilliSec O valor do atraso (intervalo) em milissegundos.
 */
void timerInit(int valueMilliSec) {
  // Define o valor do atraso.
  delay = valueMilliSec;
  // gettimeofday obtém o tempo atual e o armazena na estrutura 'timer'.
  // O segundo argumento (timezone) é geralmente NULL em sistemas POSIX modernos.
  gettimeofday(&timer, NULL); // Marca o tempo de início.
}


/**
 * @brief "Destrói" ou desativa o timer.
 *
 * Define o 'delay' como -1, indicando que o timer não está mais configurado
 * para um intervalo específico.
 */
void timerDestroy() {
  // Define 'delay' como -1 para indicar que o timer não está ativo.
  delay = -1;
}


/**
 * @brief Atualiza o valor do atraso do timer e redefine o tempo de início.
 *
 * Similar a timerInit, mas pode ser usado para mudar o intervalo de um timer
 * já existente e reiniciar sua contagem.
 *
 * @param valueMilliSec O novo valor do atraso (intervalo) em milissegundos.
 */
void timerUpdateTimer(int valueMilliSec) {
  // Atualiza o valor do atraso.
  delay = valueMilliSec;
  // Registra o novo tempo de início.
  gettimeofday(&timer, NULL);
}


/**
 * @brief Calcula a diferença de tempo em milissegundos desde a última vez
 * que o timer foi iniciado ou atualizado.
 *
 * @return int A diferença de tempo em milissegundos.
 */
int getTimeDiff() {
  // Obtém o tempo atual e armazena em 'now'.
  gettimeofday(&now, NULL);


  // Calcula a diferença de tempo.
  // now.tv_sec e timer.tv_sec são os segundos.
  // now.tv_usec e timer.tv_usec são os microssegundos.
  // 1. Calcula a diferença em segundos e converte para microssegundos (multiplica por 1.000.000).
  // 2. Adiciona a diferença em microssegundos.
  // 3. Divide o resultado total em microssegundos por 1000 para obter milissegundos.
  long diff_usec = (now.tv_sec - timer.tv_sec) * 1000000L + (now.tv_usec - timer.tv_usec);
  long diff_msec = diff_usec / 1000L;


  return (int)diff_msec; // Converte para int e retorna.
}


/**
 * @brief Verifica se o tempo de 'delay' configurado já passou.
 *
 * Se o tempo passou, esta função também redefine o tempo de início do timer
 * para o momento atual, tornando-a adequada para verificar intervalos periódicos.
 *
 * @return int Retorna 1 se o tempo de 'delay' passou, 0 caso contrário.
 */
int timerTimeOver() {
  int ret = 0; // Valor de retorno, inicializado como 0 (tempo não passou).


  // Se 'delay' for negativo (timer não inicializado/destruído), considera que o tempo não passou.
  if (delay < 0) {
    return 0;
  }


  // Compara a diferença de tempo atual com o 'delay' configurado.
  if (getTimeDiff() >= delay) { // Usa >= para garantir que mesmo um tempo exato seja capturado.
    ret = 1; // Marca que o tempo passou.
    // Reseta o tempo de início do timer para o tempo atual ('now').
    // Isso faz com que a próxima verificação de timerTimeOver() comece a contar
    // a partir deste momento.
    gettimeofday(&timer, NULL); // Poderia usar 'timer = now;' se 'now' foi obtido recentemente em getTimeDiff.
                                // Mas chamar gettimeofday de novo é mais seguro para precisão.
  }


  return ret; // Retorna 1 se o tempo passou, 0 caso contrário.
}


/**
 * @brief Imprime a diferença de tempo atual em milissegundos no console.
 *
 * Útil para depuração ou para exibir informações de tempo.
 */
void timerPrint() {
  // Chama getTimeDiff() para obter a diferença de tempo atual e a imprime.
  printf("Timer:  %dms", getTimeDiff()); // Adicionado "ms" para clareza.
}
