// Inclui os arquivos de cabeçalho necessários.
// "chute.h" provavelmente contém definições relacionadas à mecânica de "chute" ou palpite do jogador,
// como a estrutura ItensChute e ItensUsados, e possivelmente constantes como MODAL_WIDTH, MODAL_HEIGHT, etc.
// Também deve declarar as funções de manipulação de tela como screenSetColor, screenGotoxy, screenUpdate, keyhit, readch,
// e constantes de cor (WHITE, BLACK, GREEN, YELLOW), limites de tela (MAXX, MINX),
// arrays de nomes (NOMES_SUSPEITOS, NOMES_ARMAS, NOMES_LOCAIS) e USADOS_POR_CATEGORIA.
#include "chute.h"
// "ranking.h" deve conter protótipos de funções para gerenciar o ranking de jogadores,
// como salvar_ranking e mostrar_ranking.
#include "ranking.h"
// Biblioteca padrão para manipulação de strings (ex: strlen).
#include <string.h>
// Biblioteca padrão para funções gerais, incluindo alocação de memória,
// conversão de tipos e geração de números aleatórios (ex: rand).
#include <stdlib.h>

/**
 * @brief Limpa uma área retangular da tela, preenchendo-a com espaços.
 *
 * Esta função é usada para apagar o conteúdo de uma "janela modal" antes de desenhar novo conteúdo.
 *
 * @param x Coordenada X do canto superior esquerdo da área a ser limpa.
 * @param y Coordenada Y do canto superior esquerdo da área a ser limpa.
 * @param width Largura da área a ser limpa (em colunas).
 * @param height Altura da área a ser limpa (em linhas).
 */
void limpar_area_modal(int x, int y, int width, int height) {
  // Define a cor do texto como branco e o fundo como preto para a operação de limpeza.
  // WHITE e BLACK são constantes de cor que devem ser definidas em outro lugar (ex: chute.h ou screen.h).
  screenSetColor(WHITE, BLACK); // Função para definir cores do terminal/tela.
  // Itera por cada linha da área a ser limpa.
  for (int j = 0; j < height; j++) {
    // Move o cursor do terminal para o início da linha atual dentro da área.
    screenGotoxy(x, y + j); // Função para posicionar o cursor.
    // Itera por cada coluna da linha atual.
    for (int i = 0; i < width; i++) {
      // Imprime um caractere de espaço para "apagar" o caractere existente naquela posição.
      printf(" ");
    }
  }
}


/**
 * @brief Desenha uma moldura retangular na tela usando caracteres especiais de desenho de linha.
 *
 * A função é declarada como 'static', o que significa que sua visibilidade é
 * limitada a este arquivo de código fonte (chute.c). Não pode ser chamada de outros arquivos.
 *
 * @param x Coordenada X do canto superior esquerdo da moldura.
 * @param y Coordenada Y do canto superior esquerdo da moldura.
 * @param width Largura total da moldura (incluindo as bordas).
 * @param height Altura total da moldura (incluindo as bordas).
 */
static void desenhar_moldura(int x, int y, int width, int height) {
  // Desenha o canto superior esquerdo da moldura.
  screenGotoxy(x, y);
  printf("┌"); // Caractere de canto (ex: Unicode U+250C).
  // Desenha o canto superior direito.
  screenGotoxy(x + width - 1, y);
  printf("┐"); // Caractere de canto (ex: Unicode U+2510).
  // Desenha o canto inferior esquerdo.
  screenGotoxy(x, y + height - 1);
  printf("└"); // Caractere de canto (ex: Unicode U+2514).
  // Desenha o canto inferior direito.
  screenGotoxy(x + width - 1, y + height - 1);
  printf("┘"); // Caractere de canto (ex: Unicode U+2518).


  // Desenha as bordas horizontais (superior e inferior).
  // Itera pelas colunas entre os cantos.
  for (int i = x + 1; i < x + width - 1; i++) {
    screenGotoxy(i, y); // Posição na borda superior.
    printf("-");        // Caractere de linha horizontal (ou "─", Unicode U+2500).
    screenGotoxy(i, y + height - 1); // Posição na borda inferior.
    printf("-");                     // Caractere de linha horizontal.
  }


  // Desenha as bordas verticais (esquerda e direita).
  // Itera pelas linhas entre os cantos.
  for (int j = y + 1; j < y + height - 1; j++) {
    screenGotoxy(x, j); // Posição na borda esquerda.
    printf("|");        // Caractere de linha vertical (ou "│", Unicode U+2502).
    screenGotoxy(x + width - 1, j); // Posição na borda direita.
    printf("|");                    // Caractere de linha vertical.
  }
}


