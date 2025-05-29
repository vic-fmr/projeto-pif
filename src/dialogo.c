// Inclui o arquivo de cabeçalho "dialogo.h".
// Este arquivo provavelmente contém a declaração da função showDialog.
#include "dialogo.h"


// Inclui o arquivo de cabeçalho "screen.h".
// Este arquivo é crucial para a manipulação da tela, devendo declarar funções
// como screenSetColor, screenGotoxy, e constantes de cor (ex: WHITE, BLACK).
#include "screen.h"


// Inclui a biblioteca padrão de entrada/saída do C.
// Necessária para a função printf, usada para exibir texto.
#include <stdio.h>


// Inclui a biblioteca padrão de manipulação de strings do C.
// Necessária para a função strlen, usada para obter o comprimento de uma string.
#include <string.h>


// Inclui o arquivo de cabeçalho "mapa.h".
// Este arquivo provavelmente define constantes relacionadas ao mapa do jogo,
// como MAP_HEIGHT (altura do mapa) e MAP_WIDTH (largura do mapa).
#include "mapa.h"


/**
 * @brief Exibe uma caixa de diálogo na tela contendo duas pistas.
 *
 * A caixa de diálogo é posicionada abaixo da área do mapa e tem uma altura
 * de 5 linhas. A primeira linha serve como um título para a seção de dicas.
 * As duas pistas fornecidas são exibidas nas linhas subsequentes.
 *
 * @param clue1 Uma string constante representando a primeira pista a ser exibida.
 * @param clue2 Uma string constante representando a segunda pista a ser exibida.
 */
void showDialog(const char *clue1, const char *clue2) {
  // Define a cor do texto como branco (WHITE) e a cor de fundo como preto (BLACK).
  // Estas constantes de cor devem ser definidas em "screen.h" ou um arquivo similar.
  screenSetColor(WHITE, BLACK);


  // Loop para iterar sobre as linhas da caixa de diálogo.
  // A caixa de diálogo começa em MAP_HEIGHT (linha abaixo do mapa) e tem 5 linhas de altura.
  for (int y = MAP_HEIGHT; y < MAP_HEIGHT + 5; y++) {
    // Loop para iterar sobre as colunas da caixa de diálogo (largura do mapa).
    for (int x = 0; x < MAP_WIDTH; x++) {
      // Move o cursor do terminal para a posição (x, y) atual.
      screenGotoxy(x, y);


      // Verifica se está processando a primeira linha da caixa de diálogo (linha do título).
      if (y == MAP_HEIGHT) {
        // Se estiver na coluna x=2, imprime o texto do título.
        if (x == 2)
          printf("| Dicas encontradas no local |");
        // Caso contrário, se estiver nas colunas antes do início do título (x < 2)
        // ou depois do fim do título, imprime '=' para formar uma borda horizontal.
        // strlen("| Dicas encontradas no local |") calcula o comprimento do título.
        else if (x < 2 || x > 1 + strlen("| Dicas encontradas no local |"))
          printf("=");
        // Pula para a próxima iteração do loop interno (coluna x),
        // pois esta célula da linha do título já foi tratada.
        continue;
      }
      // Para as outras linhas da caixa de diálogo (abaixo da linha do título),
      // imprime um espaço em branco para limpar qualquer conteúdo anterior.
      printf(" ");
    }
  }


  // Após limpar e desenhar a estrutura da caixa de diálogo:


  // Move o cursor para a posição onde a primeira pista será exibida.
  // (coluna 1, terceira linha da caixa de diálogo - MAP_HEIGHT + 2).
  screenGotoxy(1, MAP_HEIGHT + 2);
  // Imprime a primeira pista.
  printf("%s", clue1);


  // Move o cursor para a posição onde a segunda pista será exibida.
  // (coluna 1, quarta linha da caixa de diálogo - MAP_HEIGHT + 3).
  screenGotoxy(1, MAP_HEIGHT + 3);
  // Imprime a segunda pista.
  printf("%s", clue2);


  // Nota: Não há uma chamada explícita a screenUpdate() aqui.
  // Dependendo da biblioteca de tela, as alterações podem ser imediatas
  // ou podem exigir uma chamada de atualização em outro lugar.
}
