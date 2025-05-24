// // Arquivo para testar as criacao de pistas. usar como base quando for
// integrar na Main.

// #include "../include/jogo.h"
// #include "../include/pistas.h"
// #include <stdio.h>

// int main() {
//     ItensUsados itens;
//     Pista pistas[12];

//     gerar_rodada(&itens);
//     gerar_pistas(pistas, itens);

//     printf("=== PISTAS DA RODADA! ===\n\n");
//     for (int i = 0; i < 12; i++) {
//         printf("Pista %02d: %s\n", i + 1, pistas[i].texto);
//     }

//     ItensChute chute = {
//         .suspeitos = 1,
//         .armas = 0,
//         .locais = 1
//     };

//     int resultado = validar_resultado(&chute, &itens);
//     printf("%d\n", resultado);

//     return 0;
// }