/**
 * @brief Centraliza um texto em uma determinada linha (y) dentro da largura de um modal.
 *
 * A função é declarada como 'static', limitando sua visibilidade a este arquivo.
 *
 * @param y Coordenada Y (linha) onde o texto será impresso.
 * @param texto A string de texto a ser centralizada e impressa.
 * @param modal_x Coordenada X inicial (coluna da esquerda) do modal, usada como referência
 * para o cálculo da centralização.
 */
static void centralizar_texto(int y, const char *texto, int modal_x) {
  // Calcula o comprimento da string de texto.
  int len = strlen(texto);
  // Calcula a posição X (coluna) para iniciar a impressão do texto.
  // MODAL_WIDTH é uma constante que define a largura total do modal.
  // A fórmula (MODAL_WIDTH - len) / 2 encontra o espaço vazio em cada lado do texto.
  int x = modal_x + (MODAL_WIDTH - len) / 2;
  // Move o cursor para a posição calculada.
  screenGotoxy(x, y);
  // Imprime o texto.
  printf("%s", texto);
}


/**
 * @brief Permite ao jogador selecionar um suspeito, uma arma e um local para o seu "chute".
 *
 * Esta função gerencia a interface de seleção em três etapas (categorias).
 * As opções para cada categoria são embaralhadas para variar a apresentação.
 * O jogador navega com as setas, seleciona com Enter e pode voltar com ESC.
 *
 * @param itens Ponteiro para uma estrutura `ItensUsados` que contém os arrays de índices
 * dos itens válidos (suspeitos, armas, locais) que podem ser escolhidos nesta rodada.
 * @return ItensChute Uma estrutura contendo os índices dos itens selecionados pelo jogador.
 * Retorna {-1, -1, -1} se o jogador sair (ESC na primeira categoria)
 * antes de completar a seleção.
 */
