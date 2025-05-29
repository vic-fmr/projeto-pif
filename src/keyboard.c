/**
 * keyboard.h // Indica que as declarações estão em keyboard.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002" // Informações de autoria e base
 */


// Inclui a biblioteca termios.h, que define estruturas e funções
// para controlar atributos de terminais assíncronos (como o console).
// É essencial para modificar o comportamento padrão de entrada do terminal.
#include <termios.h>
// Inclui a biblioteca unistd.h, que define várias constantes e tipos simbólicos
// e declara funções diversas de sistema POSIX, como read().
#include <unistd.h>


// Inclui o arquivo de cabeçalho "keyboard.h".
// Este arquivo deve conter as declarações (protótipos) das funções
// keyboardInit, keyboardDestroy, keyhit, e readch.
#include "keyboard.h"


// Estruturas para armazenar as configurações do terminal.
// 'initialSettings' guardará as configurações originais do terminal para restaurá-las depois.
// 'newSettings' será usada para aplicar as configurações modificadas (modo não canônico).
static struct termios initialSettings, newSettings;
// Variável para armazenar um caractere "espiado" (peeked).
// Usada pela função keyhit() para verificar se uma tecla foi pressionada sem consumi-la,
// e por readch() para retornar esse caractere se ele existir.
// -1 indica que não há caractere "espiado".
static int peekCharacter = -1;


/**
 * @brief Inicializa o modo de teclado não canônico.
 *
 * Salva as configurações atuais do terminal e as modifica para que a entrada
 * seja processada caractere a caractere, sem eco e sem esperar pela tecla Enter.
 */
void keyboardInit() {
  // tcgetattr(0, &initialSettings);
  // Obtém os atributos atuais do terminal associado ao descritor de arquivo 0 (stdin - entrada padrão)
  // e os armazena em 'initialSettings'.
  tcgetattr(0, &initialSettings);
  // Copia as configurações iniciais para 'newSettings' para começar a modificá-las.
  newSettings = initialSettings;


  // Modifica as flags de modo local (c_lflag) em 'newSettings':
  // newSettings.c_lflag &= ~ICANON;
  // Desativa o modo canônico (ICANON). No modo canônico, a entrada é processada em linhas
  // (terminadas por Enter, NL, EOL, etc.) e permite edição de linha. Desativá-lo
  // permite ler caracteres assim que são digitados.
  newSettings.c_lflag &= ~ICANON;


  // newSettings.c_lflag &= ~ECHO;
  // Desativa o eco (ECHO). As teclas digitadas não serão exibidas automaticamente no terminal.
  newSettings.c_lflag &= ~ECHO;


  // newSettings.c_lflag &= ~ISIG;
  // Desativa a verificação de sinais (ISIG). Sinais como INTR (Ctrl+C), QUIT (Ctrl+\),
  // e SUSP (Ctrl+Z) não serão gerados.
  newSettings.c_lflag &= ~ISIG;


  // Modifica os caracteres de controle (c_cc):
  // newSettings.c_cc[VMIN] = 1;
  // Define VMIN (número mínimo de bytes a serem lidos) para 1.
  // Isso significa que read() bloqueará até que pelo menos 1 caractere esteja disponível.
  newSettings.c_cc[VMIN] = 1;


  // newSettings.c_cc[VTIME] = 0;
  // Define VTIME (tempo limite de leitura em décimos de segundo) para 0.
  // Com VMIN > 0 e VTIME = 0, read() bloqueará indefinidamente até VMIN bytes serem recebidos.
  newSettings.c_cc[VTIME] = 0;


  // tcsetattr(0, TCSANOW, &newSettings);
  // Aplica as novas configurações ('newSettings') ao terminal (stdin).
  // TCSANOW significa que a mudança ocorre imediatamente.
  tcsetattr(0, TCSANOW, &newSettings);
}


/**
 * @brief Restaura as configurações originais do terminal.
 *
 * Deve ser chamada ao final do programa ou quando o modo não canônico
 * não for mais necessário, para que o terminal volte ao seu comportamento normal.
 */
void keyboardDestroy() {
  // tcsetattr(0, TCSANOW, &initialSettings);
  // Restaura os atributos do terminal para os que foram salvos em 'initialSettings'
  // durante a chamada de keyboardInit().
  tcsetattr(0, TCSANOW, &initialSettings);
}


/**
 * @brief Verifica se uma tecla foi pressionada sem consumi-la (non-blocking).
 *
 * @return int Retorna 1 se uma tecla foi pressionada e está disponível para leitura,
 * 0 caso contrário.
 */
int keyhit() {
  unsigned char ch;
  int nread;


  // Se já houver um caractere "espiado" em peekCharacter, significa que uma tecla
  // foi detectada anteriormente e ainda não foi lida por readch().
  if (peekCharacter != -1) return 1;


  // Modifica temporariamente as configurações do terminal para leitura não bloqueante.
  // newSettings.c_cc[VMIN] = 0;
  // Define VMIN para 0. Com VMIN = 0 e VTIME = 0 (definido abaixo implicitamente ou
  // se VTIME já for 0), read() retornará imediatamente. Se houver dados, retorna
  // o número de bytes lidos. Se não houver dados, retorna 0.
  newSettings.c_cc[VMIN] = 0;
  // Aplica a configuração temporária para leitura não bloqueante.
  tcsetattr(0, TCSANOW, &newSettings);
  // Tenta ler 1 byte da entrada padrão (stdin).
  // Esta chamada agora será não bloqueante devido à configuração VMIN = 0.
  nread = read(0, &ch, 1);
  // Restaura VMIN para 1 para que as chamadas subsequentes a readch() (ou read() direto)
  // voltem a ser bloqueantes até que um caractere seja digitado.
  newSettings.c_cc[VMIN] = 1;
  // Reaplica a configuração com VMIN = 1.
  tcsetattr(0, TCSANOW, &newSettings);


  // Se read() conseguiu ler 1 byte (nread == 1), significa que uma tecla foi pressionada.
  if (nread == 1) {
    peekCharacter = ch; // Armazena o caractere lido em peekCharacter para uso posterior por readch().
    return 1;           // Retorna 1 indicando que uma tecla foi detectada.
  }


  // Se read() não leu nenhum byte (nread == 0), nenhuma tecla foi pressionada.
  return 0; // Retorna 0.
}


/**
 * @brief Lê um caractere da entrada do teclado (bloqueante).
 *
 * Se um caractere foi previamente detectado por keyhit() e armazenado em
 * peekCharacter, ele é retornado. Caso contrário, espera (bloqueia)
 * até que uma tecla seja pressionada e então a lê e retorna.
 *
 * @return int O caractere lido (como um int) ou o caractere "espiado".
 */
int readch() {
  char ch;


  // Verifica se há um caractere "espiado" de uma chamada anterior a keyhit().
  if (peekCharacter != -1) {
    ch = peekCharacter;    // Pega o caractere "espiado".
    peekCharacter = -1;    // Reseta peekCharacter, indicando que o caractere foi consumido.
    return ch;             // Retorna o caractere "espiado".
  }
  // Se não houver caractere "espiado", lê um caractere da entrada padrão (stdin).
  // Esta chamada a read() será bloqueante porque keyboardInit() configurou
  // VMIN = 1 e VTIME = 0 (e keyhit() restaurou VMIN = 1).
  // O programa esperará aqui até que o usuário pressione uma tecla.
  read(0, &ch, 1);
  return ch; // Retorna o caractere lido.
}
