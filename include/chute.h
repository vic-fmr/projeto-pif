#ifndef CHUTE_H
#define CHUTE_H

#include "screen.h"
#include "keyboard.h"
#include "jogo.h"

#define MODAL_WIDTH 40
#define MODAL_HEIGHT 12

ItensChute obter_chute_jogador(const ItensUsados *itens);
void mostrar_resultado_chute(int acertos, const char *nome, double tempo);

#endif