ItensChute obter_chute_jogador(const ItensUsados *itens) {
  // Inicializa a estrutura de chute com valores inválidos (-1).
  // Estes valores serão preenchidos à medida que o jogador faz as seleções.
  ItensChute chute = {-1, -1, -1};
  // Controla a categoria atual de seleção (0: Suspeito, 1: Arma, 2: Local).
  int categoria_atual = 0;
  // Controla o item atualmente selecionado (destacado) na lista da categoria atual (índice da lista exibida).
  int selecao = 0;
  // Armazena o código da tecla pressionada pelo jogador.
  int tecla;


  // Matriz para armazenar os índices *originais* das opções após serem embaralhadas para cada categoria.
  // 3 categorias, e USADOS_POR_CATEGORIA opções por categoria.
  // USADOS_POR_CATEGORIA é uma constante que define quantas opções são mostradas ao jogador.
  int embaralhados[3][USADOS_POR_CATEGORIA];
  // Flags para garantir que cada categoria seja embaralhada apenas uma vez por chamada desta função.
  // 0 = não embaralhado, 1 = já embaralhado.
  int ja_embaralhado[3] = {0, 0, 0};


  // Loop principal: continua enquanto o jogador não tiver selecionado as 3 categorias.
  while (categoria_atual < 3) {
    // Calcula a largura disponível na tela (MAXX e MINX são constantes dos limites da tela).
    int screen_width = MAXX - MINX;
    // Calcula a posição X (coluna da esquerda) para o modal, de forma que ele fique centralizado na tela.
    int modal_x = MINX + (screen_width - MODAL_WIDTH) / 2;
    // Define a posição Y (linha do topo) para o modal.
    int modal_y = 2; // Começa na linha 2 da tela.


    // Limpa a área onde o modal será desenhado.
    // MODAL_WIDTH e MODAL_HEIGHT são constantes das dimensões do modal.
    limpar_area_modal(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);
    // Desenha a moldura do modal.
    desenhar_moldura(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);


    // Ponteiros para armazenar o título e as opções da categoria atual.
    const char *titulo;         // Título da categoria (ex: "SELECIONE O SUSPEITO").
    const char **opcoes;        // Ponteiro para um array de strings (os nomes das opções).
    const int *indices;         // Ponteiro para o array de índices válidos da categoria atual (vindo de `itens`).


    // Define o título, as opções (array de nomes) e os índices (array de inteiros) com base na categoria atual.
    switch (categoria_atual) {
    case 0: // Seleção do Suspeito
      titulo = "SELECIONE O SUSPEITO";
      opcoes = NOMES_SUSPEITOS;   // NOMES_SUSPEITOS é um array de strings (char**) definido em outro lugar.
      indices = itens->suspeitos; // Acessa os índices de suspeitos da estrutura ItensUsados.
      break;
    case 1: // Seleção da Arma
      titulo = "SELECIONE A ARMA";
      opcoes = NOMES_ARMAS;       // NOMES_ARMAS é um array de strings.
      indices = itens->armas;     // Acessa os índices de armas.
      break;
    case 2: // Seleção do Local
      titulo = "SELECIONE O LOCAL";
      opcoes = NOMES_LOCAIS;      // NOMES_LOCAIS é um array de strings.
      indices = itens->locais;    // Acessa os índices de locais.
      break;
    }


    // Embaralha as opções da categoria atual se ainda não foram embaralhadas nesta chamada da função.
    // Usa o algoritmo de Fisher-Yates (modern version) para embaralhar os índices.
    if (!ja_embaralhado[categoria_atual]) {
      // Copia os índices originais (vindos de `itens->categoria`) para a matriz `embaralhados`
      // antes de realizar o embaralhamento nela.
      for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
        embaralhados[categoria_atual][i] = indices[i];
      }


      // Algoritmo de embaralhamento de Fisher-Yates.
      // Itera do último elemento até o segundo.
      for (int i = USADOS_POR_CATEGORIA - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Gera um índice aleatório 'j' entre 0 e 'i' (inclusive).
        // Troca os elementos nas posições 'i' e 'j' do array `embaralhados` da categoria atual.
        int temp = embaralhados[categoria_atual][i];
        embaralhados[categoria_atual][i] = embaralhados[categoria_atual][j];
        embaralhados[categoria_atual][j] = temp;
      }
      // Marca a categoria como já embaralhada para não embaralhar novamente se o jogador voltar a ela com ESC.
      ja_embaralhado[categoria_atual] = 1;
    }


    // Centraliza e exibe o título da categoria no modal.
    // modal_y + 1 para exibir o título na segunda linha do modal.
    centralizar_texto(modal_y + 1, titulo, modal_x);


    // Exibe as opções embaralhadas da categoria atual.
    for (int i = 0; i < USADOS_POR_CATEGORIA; i++) {
      // Move o cursor para a posição da opção (modal_x + 2 para um recuo, modal_y + 3 + i para as linhas).
      screenGotoxy(modal_x + 2, modal_y + 3 + i);
      // Se a opção atual (i) é a selecionada (`selecao`), inverte as cores (destaque).
      if (i == selecao)
        screenSetColor(BLACK, WHITE); // Texto preto, fundo branco (destaque).
      else
        screenSetColor(WHITE, BLACK); // Texto branco, fundo preto (normal).
      // Imprime o nome da opção.
      // `embaralhados[categoria_atual][i]` fornece o índice *original* do item (ex: índice do suspeito na lista global).
      // `opcoes[...]` usa esse índice original para buscar o nome correto no array de nomes.
      printf("%s", opcoes[embaralhados[categoria_atual][i]]);
    }


    // Restaura a cor padrão (branco sobre preto) para as instruções.
    screenSetColor(WHITE, BLACK);
    // Exibe as instruções de navegação no rodapé do modal.
    // MODAL_HEIGHT - 2 para a penúltima linha do modal.
    screenGotoxy(modal_x + 2, modal_y + MODAL_HEIGHT - 2);
    printf("Setas: Navegar   Enter: Selecionar");
    // MODAL_HEIGHT - 1 para a última linha do modal.
    screenGotoxy(modal_x + 2, modal_y + MODAL_HEIGHT - 1);
    printf("ESC: Voltar");


    // Atualiza a tela para mostrar todas as mudanças (desenhos, textos, cores).
    // A necessidade desta função depende da biblioteca de tela utilizada.
    screenUpdate();


    // Loop para capturar e processar a entrada do jogador (teclado) para esta categoria.
    while (1) {
      // Verifica se alguma tecla foi pressionada (função não bloqueante).
      // keyhit() deve ser uma função da biblioteca de tela que retorna true se há uma tecla no buffer.
      if (keyhit()) {
        tecla = readch(); // Lê o caractere pressionado (pode ser bloqueante ou não, dependendo de readch).


        // Verifica se a tecla ESC foi pressionada (código ASCII 27).
        if (tecla == 27) { // ESC
          // Verifica se é uma sequência de escape para setas (ex: ESC [ A para Seta Cima).
          // Terminais ANSI/VT100 enviam sequências de múltiplos caracteres para teclas especiais.
          // Esta verificação tenta detectar o início de tal sequência.
          if (keyhit() && readch() == 91) { // '[' após ESC geralmente indica uma sequência de controle.
            tecla = readch(); // Lê o caractere final da sequência (A, B, C, D para setas).
            if (tecla == 65 && selecao > 0) // 65 é 'A' (Seta para Cima)
              selecao--; // Move a seleção para cima, se não estiver no topo da lista.
            else if (tecla == 66 && selecao < USADOS_POR_CATEGORIA - 1) // 66 é 'B' (Seta para Baixo)
              selecao++; // Move a seleção para baixo, se não estiver na base da lista.
          } else {
            // Se foi apenas ESC (não uma sequência de seta):
            // Permite voltar para a categoria anterior.
            if (categoria_atual > 0) {
              categoria_atual--; // Volta para a categoria anterior.
              selecao = 0; // Reseta a seleção para o início da lista da categoria anterior.
              break; // Sai do loop de leitura de tecla para redesenhar a tela da categoria anterior.
            } else {
              // Se estiver na primeira categoria (0) e pressionar ESC, o jogador quer sair da seleção.
              return chute; // Retorna o chute incompleto (com -1 nos campos).
            }
          }
        // Verifica se a tecla Enter foi pressionada.
        // Diferentes sistemas podem enviar '\n' (LF, ASCII 10) ou '\r' (CR, ASCII 13) para Enter.
        } else if (tecla == '\n' || tecla == 10 || tecla == 13) { // Enter
          // Obtém o índice *original* do item escolhido (que estava na posição `selecao` da lista embaralhada).
          int escolhido = embaralhados[categoria_atual][selecao];
          // Armazena o índice do item escolhido na estrutura `chute` de acordo com a categoria atual.
          switch (categoria_atual) {
          case 0:
            chute.suspeitos = escolhido;
            break;
          case 1:
            chute.armas = escolhido;
            break;
          case 2:
            chute.locais = escolhido;
            break;
          }
          // Avança para a próxima categoria.
          categoria_atual++;
          // Reseta a seleção para o topo da lista (índice 0) na nova categoria.
          selecao = 0;
          break; // Sai do loop de leitura de tecla para processar a próxima categoria ou finalizar.
        }
        // Após processar uma tecla de seta, Enter ou ESC (que não saiu da função),
        // sai do loop de leitura para redesenhar o modal com a nova seleção destacada.
        break;
      } // Fim do if (keyhit())
    }   // Fim do while(1) de leitura de tecla
  }     // Fim do while (categoria_atual < 3)


  // Retorna o chute completo do jogador (com os 3 itens selecionados).
  return chute;
}




