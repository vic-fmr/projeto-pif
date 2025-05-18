#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <time.h>

void iniciar_temporizador(time_t *inicio);
double parar_temporizador(time_t inicio);

#endif