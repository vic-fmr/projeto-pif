#include "temporizador.h"

void iniciar_temporizador(time_t *inicio) {
    *inicio = time(NULL);
}

double parar_temporizador(time_t inicio) {
    return difftime(time(NULL), inicio);
}