/**
 * @brief Mostra o resultado do chute do jogador em um modal.
 *
 * Se o jogador acertar tudo (3 acertos), salva o nome e o tempo no ranking
 * e oferece a opção de visualizá-lo.
 * Caso contrário, mostra quantos itens o jogador acertou.
 *
 * @param acertos Número de itens que o jogador acertou corretamente (0 a 3).
 * @param nome    Nome do jogador (usado para salvar no ranking se vencer).
 * @param tempo   Tempo que o jogador levou para resolver (usado para salvar no ranking).
 */
void mostrar_resultado_chute(int acertos, const char *nome, double tempo) {
  // Calcula a posição X (coluna da esquerda) para o modal de resultado, centralizando-o.
  int modal_x = MINX + (MAXX - MINX - MODAL_WIDTH) / 2;
  // Define a posição Y (linha do topo) para o modal de resultado.
  int modal_y = 2;


  // Limpa a área do modal e desenha sua moldura.
  limpar_area_modal(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);
  desenhar_moldura(modal_x, modal_y, MODAL_WIDTH, MODAL_HEIGHT);
  // Exibe o título "RESULTADO" centralizado na segunda linha do modal.
  centralizar_texto(modal_y + 1, "RESULTADO", modal_x);


  // Verifica se o jogador acertou todas as 3 categorias.
  if (acertos == 3) {
    // Salva o nome e o tempo do jogador no ranking.
    // salvar_ranking() é uma função definida em outro lugar (provavelmente ranking.c).
    salvar_ranking(nome, tempo);


    // Define a cor do texto para verde (sucesso). GREEN deve ser uma constante de cor.
    screenSetColor(GREEN, BLACK);
    // Posiciona o cursor para a mensagem de parabéns.
    screenGotoxy(modal_x + 5, modal_y + 3); // Recuo de 5 colunas, 3ª linha útil do modal.
    printf("Parabéns! Caso resolvido!");


    // Restaura a cor padrão (branco sobre preto).
    screenSetColor(WHITE, BLACK);
    // Posiciona o cursor para a instrução de ver o ranking.
    screenGotoxy(modal_x + 5, modal_y + MODAL_HEIGHT - 2); // Penúltima linha do modal.
    printf("Pressione Enter para ver o ranking...");


    // Aguarda o jogador pressionar Enter.
    // getchar() lê um caractere da entrada padrão. Pode ser problemático se houver
    // caracteres residuais no buffer de entrada (stdin) de leituras anteriores.
    // Usar um loop com keyhit() e readch() para esperar especificamente pelo Enter seria mais robusto.
    getchar();
    // Mostra a tela de ranking.
    // mostrar_ranking() é uma função definida em outro lugar (provavelmente ranking.c).
    mostrar_ranking();
  } else {
    // Se não acertou tudo, mostra quantos acertou.
    // Define a cor do texto para amarelo (aviso/informação). YELLOW deve ser uma constante de cor.
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(modal_x + 5, modal_y + 3);
    printf("Acertou %d/3. Continue!", acertos);
    // Restaura a cor padrão.
    screenSetColor(WHITE, BLACK);
    screenGotoxy(modal_x + 5, modal_y + MODAL_HEIGHT - 2);
    printf("Pressione qualquer tecla...");
  }


  // Atualiza a tela para mostrar o modal de resultado.
  screenUpdate();


  // Aguarda o jogador pressionar qualquer tecla para continuar.
  // Loop espera até que keyhit() retorne verdadeiro (tecla pressionada).
  while (!keyhit())
    ; // Loop vazio, apenas espera.
  readch(); // Lê e descarta a tecla pressionada, limpando o buffer para a próxima entrada.}
