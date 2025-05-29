// Inclusão de todos os arquivos de cabeçalho necessários para as diferentes partes do jogo.
#include "player.h"       // Lógica e dados do jogador.
#include "jogo.h"         // Lógica geral do jogo, como geração de rodada e validação.
#include "mapa.h"         // Funções e dados relacionados ao mapa do jogo.
#include "salas.h"        // Lógica para verificar salas e interações.
#include "dialogo.h"      // Funções para mostrar diálogos/pistas na tela.
#include "pistas.h"       // Geração e manipulação de pistas.
#include "screen.h"       // Funções de baixo nível para manipulação da tela/console.
#include "keyboard.h"     // Funções para captura de entrada do teclado de forma não canônica.
#include "timer.h"        // Funções relacionadas a temporizadores ou delays.
#include "ui.h"           // Funções para elementos de interface do usuário, como tela inicial e instruções.
#include "chute.h"        // Lógica para o jogador fazer um "chute" (palpite).
#include "temporizador.h" // Funções para medir o tempo de jogo (provavelmente diferente de "timer.h").
#include "ranking.h"      // Funções para salvar e mostrar o ranking.


// Inclusões padrão que podem ser necessárias (embora não explicitamente usadas aqui,
// são comuns em arquivos main e podem ser usadas pelas funções dos headers incluídos)
#include <stdio.h>  // Para entrada/saída padrão (ex: printf, se não encapsulado por screen.h)
#include <stdlib.h> // Para funções gerais (ex: exit, alocação de memória)
#include <time.h>   // Para funções de tempo (time, difftime)


/**
 * @brief Função principal do jogo.
 *
 * Inicializa os componentes do jogo, gerencia o loop principal de eventos
 * (entrada do jogador, movimento, chute, exibição de pistas) e finaliza
 * os componentes ao sair.
 */
