// Inclui o arquivo de cabeçalho "player.h".
// Este arquivo provavelmente contém declarações relacionadas ao jogador,
// possivelmente a declaração das variáveis globais playerX e playerY se
// elas forem usadas em outros arquivos, ou outras funções específicas do jogador.
#include "player.h"


// Inclui o arquivo de cabeçalho "mapa.h".
// Essencial porque a função clearPlayer() precisa acessar a matriz 'map'
// para saber qual caractere do mapa restaurar quando o jogador se move.
// Deve conter a declaração da matriz global 'char map[MAP_HEIGHT][MAP_WIDTH];'
// e as constantes MAP_HEIGHT e MAP_WIDTH.
#include "mapa.h"


// Inclui o arquivo de cabeçalho "screen.h".
// Necessário para as funções de manipulação da tela, como screenGotoxy (para
// posicionar o cursor) e screenSetColor (para definir as cores do texto e fundo).
// Também deve definir as constantes de cor como YELLOW, BLACK, WHITE.
#include "screen.h"


// Variáveis globais que armazenam a posição atual do jogador no mapa.
// 'playerX' é a coordenada da coluna (horizontal).
// 'playerY' é a coordenada da linha (vertical).
// São inicializadas com uma posição inicial (40, 12).
int playerX = 40;
int playerY = 12;


/**
 * @brief Desenha o caractere do jogador na sua posição atual no mapa.
 *
 * Move o cursor para as coordenadas (playerX, playerY), define a cor
 * do jogador (amarelo sobre preto) e imprime o caractere 'o' para representá-lo.
 */
void drawPlayer() {
  // Move o cursor do console para a posição atual do jogador (playerX, playerY).
  screenGotoxy(playerX, playerY);
  // Define a cor do texto para amarelo (YELLOW) e o fundo para preto (BLACK)
  // para destacar o jogador. YELLOW e BLACK são constantes de cor.
  screenSetColor(YELLOW, BLACK);
  // Imprime o caractere 'o' para representar o jogador na tela.
  printf("o");
}


/**
 * @brief Apaga o caractere do jogador da sua posição atual no mapa,
 * restaurando o caractere original do mapa que estava naquela posição.
 *
 * Antes de o jogador se mover para uma nova posição, esta função é chamada
 * para limpar sua representação visual da posição antiga.
 */
void clearPlayer() {
  // Move o cursor do console para a posição atual do jogador (playerX, playerY),
  // que é a posição de onde ele está prestes a se mover.
  screenGotoxy(playerX, playerY);
  // Obtém o caractere original do mapa que está sob a posição atual do jogador.
  // 'map' é a matriz global que armazena o layout do mapa.
  char tile = map[playerY][playerX];
  // Define a cor do texto para branco (WHITE) e o fundo para preto (BLACK),
  // que é a cor padrão usada para desenhar o mapa (conforme visto em drawMap()).
  screenSetColor(WHITE, BLACK);
  // Imprime o caractere original do mapa ('tile') de volta na posição,
  // efetivamente "apagando" o jogador e restaurando a aparência do mapa.
  printf("%c", tile);
}
