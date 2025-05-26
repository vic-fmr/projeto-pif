#include "temporizador.h"

void iniciar_temporizador(time_t *inicio) {
  *inicio = time(NULL);
}

double parar_temporizador(time_t inicio) {
  time_t fim = time(NULL);
  return difftime(fim, inicio); // tempo em segundos
}