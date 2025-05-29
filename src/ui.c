// Inclui a biblioteca padrão de entrada/saída (para printf, fgets, getchar).
#include <stdio.h>
// Inclui para funções POSIX como sleep (embora não usada diretamente aqui,
// pode ser comum em contextos de UI de console para pausas).
// O uso principal aqui não é evidente, mas pode ser para alguma função de screen.h.
#include <unistd.h>
// Inclui o arquivo de cabeçalho "screen.h".
// Essencial para todas as funções de manipulação da tela: screenClear, screenSetColor, screenGotoxy.
// Também deve definir constantes de cor como BLACK, WHITE, LIGHTGRAY, CYAN, RED.
#include "screen.h"
// Inclui a biblioteca padrão para manipulação de strings (strlen, strcspn).
#include <string.h>
// Inclui o arquivo de cabeçalho "keyboard.h" (não usado diretamente neste trecho,
// mas pode ser parte do setup geral do projeto).
#include "keyboard.h"
// Inclui a biblioteca padrão para classificação de caracteres (isspace).
#include <ctype.h>


// Define o nome do arquivo de ranking (não usado diretamente neste arquivo,
// mas pode ser uma constante global do projeto definida aqui ou em outro header).
#define ARQUIVO_RANKING "ranking.csv"


/**
 * @brief Preenche uma área retangular da tela com uma cor de fundo sólida.
 *
 * Define a cor de foreground e background para a mesma cor e então imprime
 * espaços em toda a área especificada.
 *
 * @param largura Largura da área a ser pintada.
 * @param altura Altura da área a ser pintada.
 * @param cor_fundo A cor (do enum screenColor) a ser usada para o fundo.
 */
void pintar_fundo(int largura, int altura, int cor_fundo) {
  // Define a cor do texto (foreground) e do fundo para a mesma 'cor_fundo'.
  // Isso faz com que os espaços impressos tenham a cor de fundo desejada.
  screenSetColor(cor_fundo, cor_fundo); // As constantes de cor vêm de screen.h
  // Itera sobre cada linha da área.
  for (int y = 0; y < altura; y++) {
    // Move o cursor para o início da linha atual (coluna 0).
    screenGotoxy(0, y);
    // Itera sobre cada coluna da linha atual.
    for (int x = 0; x < largura; x++) {
      // Imprime um espaço. Como a cor de foreground e background são iguais,
      // isso efetivamente "pinta" a célula com a cor de fundo.
      printf(" ");
    }
  }
}


/**
 * @brief Exibe a tela inicial do jogo com arte ASCII e uma mensagem.
 *
 * Limpa a tela, pinta o fundo, exibe o título do jogo em arte ASCII
 * e aguarda o jogador pressionar Enter para continuar.
 */
void tela_inicial() {
  // Array de strings contendo a arte ASCII para o título do jogo.
  // Cada string é uma linha da arte.
  const char *arte[] = {
    
      "░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░        ",
      "░▒▓████████▓▒░▒▓██████▓▒░▒▓████████▓▒░▒▓██████▓▒░░▒▓█▓▒░        ",
      "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░        ",
      "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░            ",
      "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ░▒▓█▓▒░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░        ",
      "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░            ",
      "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒▒▓███▓▒░▒▓█▓▒░▒▓█▓▒░        ░▒▓████████▓▒░        ",
      "░▒▓██████▓▒░░▒▓████████▓▒░ ░▒▓█▓▒░  ░▒▓████████▓▒░▒▓█▓▒░            ",
      "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░        ",
      "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░            ",
      "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░        ",
      "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░            ",
      "░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▒░        ",
      "░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░    ",
      "", // Linha vazia para espaçamento
      "                         Um jogo de dedução e assassinatos acadêmicos.",
      "                               Pressione ENTER para começar..."
  };


  // Limpa a tela de qualquer conteúdo anterior.
  screenClear();
  // Pinta o fundo da tela de preto. (150 de largura, 45 de altura).
  // As dimensões devem corresponder ao tamanho do terminal esperado.
  pintar_fundo(150, 45, BLACK); // BLACK é uma constante de cor de screen.h
  // Define a cor do texto para branco e o fundo para preto para a arte ASCII.
  screenSetColor(WHITE, BLACK); // WHITE é uma constante de cor de screen.h


  // Calcula o número de linhas na arte ASCII.
  int linhas = sizeof(arte) / sizeof(arte[0]);
  // Define a linha inicial (y) para exibir a arte.
  int y = 3;


  // Itera sobre cada linha da arte ASCII.
  for (int i = 0; i < linhas; i++) {
    // Calcula a posição x para centralizar a linha atual da arte.
    // Assume uma largura de tela de 80 colunas para centralização.
    // Isso pode precisar de ajuste se a largura real da tela (150 usada em pintar_fundo) for diferente.
    int x = (80 - strlen(arte[i])) / 2;
    // Garante que x não seja negativo se a string for muito longa.
    if (x < 0) x = 0;
    // Move o cursor para a posição (x, y) calculada.
    screenGotoxy(x, y++); // Incrementa y para a próxima linha.
    // Imprime a linha atual da arte ASCII.
    printf("%s", arte[i]);
  }
  // Aguarda o jogador pressionar Enter para prosseguir.
  // getchar() lê um único caractere da entrada padrão.
  getchar();
}


