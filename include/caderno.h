#ifndef CADERNO_H
#define CADERNO_H

// Incluir outras dependências que caderno.c precisa para suas funções públicas
#include "pistas.h" // Se Pista for passada ou retornada

void init_caderno();
void adicionar_pista_coletada(int id_pista_para_adicionar);
void gerenciarCaderno(); // Se quiser chamar de fora

#endif