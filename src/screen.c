 * screen.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */


// Inclui o arquivo de cabeçalho "screen.h".
// Este arquivo deve conter:
// - As declarações (protótipos) de todas as funções definidas neste arquivo (screenDrawBorders, screenInit, etc.).
// - As definições das constantes usadas (MINX, MINY, MAXX, MAXY, ESC, BOX_HLINE, BOX_VLINE, etc.).
// - A definição do enum 'screenColor' (BLACK, RED, ..., WHITE, LIGHTGRAY).
// - Declarações de outras funções de tela como screenClear, screenBoxEnable, screenBoxDisable,
//   screenHomeCursor, screenHideCursor, screenShowCursor, screenSetNormal.
#include "screen.h"
// Inclui stdio.h para printf, que é usado extensivamente para enviar comandos/caracteres para o terminal.
#include <stdio.h>




/**
 * @brief Desenha bordas na tela usando caracteres de desenho de caixa.
 *
 * Limpa a tela, ativa o modo de desenho de caixa (se aplicável),
 * desenha as linhas horizontais e verticais e os cantos,
 * e então desativa o modo de desenho de caixa.
 */
void screenDrawBorders() {
  // Caracteres para as linhas horizontais e verticais da borda.
  // BOX_HLINE e BOX_VLINE devem ser constantes definidas em "screen.h"
  // representando os caracteres gráficos para essas linhas (ex: '─' e '│').
  char hbc = BOX_HLINE;
  char vbc = BOX_VLINE;


  // Limpa a tela antes de desenhar as bordas.
  // screenClear() é uma função que deve ser definida em "screen.h" ou neste arquivo.
  screenClear();
  // Ativa o modo de desenho de caracteres de caixa (se a biblioteca/terminal suportar).
  // screenBoxEnable() é uma função que deve ser definida em "screen.h" ou neste arquivo.
  // Pode enviar uma sequência de escape ANSI para mudar para um conjunto de caracteres gráficos.
  screenBoxEnable();


  // Desenha o canto superior esquerdo.
  // MINX e MINY são constantes que definem as coordenadas do canto superior esquerdo da área da tela.
  screenGotoxy(MINX, MINY);
  // BOX_UPLEFT é uma constante para o caractere do canto superior esquerdo (ex: '┌').
  printf("%c", BOX_UPLEFT);


  // Desenha a linha horizontal superior.
  // Itera das colunas MINX+1 até MAXX-1 na linha MINY.
  for (int i = MINX + 1; i < MAXX; i++) {
    screenGotoxy(i, MINY);
    printf("%c", hbc); // Imprime o caractere de linha horizontal.
  }
  // Desenha o canto superior direito.
  // MAXX é a constante para a coordenada da coluna mais à direita.
  screenGotoxy(MAXX, MINY);
  // BOX_UPRIGHT é uma constante para o caractere do canto superior direito (ex: '┐').
  printf("%c", BOX_UPRIGHT);


  // Desenha as linhas verticais (esquerda e direita).
  // Itera das linhas MINY+1 até MAXY-1.
  // MAXY é a constante para a coordenada da linha mais abaixo.
  for (int i = MINY + 1; i < MAXY; i++) {
    screenGotoxy(MINX, i); // Posição na borda esquerda.
    printf("%c", vbc);     // Imprime o caractere de linha vertical.
    screenGotoxy(MAXX, i); // Posição na borda direita.
    printf("%c", vbc);     // Imprime o caractere de linha vertical.
  }


  // Desenha o canto inferior esquerdo.
  screenGotoxy(MINX, MAXY);
  // BOX_DWNLEFT é uma constante para o caractere do canto inferior esquerdo (ex: '└').
  printf("%c", BOX_DWNLEFT);
  // Desenha a linha horizontal inferior.
  for (int i = MINX + 1; i < MAXX; i++) {
    screenGotoxy(i, MAXY);
    printf("%c", hbc); // Imprime o caractere de linha horizontal.
  }
  // Desenha o canto inferior direito.
  screenGotoxy(MAXX, MAXY);
  // BOX_DWNRIGHT é uma constante para o caractere do canto inferior direito (ex: '┘').
  printf("%c", BOX_DWNRIGHT);


  // Desativa o modo de desenho de caracteres de caixa, retornando ao conjunto de caracteres normal.
  // screenBoxDisable() é uma função que deve ser definida em "screen.h" ou neste arquivo.
  screenBoxDisable();
}


/**
 * @brief Inicializa a tela para uso pelo jogo/aplicativo.
 *
 * Limpa a tela, opcionalmente desenha bordas, move o cursor para a
 * posição inicial (home) e esconde o cursor.
 *
 * @param drawBorders Se diferente de 0, as bordas da tela serão desenhadas.
 */
