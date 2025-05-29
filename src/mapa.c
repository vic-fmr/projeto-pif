// Inclui o arquivo de cabeçalho "mapa.h".
// Este arquivo deve conter as definições das constantes MAP_HEIGHT e MAP_WIDTH,
// a declaração da variável global 'map', e os protótipos das funções
// initMap, drawMap, e possivelmente desenharNomeNoMapa (se for usada externamente).
#include "mapa.h"


// Inclui o arquivo de cabeçalho "salas.h".
// Provavelmente contém a declaração da função initNomesNasSalas e
// possivelmente definições relacionadas às salas do mapa.
#include "salas.h"


// Inclui o arquivo de cabeçalho "screen.h".
// Essencial para a manipulação da tela, fornecendo funções como
// screenGotoxy (para posicionar o cursor) e screenSetColor (para definir cores).
// Também deve definir constantes de cor como WHITE e BLACK.
#include "screen.h"


// Inclui a biblioteca padrão de entrada/saída do C.
// Necessária para a função printf, usada para desenhar os caracteres do mapa na tela.
#include <stdio.h>


// Declaração da matriz global que representa o mapa do jogo.
// MAP_HEIGHT e MAP_WIDTH são constantes que definem as dimensões do mapa.
// Esta matriz armazenará os caracteres que compõem o layout do mapa (paredes, espaços, etc.).
char map[MAP_HEIGHT][MAP_WIDTH];


/**
 * @brief Desenha uma string (nome) em uma posição específica da matriz do mapa.
 *
 * Modifica diretamente a matriz 'map' global para embutir o nome no layout do mapa.
 *
 * @param x Coordenada X (coluna) inicial no mapa onde o nome começará a ser desenhado.
 * @param y Coordenada Y (linha) no mapa onde o nome será desenhado.
 * @param nome A string contendo o nome a ser desenhado no mapa.
 */
void desenharNomeNoMapa(int x, int y, const char *nome) {
  // Itera sobre cada caractere da string 'nome' até encontrar o terminador nulo '\0'.
  for (int i = 0; nome[i] != '\0'; i++) {
    // Verifica se a posição atual para desenhar o caractere (x + i) está dentro dos limites da largura do mapa.
    if (x + i < MAP_WIDTH) {
      // Atribui o caractere atual do nome à posição correspondente na matriz do mapa.
      map[y][x + i] = nome[i];
    }
  }
}


/**
 * @brief Inicializa a matriz do mapa com seu layout base (paredes, espaços, portas).
 *
 * Esta função define a estrutura fundamental do mapa, preenchendo a matriz 'map'
 * com caracteres que representam paredes, espaços vazios e aberturas para portas.
 * Também chama initNomesNasSalas para adicionar nomes de locais ao mapa.
 */
void initMap() {
  // Itera sobre cada linha do mapa.
  for (int y = 0; y < MAP_HEIGHT; y++) {
    // Itera sobre cada coluna do mapa (começando de x=1, possivelmente para reservar x=0 para algo ou por um off-by-one).
    // Se a intenção é cobrir todo o mapa, o loop de x deveria começar de 0.
    // No entanto, as bordas externas são tratadas especificamente para x=1 e x=MAP_WIDTH-1 mais abaixo,
    // o que sugere que x=0 e y=0 podem não ser usados ou são tratados como parte da borda.
    // Ajuste: O loop original começava em x=1. Se as bordas são em x=0 e x=MAP_WIDTH-1,
    // o loop deveria ser de x=0 a x < MAP_WIDTH. A lógica atual parece colocar
    // as bordas em x=1 e x=MAP_WIDTH-1, o que é incomum se 0-indexed.
    // Assumindo que a intenção é preencher todo o mapa, incluindo as bordas:
    for (int x = 0; x < MAP_WIDTH; x++) { // Modificado para x=0 para cobrir toda a largura


      // Lógica inicial para definir paredes internas e espaços.
      // Esta seção parece criar uma estrutura de salas internas.
      if (x == 20 || x == MAP_WIDTH - 20) { // Paredes verticais internas.
        map[y][x] = '|';
      } else if (y == 5 || y == MAP_HEIGHT - 5) { // Paredes horizontais internas.
        map[y][x] = '-';
      } else {
        map[y][x] = ' '; // Espaço vazio padrão.
      }


      // Lógica para criar aberturas (portas) nas paredes.
      // Estas condições sobrescrevem os caracteres de parede ou espaço definidos anteriormente.
      // Portas verticais:
      if (x == 5 || x == 6 || x == 31 || x == 32 || x == MAP_WIDTH - 4 || x == MAP_WIDTH - 5) {
        map[y][x] = ' '; // Define como espaço, criando uma abertura.
      }
      // Portas horizontais:
      if (y == 2 || y == 10 || y == MAP_HEIGHT - 2) {
        map[y][x] = ' '; // Define como espaço, criando uma abertura.
      }


      // Lógica para definir as bordas externas do mapa.
      // Esta lógica deve sobrescrever qualquer coisa definida anteriormente para as posições de borda.
      if (x == 0 || x == MAP_WIDTH - 1) { // Bordas verticais externas (coluna 0 e última coluna).
        map[y][x] = '|';
      }
      if (y == 0 || y == MAP_HEIGHT - 1) { // Bordas horizontais externas (linha 0 e última linha).
        map[y][x] = '-';
      }
    }
  }
  // Após definir a estrutura base do mapa, chama uma função para inicializar/desenhar
  // os nomes das salas diretamente na matriz do mapa.
  // initNomesNasSalas() provavelmente usa desenharNomeNoMapa() internamente.
  initNomesNasSalas();
}


/**
 * @brief Desenha o conteúdo da matriz 'map' na tela do console.
 *
 * Itera sobre a matriz 'map' e usa funções da biblioteca 'screen.h'
 * para posicionar o cursor e imprimir cada caractere do mapa na tela.
 */
void drawMap() {
  // Itera sobre cada linha da matriz do mapa.
  for (int y = 0; y < MAP_HEIGHT; y++) {
    // Itera sobre cada coluna da matriz do mapa.
    for (int x = 0; x < MAP_WIDTH; x++) {
      // Move o cursor do console para a posição (x, y) correspondente.
      screenGotoxy(x, y);
      // Define a cor do texto para branco e o fundo para preto (cores padrão para o mapa).
      // WHITE e BLACK são constantes de cor definidas em "screen.h".
      screenSetColor(WHITE, BLACK);
      // Imprime o caractere armazenado na posição map[y][x] na tela.
      printf("%c", map[y][x]);
    }
  }
  // Nota: Geralmente, após desenhar tudo, uma chamada a screenUpdate() seria necessária
  // para garantir que todas as alterações sejam exibidas, dependendo da biblioteca de tela.
  // No entanto, ela não está presente aqui, o que implica que ou printf atualiza
  // diretamente, ou screenUpdate() é chamada pela função que chamou drawMap().
}
