#ifndef RANKING_H
#define RANKING_H

int validar_nome(const char *nome);
void salvar_ranking(const char *nome, double tempo, int acertou);
void mostrar_ranking();
void limpar_ranking();

#endif