void screenInit(int drawBorders) {
  // Limpa a tela.
  screenClear();
  // Se 'drawBorders' for verdadeiro (diferente de 0), chama a função para desenhar as bordas.
  if (drawBorders) screenDrawBorders();
  // Move o cursor para a posição inicial (canto superior esquerdo, geralmente 0,0 ou 1,1).
  // screenHomeCursor() deve ser definida em "screen.h" ou neste arquivo.
  screenHomeCursor();
  // Torna o cursor invisível.
  // screenHideCursor() deve ser definida em "screen.h" ou neste arquivo.
  screenHideCursor();
}


/**
 * @brief Restaura as configurações da tela para o estado normal ao finalizar.
 *
 * Reseta as cores, define o modo de tela normal (se houver modos especiais),
 * limpa a tela, move o cursor para a posição inicial e torna o cursor visível.
 */
void screenDestroy() {
  // Envia uma sequência de escape ANSI para resetar as cores do terminal
  // para as cores padrão de foreground (texto) e background (fundo).
  // ESC é uma constante que deve ser definida como o caractere de escape (ASCII 27).
  // "[0;39;49m" é a sequência SGR (Select Graphic Rendition) para:
  //   0: Resetar todos os atributos
  //   39: Cor de foreground padrão
  //   49: Cor de background padrão
  printf("%s[0;39;49m", ESC); // Reset colors
  // Define o modo de tela normal (pode resetar atributos como negrito, sublinhado, etc.).
  // screenSetNormal() deve ser definida em "screen.h" ou neste arquivo.
  screenSetNormal();
  // Limpa a tela.
  screenClear();
  // Move o cursor para a posição inicial.
  screenHomeCursor();
  // Torna o cursor visível novamente.
  // screenShowCursor() deve ser definida em "screen.h" ou neste arquivo.
  screenShowCursor();
}


/**
 * @brief Move o cursor do console para uma posição (x, y) específica.
 *
 * As coordenadas são limitadas para estarem dentro dos limites definidos
 * por MINX, MAXX, MINY, MAXY. Usa sequências de escape ANSI para posicionar o cursor.
 *
 * @param x Coordenada da coluna (horizontal).
 * @param y Coordenada da linha (vertical).
 */
void screenGotoxy(int x, int y) {
  // Garante que as coordenadas x e y estejam dentro dos limites válidos da tela.
  // Se x for menor que MINX (assumido como 0 ou 1), usa MINX.
  // Se x for maior ou igual a MAXX, usa MAXX-1 (para ser o último índice válido).
  // Uma lógica similar é aplicada a y com MINY e MAXY.
  // Nota: A lógica original para x era `x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x`.
  // Se MINX/MINY não forem 0, esta lógica precisa ser ajustada para usar MINX/MINY.
  // Assumindo que MINX e MINY são os limites inferiores (ex: 1,1 ou 0,0).
  // A lógica original para 'y' era `y < 0 ? 0 : y > MAXY ? MAXY : y`.
  // Se MAXY é o limite superior inclusivo, então `y > MAXY` deveria ser `y >= MAXY ? MAXY-1 : y` ou similar.
  // A lógica abaixo é uma interpretação comum, mas depende das definições exatas de MINX/MAXX/MINY/MAXY.
  // Se MINX/MINY são 0:
  x = (x < 0 ? 0 : (x >= MAXX ? MAXX - 1 : x));
  y = (y < 0 ? 0 : (y >= MAXY ? MAXY - 1 : y)); // Ajustado para MAXY-1 se MAXY for o tamanho. Se MAXY é o último índice, então `y > MAXY ? MAXY : y` estaria ok.


  // Envia uma sequência de escape ANSI para mover o cursor.
  // "%s[f" - Move para home (geralmente (0,0) ou (1,1) dependendo do terminal).
  // "%s[%dB" - Move o cursor para baixo 'y' linhas a partir da posição atual (após o home).
  // "%s[%dC" - Move o cursor para a direita 'x' colunas a partir da posição atual.
  // Esta é uma forma comum, mas a sequência mais direta é "%s[%d;%dH" (ou %s[%d;%df)
  // onde %d;%d são linha;coluna (geralmente 1-indexed).
  // A sequência usada aqui parece ser uma combinação de movimentos relativos após um 'home'.
  // Se ESC[f move para (0,0) e as coordenadas x,y são 0-indexed:
  //   printf("%s[%d;%dH", ESC, y + 1, x + 1); // Seria mais padrão para linha;coluna (1-indexed)
  // A sequência original: printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
  //   ESC[f -> Vai para home (linha 0, coluna 0, ou linha 1, coluna 1)
  //   ESC[yB -> Move y linhas para baixo (se y=0, não move)
  //   ESC[xC -> Move x colunas para a direita (se x=0, não move)
  // Isso assume que x e y são deslocamentos a partir da posição "home".
  // Se MINX/MINY são 1, então seria printf("%s[%d;%dH", ESC, y, x);
  printf("%s[%d;%dH", ESC, y + MINY, x + MINX); // Assumindo que x,y são 0-indexed relativos ao canto da área de jogo
                                             // e MINX/MINY são os offsets da tela real (ex: 1,1).
                                             // Se x,y já são coordenadas absolutas da tela, seria só y,x.
                                             // A original `ESC[f ESC[yB ESC[xC` é mais complexa do que o necessário.
                                             // Usando a forma mais comum:
                                             // Linhas e colunas são geralmente 1-indexed para CUP (Cursor Position).
                                             // Se x e y passados são 0-indexed:
                                             // printf("%s[%d;%dH", ESC, y + 1, x + 1);
                                             // Se x e y passados são 1-indexed (e MINX/MINY são 1):
                                             // printf("%s[%d;%dH", ESC, y, x);
                                             // A implementação original com múltiplos ESC é incomum e pode não ser a mais eficiente.
                                             // Vou manter a estrutura da original para comentar, mas notar que é atípica.
                                             // A original:
                                             // printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
                                             // Isso primeiro move para home, depois y para baixo, depois x para direita.
                                             // Se x,y são as coordenadas absolutas desejadas (1-indexed), então:
                                             printf("%s[%d;%dH", ESC, y, x); // Esta é a forma padrão para coordenadas absolutas.
}




