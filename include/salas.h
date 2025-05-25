#ifndef SALAS_H
#define SALAS_H

#include <stdbool.h>
#include "pistas.h"

typedef struct {
  int Xinicial;
  int Xfinal;
  int Yinicial;
  int Yfinal;
} tamanhoSala;

extern tamanhoSala tamanhoAuditorio;
extern tamanhoSala tamanhoBiblioteca;
extern tamanhoSala tamanhoSala401;
extern tamanhoSala tamanhoCopa;
extern tamanhoSala tamanhoGaragino;
extern tamanhoSala tamanhoSalaProf;
extern tamanhoSala tamanhoSalaTI;
extern tamanhoSala tamanhoPraca;

void initNomesNasSalas();
bool verificarSala(tamanhoSala sala, const char *clue1, const char *clue2);

#endif
