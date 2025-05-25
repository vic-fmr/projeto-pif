#include "ranking.h"
#include "temporizador.h"
#include <stdio.h>

int main() {
  char nome[50];
  time_t inicio;
  int acertou;

  do {
    printf("Digite seu nome (sem vírgulas): ");
    scanf("%49s", nome);
  } while (!validar_nome(nome));

  iniciar_temporizador(&inicio);

  // Simula lógica do jogo
  printf("=== DESCUBRA O ASSASSINO ===\n");

  printf("Você acertou o mistério? (1 = sim, 0 = não): ");
  scanf("%d", &acertou);

  double tempo = parar_temporizador(inicio);
  salvar_ranking(nome, tempo, acertou);

  int opcao;
  printf("\n1. Ver Ranking\n2. Limpar Ranking\n3. Sair\nEscolha: ");
  scanf("%d", &opcao);
  if (opcao == 1)
    mostrar_ranking();
  else if (opcao == 2)
    limpar_ranking();

  return 0;
}