int main() {
  int ch = 0;         // Variável para armazenar a tecla pressionada pelo jogador.
  char nome[50];      // Array de caracteres para armazenar o nome do jogador.
  time_t inicio = time(NULL); // Registra o momento de início do jogo para calcular a duração.


  // Exibe a tela inicial e as instruções do jogo, obtendo o nome do jogador.
  tela_inicial();
  mostrar_instrucoes(nome);
  // 'inicio();' // Linha comentada, talvez uma função de inicialização anterior.


  // Inicializa os componentes de baixo nível: tela, teclado e timer (para delays/ticks).
  screenInit(1);    // Inicializa a tela (o argumento '1' pode ser um modo ou flag).
  keyboardInit();   // Configura o teclado para entrada não canônica.
  timerInit(50);    // Inicializa um timer (o argumento '50' pode ser milissegundos para um tick).


  // Inicializa e desenha os elementos do jogo no mapa.
  initMap();        // Prepara a estrutura de dados do mapa.
  drawMap();        // Desenha o mapa na tela.
  drawPlayer();     // Desenha o jogador na sua posição inicial no mapa.
  // iniciar_temporizador(&inicioTempo); // Linha comentada, talvez para um temporizador de contagem regressiva.
  screenUpdate();   // Atualiza a tela para exibir as mudanças iniciais.


  ItensUsados itens; // Estrutura para armazenar os itens corretos (gabarito) da rodada.
  Pista pistas[12];  // Array para armazenar as pistas do jogo (12 pistas no total).
  gerar_rodada(&itens); // Sorteia os itens corretos (suspeito, arma, local) para a rodada.
  gerar_pistas(pistas, itens); // Gera as pistas com base nos itens sorteados.


  // Loop principal do jogo. Continua até que a tecla ESC (código 27) seja pressionada.
  while (ch != 27) { // 27 é o código ASCII para a tecla ESC.
    // Verifica se alguma tecla foi pressionada.
    if (keyhit()) {
      ch = readch(); // Lê a tecla pressionada.


      // Se a tecla 'c' for pressionada, o jogador quer fazer um "chute".
      if (ch == 'c') {
        ItensChute chute = obter_chute_jogador(&itens); // Abre a interface para o jogador fazer o palpite.


        // Verifica se o jogador completou o chute (não cancelou pressionando ESC na primeira categoria).
        // obter_chute_jogador retorna -1 nos campos de 'chute' se cancelado.
        if (chute.suspeitos != -1) {
          time_t fim = time(NULL); // Registra o momento em que o chute foi feito.
          double duracao = difftime(fim, inicio); // Calcula a duração total do jogo até o chute.
          int acertos = validar_resultado(&chute, &itens); // Compara o chute com o gabarito.


          // Mostra o resultado do chute ao jogador.
          mostrar_resultado_chute(acertos, nome, duracao);


          // Se o jogador acertou todos os 3 itens.
          if (acertos == 3) {
            // double tempo = parar_temporizador(inicio); // Linha comentada, talvez para um temporizador específico.
            // salvar_ranking(nome, tempo); // Linha comentada, salvar_ranking já é chamado em mostrar_resultado_chute.


            // Condição de vitória!
            break; // Sai do loop principal do jogo.
          }
        }


        // Após o modal de chute ser fechado (seja por completar o chute ou cancelar),
        // redesenha a tela do jogo para remover o modal e restaurar a visão do mapa.
        screenClear();    // Limpa toda a tela.
        drawMap();        // Redesenha o mapa.
        drawPlayer();     // Redesenha o jogador.
        screenUpdate();   // Atualiza a tela.
      }


      // Lógica de movimento do jogador.
      int newX = playerX; // Posição X atual do jogador (playerX é uma variável global ou externa).
      int newY = playerY; // Posição Y atual do jogador (playerY é uma variável global ou externa).


      // Atualiza as coordenadas newX/newY com base na tecla de movimento pressionada.
      if (ch == 'w' || ch == 'W') newY--; // 'w' ou 'W' para mover para cima.
      if (ch == 's' || ch == 'S') newY++; // 's' ou 'S' para mover para baixo.
      if (ch == 'a' || ch == 'A') newX--; // 'a' ou 'A' para mover para a esquerda.
      if (ch == 'd' || ch == 'D') newX++; // 'd' ou 'D' para mover para a direita.


      // Verifica se a nova posição (newX, newY) é válida (não é uma parede).
      // map[newY][newX] acessa o caractere do mapa na nova posição.
      // Assume que '|' e '-' são caracteres de parede.
      if (map[newY][newX] != '|' && map[newY][newX] != '-') {
        clearPlayer();    // Apaga o jogador da posição antiga na tela.
        playerX = newX;   // Atualiza a posição global do jogador.
        playerY = newY;   // Atualiza a posição global do jogador.
        drawPlayer();     // Desenha o jogador na nova posição.


        // Verifica se o jogador entrou em alguma sala e mostra as pistas correspondentes.
        // A função verificarSala provavelmente retorna true se o jogador está na sala
        // e exibe as pistas usando showDialog internamente.
        // Cada chamada a verificarSala passa:
        //   - As dimensões/coordenadas da sala (ex: tamanhoAuditorio).
        //   - A primeira pista da sala.
        //   - A segunda pista da sala (pode ser uma string vazia "" se não houver segunda pista).
        // Se nenhuma das verificações de sala for verdadeira, significa que o jogador
        // não está em uma sala que exibe pistas, então um diálogo vazio é mostrado.
        if (!(verificarSala(tamanhoAuditorio, pistas[0].texto, pistas[8].texto) ||
              verificarSala(tamanhoBiblioteca, pistas[1].texto, "") ||
              verificarSala(tamanhoSala401, pistas[2].texto, pistas[9].texto) ||
              verificarSala(tamanhoCopa, pistas[3].texto, "") ||
              verificarSala(tamanhoGaragino, pistas[4].texto, "") ||
              verificarSala(tamanhoSalaProf, pistas[5].texto, pistas[10].texto) ||
              verificarSala(tamanhoSalaTI, pistas[6].texto, "") ||
              verificarSala(tamanhoPraca, pistas[7].texto, pistas[11].texto))) {
          // Se não estiver em nenhuma sala que mostre pistas, mostra um diálogo vazio
          // para limpar a área de diálogo de pistas anteriores.
          showDialog(" ", " ");
        }
      } else {
        // Se a nova posição for uma parede, o jogador não se move.
        // Apenas redesenha o jogador na posição atual (caso algo tenha sido sobreposto).
        // Embora, se clearPlayer/drawPlayer só afetam a posição do jogador,
        // e o mapa é estático, esta chamada pode não ser estritamente necessária aqui.
        drawPlayer();
      }
      screenUpdate(); // Atualiza a tela após o movimento ou tentativa de movimento.
    } // Fim do if (keyhit())
    // Adicionar um pequeno delay aqui pode ser útil para controlar a velocidade do jogo
    // e o consumo de CPU, se o loop estiver muito rápido. Ex: timerDelay(10);
  } // Fim do while (ch != 27)


  // Ao sair do loop principal (jogador pressionou ESC ou venceu):
  // Libera/destrói os componentes inicializados para restaurar o estado do terminal.
  keyboardDestroy();  // Restaura as configurações originais do teclado/terminal.
  screenDestroy();    // Restaura as configurações originais da tela (se houver).
  timerDestroy();     // Libera recursos do timer (se houver).


  return 0; // Indica que o programa terminou com sucesso.
}
