// Inclui o arquivo de cabeçalho "salas.h".
// Este arquivo deve conter:
// - A definição da estrutura 'tamanhoSala'.
// - As declarações (protótipos) das funções initNomesNasSalas e verificarSala.
// - Possivelmente declarações extern das variáveis globais de tamanho das salas, se usadas em outros arquivos.
#include "salas.h"

// Inclui o arquivo de cabeçalho "dialogo.h".
// Necessário para a função showDialog, que é chamada dentro de verificarSala
// para exibir as pistas quando o jogador está em uma sala.
#include "dialogo.h"

// Inclui o arquivo de cabeçalho "player.h".
// Necessário para acessar as variáveis globais playerX e playerY, que armazenam
// a posição atual do jogador e são usadas em verificarSala.
#include "player.h"

// Inclui o arquivo de cabeçalho "mapa.h".
// Necessário para a função desenharNomeNoMapa (que modifica a matriz do mapa)
// e para a constante MAP_WIDTH usada na definição das dimensões das salas.
// Deve conter a declaração da função desenharNomeNoMapa e da constante MAP_WIDTH.
#include "mapa.h"

// Definição das dimensões de cada sala do jogo.
// 'tamanhoSala' é uma estrutura que provavelmente contém campos como:
//   int Xinicial;
//   int Xfinal;
//   int Yinicial;
//   int Yfinal;
// Estas variáveis globais definem as coordenadas retangulares de cada sala no mapa.
// MAP_WIDTH e MAP_HEIGHT (usado implicitamente, pois Yfinal pode ser MAP_HEIGHT-1) são constantes
// que definem as dimensões totais do mapa.

// Coordenadas para o Auditório:
// X (colunas) de 1 a 19, Y (linhas) de 1 a 4.
tamanhoSala tamanhoAuditorio = {1, 19, 1, 4};
// Coordenadas para a Biblioteca:
// X de 21 a 59, Y de 1 a 4.
tamanhoSala tamanhoBiblioteca = {21, 59, 1, 4};
// Coordenadas para a Sala 401:
// X de 61 até a penúltima coluna do mapa (MAP_WIDTH - 1), Y de 1 a 4.
tamanhoSala tamanhoSala401 = {61, MAP_WIDTH - 1, 1, 4};
// Coordenadas para a Copa:
// X de 61 até MAP_WIDTH - 1, Y de 6 até a penúltima linha antes da borda inferior (MAP_HEIGHT - 6).
tamanhoSala tamanhoCopa = {61, MAP_WIDTH - 1, 6, MAP_HEIGHT - 6}; // Assumindo que MAP_HEIGHT - 6 é uma linha válida.
// Coordenadas para o Garagino (provavelmente uma garagem ou área similar):
// X de 61 até MAP_WIDTH - 1, Y da quarta linha antes do fim (MAP_HEIGHT - 4) até a penúltima linha (MAP_HEIGHT - 1).
tamanhoSala tamanhoGaragino = {61, MAP_WIDTH - 1, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
// Coordenadas para a Sala dos Professores:
// X de 21 a 59, Y de MAP_HEIGHT - 4 até MAP_HEIGHT - 1.
tamanhoSala tamanhoSalaProf = {21, 59, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
// Coordenadas para a Sala de TI:
// X de 1 a 19, Y de MAP_HEIGHT - 4 até MAP_HEIGHT - 1.
tamanhoSala tamanhoSalaTI = {1, 19, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
// Coordenadas para a Praça:
// X de 1 a 19, Y de 6 até MAP_HEIGHT - 6.
tamanhoSala tamanhoPraca = {1, 19, 6, MAP_HEIGHT - 6};

/**
 * @brief Inicializa (desenha) os nomes das salas na matriz do mapa.
 *
 * Esta função chama desenharNomeNoMapa para cada sala, posicionando
 * o nome da sala em uma localização aproximada dentro de suas coordenadas definidas.
 */
void initNomesNasSalas() {
  // Desenha "AUDITORIO" no mapa.
  // A posição (tamanhoAuditorio.Xinicial + 4, 2) é relativa ao canto da sala.
  desenharNomeNoMapa(tamanhoAuditorio.Xinicial + 4, 2, "AUDITORIO");
  // Desenha "BIBLIOTECA" no mapa.
  desenharNomeNoMapa(tamanhoBiblioteca.Xinicial + 10, 2, "BIBLIOTECA");
  // Desenha "SALA 401" no mapa.
  desenharNomeNoMapa(tamanhoSala401.Xinicial + 5, 2, "SALA 401");
  // Desenha "COPA" no mapa.
  desenharNomeNoMapa(tamanhoCopa.Xinicial + 10, 10, "COPA");
  // Desenha "GARAGINO" no mapa.
  // MAP_HEIGHT - 3 é usado para posicionar o nome perto da parte inferior da sala.
  desenharNomeNoMapa(tamanhoGaragino.Xinicial + 8, MAP_HEIGHT - 3, "GARAGINO");
  // Desenha "SALA DOS PROFESSORES" no mapa.
  desenharNomeNoMapa(tamanhoSalaProf.Xinicial + 10, MAP_HEIGHT - 3, "SALA DOS PROFESSORES");
  // Desenha "SALA DE TI" no mapa.
  desenharNomeNoMapa(tamanhoSalaTI.Xinicial + 4, MAP_HEIGHT - 3, "SALA DE TI");
  // Desenha "PRACA" no mapa.
  desenharNomeNoMapa(tamanhoPraca.Xinicial + 4, 10, "PRACA");
}

/**
 * @brief Verifica se a posição atual do jogador está dentro dos limites de uma sala específica.
 *
 * Se o jogador estiver dentro da sala, esta função chama showDialog para exibir
 * as pistas associadas a essa sala.
 *
 * @param sala Estrutura tamanhoSala contendo as coordenadas da sala a ser verificada.
 * @param clue1 A primeira pista a ser exibida se o jogador estiver na sala.
 * @param clue2 A segunda pista a ser exibida (pode ser uma string vazia se não houver segunda pista).
 * @return bool Retorna true se o jogador estiver dentro da sala, false caso contrário.
 * A biblioteca stdbool.h precisa ser incluída para usar o tipo 'bool' diretamente,
 * ou um typedef (ex: int) pode ser usado. Assumindo que 'bool' está definido.
 */
bool verificarSala(tamanhoSala sala, const char *clue1, const char *clue2) {
  // playerX e playerY são as coordenadas globais da posição atual do jogador.
  // Verifica se a coordenada X do jogador está entre Xinicial e Xfinal da sala (inclusive).
  // E verifica se a coordenada Y do jogador está entre Yinicial e Yfinal da sala (inclusive).
  if (playerX >= sala.Xinicial && playerX <= sala.Xfinal &&
      playerY >= sala.Yinicial && playerY <= sala.Yfinal) {
    // Se o jogador estiver dentro dos limites da sala:
    // Chama showDialog para exibir as pistas associadas a esta sala.
    showDialog(clue1, clue2);
    // Retorna true, indicando que o jogador está na sala.
    return true;
  }
  // Se o jogador não estiver dentro dos limites da sala:
  // Retorna false.
  return false;
}