/**
 * @brief Valida se um nome contém pelo menos um caractere não espacial.
 *
 * Usado para verificar se o nome inserido pelo jogador não é vazio ou apenas espaços.
 *
 * @param nome A string contendo o nome a ser validado.
 * @return int Retorna 1 se o nome for válido (contém não espaços), 0 caso contrário.
 */
int nome_valido(const char *nome) {
  // Itera sobre cada caractere do nome.
  for (int i = 0; nome[i] != '\0'; i++) {
    // isspace() verifica se o caractere é um espaço em branco (espaço, tab, nova linha, etc.).
    // Se encontrar um caractere que NÃO é um espaço, o nome é considerado válido.
    if (!isspace(nome[i])) return 1; // Nome válido.
  }
  // Se o loop terminar sem encontrar nenhum caractere não espacial, o nome é inválido.
  return 0; // Nome inválido (vazio ou só espaços).
}


/**
 * @brief Exibe a tela de instruções do jogo e solicita o nome do jogador.
 *
 * Limpa a tela, pinta o fundo, mostra a história do jogo, os comandos
 * e entra em um loop para obter um nome válido do jogador.
 *
 * @param nome_jogador Ponteiro para uma string onde o nome do jogador será armazenado.
 */
void mostrar_instrucoes(char *nome_jogador) {
  // Limpa a tela.
  screenClear();
  // Pinta o fundo de preto.
  pintar_fundo(150, 45, BLACK);
  // Define a cor do texto para branco e fundo para preto.
  screenSetColor(WHITE, BLACK);


  // Exibe o título da seção de instruções.
  screenGotoxy(20, 2);
  printf("====================================================");
  screenGotoxy(20, 3);
  printf("               LÓGICA FATAL - MISSÃO                "); // Título centralizado manualmente.
  screenGotoxy(20, 4);
  printf("====================================================");


  // Define a cor do texto para cinza claro para a descrição da história.
  screenSetColor(LIGHTGRAY, BLACK); // LIGHTGRAY é uma constante de cor.
  screenGotoxy(10, 6);
  printf("Um terrível assassinato aconteceu na CESAR School...");


  screenGotoxy(10, 8);
  printf("O Professor Diego foi encontrado sem vida em uma das salas.");
  screenGotoxy(10, 10);
  printf("Cabe a VOCÊ descobrir quem cometeu esse crime, com qual");
  screenGotoxy(10, 11);
  printf("arma e em qual local. Use as pistas lógicas para resolver!");


  // Exibe o cabeçalho da seção de comandos.
  screenGotoxy(10, 14);
  screenSetColor(CYAN, BLACK); // CYAN é uma constante de cor.
  printf(">> COMANDOS DO JOGO:");


  // Exibe a lista de comandos.
  screenSetColor(LIGHTGRAY, BLACK);
  screenGotoxy(12, 16);
  printf("W - mover para cima");
  screenGotoxy(12, 17);
  printf("A - mover para esquerda");
  screenGotoxy(12, 18);
  printf("S - mover para baixo");
  screenGotoxy(12, 19);
  printf("D - mover para direita");
  screenGotoxy(12, 20);
  printf("C - chutar uma solução");


  int tentativa = 0; // Flag para controlar se é a primeira tentativa de inserir o nome.
  // Loop para obter um nome válido do jogador.
  do {
    // Se não for a primeira tentativa (ou seja, o nome anterior foi inválido).
    if (tentativa) {
      // Limpa as linhas onde a mensagem de erro e o nome anterior foram exibidos.
      // Isso é feito "pintando" com espaços na cor de fundo.
      screenSetColor(WHITE, BLACK); // Garante que a limpeza seja com fundo preto.
      screenGotoxy(10, 24);
      printf("                                                      "); // Limpa linha do nome.
      screenGotoxy(10, 25);
      printf("                                                      "); // Limpa linha da mensagem de erro.
    }


    // Solicita ao jogador para digitar o nome.
    screenSetColor(WHITE, BLACK);
    screenGotoxy(10, 23);
    printf("Digite seu nome para começar:                          "); // Espaços para limpar possível texto anterior.
    screenGotoxy(10, 24); // Posiciona o cursor para a entrada do nome.
    // Lê o nome do jogador da entrada padrão (stdin).
    // fgets é mais seguro que gets, pois limita o número de caracteres lidos (49 + nulo).
    fgets(nome_jogador, 50, stdin);
    // Remove o caractere de nova linha ('\n') que fgets geralmente inclui no final da string.
    // strcspn retorna o índice da primeira ocorrência de '\n'.
    nome_jogador[strcspn(nome_jogador, "\n")] = '\0';


    // Valida o nome inserido.
    if (!nome_valido(nome_jogador)) {
      // Se o nome for inválido, exibe uma mensagem de erro em vermelho.
      screenSetColor(RED, BLACK); // RED é uma constante de cor.
      screenGotoxy(10, 25);
      printf("Nome inválido. Tente novamente.");
    }


    tentativa = 1; // Marca que pelo menos uma tentativa foi feita.
  } while (!nome_valido(nome_jogador)); // Continua o loop enquanto o nome não for válido.


  // Após obter um nome válido, exibe uma mensagem de boas-vindas.
  screenSetColor(WHITE, BLACK);
  screenGotoxy(10, 27);
  printf("Bem-vindo, %s! Pressione ENTER para iniciar a investigação!", nome_jogador);
  // Aguarda o jogador pressionar Enter para iniciar o jogo.
  getchar();
}
