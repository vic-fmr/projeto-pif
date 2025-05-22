#include <stdio.h>
#include "ranking.h"
#include "temporizador.h"

int main() {
    char nome[50];
    time_t inicio;
    int acertou = 0; 

   
    do {
        printf("Digite seu nome (sem vírgulas): ");
        scanf("%49s", nome);
    } while (!validar_nome(nome));

   
    iniciar_temporizador(&inicio);
    printf("=== DESCUBRA O ASSASSINO ===\n");
    

  
    double tempo = parar_temporizador(inicio);
    salvar_ranking(nome, tempo, acertou);

   
    int opcao;
    printf("\n1. Ver Ranking\n2. Limpar Ranking\n3. Sair\nEscolha: ");
    scanf("%d", &opcao);
    if (opcao == 1) mostrar_ranking();
    else if (opcao == 2) limpar_ranking();

    return 0;
}