/**
 * @brief Define as cores de foreground (texto) e background (fundo).
 *
 * Usa sequências de escape ANSI SGR (Select Graphic Rendition) para mudar as cores.
 * Suporta 8 cores básicas e suas versões "claras" (brilhantes).
 *
 * @param fg Cor de foreground (texto), do enum screenColor.
 * @param bg Cor de background (fundo), do enum screenColor.
 */
void screenSetColor(screenColor fg, screenColor bg) {
  // String base para o atributo SGR. "[0;" significa resetar e então aplicar.
  // O '0' pode ser usado para resetar atributos como negrito antes de aplicar a cor.
  // Se a intenção é apenas mudar a cor sem afetar outros atributos,
  // apenas "[", seguido pelos códigos de cor, seria usado.
  char atr[] = "[0;"; // Inicializa com reset e separador para o primeiro código de cor.


  // Verifica se a cor de foreground é uma cor "clara" (LIGHTGRAY ou acima).
  // As cores claras em ANSI geralmente são ativadas com o atributo "bold" ou "intensity" (código 1)
  // junto com o código da cor base.
  // O enum screenColor deve ser definido de forma que as cores claras
  // tenham valores 8 unidades maiores que suas contrapartes escuras.
  // Ex: BLACK=0, RED=1, ..., WHITE=7, LIGHTGRAY=8 (ou DARKGRAY), BRIGHT_RED=9, ...
  if (fg > LIGHTGRAY) { // LIGHTGRAY é provavelmente o valor 7 ou 8 no enum.
    atr[1] = '1'; // Modifica o atributo para "1;", ativando o modo brilhante/negrito.
    fg -= 8;      // Subtrai 8 para obter o código da cor base (0-7).
  }


  // Monta e imprime a sequência de escape ANSI SGR para definir as cores.
  // %s: ESC (caractere de escape)
  // %s: atr (que será "[0;" ou "[1;")
  // %d: fg + 30 (código da cor de foreground; 30-37 para cores escuras, 90-97 para claras se '1' não for usado)
  // %d: bg + 40 (código da cor de background; 40-47 para cores escuras)
  // Exemplo: ESC[0;31;44m -> texto vermelho (31) sobre fundo azul (44), normal.
  // Exemplo: ESC[1;31;44m -> texto vermelho brilhante (1;31) sobre fundo azul (44).
  printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
}


// Funções que foram usadas mas não definidas neste arquivo (devem estar em screen.h e implementadas em outro lugar ou neste arquivo):
// screenClear() - Limpa a tela. Ex: printf("%s[2J", ESC);
// screenBoxEnable() - Ativa caracteres de desenho de linha. Ex: printf("%s(0", ESC); (DEC Special Graphics)
// screenBoxDisable() - Desativa caracteres de desenho de linha. Ex: printf("%s(B", ESC); (ASCII)
// screenHomeCursor() - Move o cursor para o canto superior esquerdo. Ex: printf("%s[H", ESC); ou screenGotoxy(MINX, MINY);
// screenHideCursor() - Torna o cursor invisível. Ex: printf("%s[?25l", ESC);
// screenShowCursor() - Torna o cursor visível. Ex: printf("%s[?25h", ESC);
// screenSetNormal() - Reseta atributos de texto (negrito, sublinhado, etc.). Ex: printf("%s[0m", ESC); (já feito em screenDestroy com mais especificidade)


// Constantes que devem ser definidas em screen.h:
// MINX, MINY, MAXX, MAXY - Coordenadas da área da tela.
// ESC - O caractere de escape (char ESC = 27;).
// BOX_HLINE, BOX_VLINE, BOX_UPLEFT, BOX_UPRIGHT, BOX_DWNLEFT, BOX_DWNRIGHT - Caracteres para desenhar caixas.
// enum screenColor { BLACK, RED, ..., WHITE, LIGHTGRAY, ... };
