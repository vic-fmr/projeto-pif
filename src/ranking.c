// Inclui o arquivo de cabeçalho "ranking.h".
// Este arquivo deve conter as declarações (protótipos) das funções
// validar_nome, salvar_ranking, e mostrar_ranking, se forem usadas
// por outros módulos do jogo. Também pode definir a estrutura EntradaRanking
// se ela for compartilhada.
#include "ranking.h"


// Inclui o arquivo de cabeçalho "screen.h".
// Necessário para funções de manipulação da tela, como screenClear(),
// e possivelmente outras como screenGotoxy() ou screenSetColor() se usadas
// para formatar a exibição do ranking (embora aqui use printf principalmente).
#include "screen.h"


// Inclui a biblioteca padrão para classificação de caracteres (ex: isprint).
#include <ctype.h>
// Inclui a biblioteca padrão de entrada/saída (para FILE, fopen, fclose, fprintf, fgets, sscanf, printf, getchar).
#include <stdio.h>
// Inclui a biblioteca padrão para funções de utilidade geral (para qsort, exit, etc.).
#include <stdlib.h>
// Inclui a biblioteca padrão para manipulação de strings (para strlen, strncpy).
#include <string.h>


// Define o nome do arquivo onde o ranking será armazenado.
#define ARQUIVO_RANKING "ranking.csv"
// Define o número máximo de entradas que podem ser lidas/processadas do ranking.
#define MAX_ENTRADAS 100


// Define uma estrutura para armazenar uma entrada individual do ranking.
// Esta definição pode estar duplicada se também estiver em "ranking.h".
// Se for usada apenas neste arquivo .c, mantê-la aqui é aceitável.
typedef struct {
    char nome[50]; // Nome do jogador (até 49 caracteres + terminador nulo).
    double tempo;  // Tempo que o jogador levou, armazenado como um double.
} EntradaRanking;


/**
 * @brief Valida o nome do jogador.
 *
 * Verifica se o nome contém caracteres inválidos, como vírgula (que é usada
 * como delimitador no arquivo CSV) ou caracteres não imprimíveis.
 *
 * @param nome A string contendo o nome do jogador a ser validado.
 * @return int Retorna 1 se o nome for válido, 0 caso contrário.
 */
int validar_nome(const char *nome) {
    // Itera sobre cada caractere da string 'nome'.
    for (int i = 0; nome[i]; i++) { // O loop continua enquanto nome[i] não for o terminador nulo '\0'.
        // Se o caractere for uma vírgula ou não for um caractere imprimível (isprint retorna 0).
        if (nome[i] == ',' || !isprint(nome[i])) {
            return 0; // Nome inválido.
        }
    }
    return 1; // Nome válido.
}


/**
 * @brief Salva uma nova entrada (nome do jogador e tempo) no arquivo de ranking.
 *
 * Abre o arquivo de ranking no modo "append" (anexar) e escreve a nova entrada
 * no formato CSV (nome,tempo).
 *
 * @param nome O nome do jogador.
 * @param tempo O tempo que o jogador levou.
 */
void salvar_ranking(const char *nome, double tempo) {
    // Abre o arquivo de ranking em modo "a" (append - anexar ao final do arquivo).
    // Se o arquivo não existir, ele será criado.
    FILE *f = fopen(ARQUIVO_RANKING, "a");
    // Verifica se o arquivo foi aberto com sucesso.
    if (!f) {
        // Se não conseguiu abrir o arquivo (ex: problema de permissão),
        // simplesmente retorna sem fazer nada (ou poderia logar um erro).
        return;
    }


    // Escreve o nome e o tempo no arquivo, formatados como uma linha CSV.
    // "%s,%.2f\n" -> string, vírgula, float com 2 casas decimais, nova linha.
    fprintf(f, "%s,%.2f\n", nome, tempo);
    // Fecha o arquivo.
    fclose(f);
}


/**
 * @brief Função de comparação para qsort, usada para ordenar as entradas do ranking por tempo.
 *
 * Compara os tempos de duas entradas do ranking.
 *
 * @param a Ponteiro void para a primeira EntradaRanking.
 * @param b Ponteiro void para a segunda EntradaRanking.
 * @return int Retorna:
 * -1 se o tempo de 'a' for menor que o tempo de 'b'.
 * 1 se o tempo de 'a' for maior que o tempo de 'b'.
 * 0 se os tempos forem iguais.
 */
int comparar_tempos(const void *a, const void *b) {
    // Converte os ponteiros void de volta para ponteiros do tipo EntradaRanking.
    const EntradaRanking *ea = (const EntradaRanking *)a;
    const EntradaRanking *eb = (const EntradaRanking *)b;


    // Compara os tempos para ordenação crescente.
    if (ea->tempo < eb->tempo) return -1; // 'a' vem antes de 'b'.
    if (ea->tempo > eb->tempo) return 1;  // 'a' vem depois de 'b'.
    return 0; // Tempos iguais.
}


/**
 * @brief Lê as entradas do arquivo de ranking, ordena-as por tempo e as exibe na tela.
 *
 * Limpa a tela, lê o arquivo CSV, armazena as entradas em um array,
 * ordena o array usando qsort com a função comparar_tempos, e então
 * imprime o ranking formatado.
 */
void mostrar_ranking() {
    // Limpa a tela antes de exibir o ranking.
    // screenClear() é uma função da biblioteca "screen.h".
    screenClear();


    // Abre o arquivo de ranking em modo "r" (read - leitura).
    FILE *f = fopen(ARQUIVO_RANKING, "r");
    // Verifica se o arquivo foi aberto com sucesso.
    if (!f) {
        // Se o arquivo não puder ser aberto (ex: não existe),
        // imprime uma mensagem e aguarda o usuário pressionar Enter.
        printf("Ranking vazio ou arquivo não encontrado.\n");
        getchar(); // Aguarda uma entrada do usuário para que ele possa ler a mensagem.
        return;    // Sai da função.
    }


    // Array para armazenar as entradas lidas do arquivo.
    EntradaRanking entradas[MAX_ENTRADAS];
    int count = 0;     // Contador para o número de entradas lidas.
    char linha[100];   // Buffer para armazenar cada linha lida do arquivo.


    // Lê o arquivo linha por linha.
    // fgets lê até (sizeof(linha) - 1) caracteres, ou até uma nova linha, ou até o fim do arquivo.
    // O loop continua enquanto fgets conseguir ler uma linha E o contador 'count' for menor que MAX_ENTRADAS.
    while (fgets(linha, sizeof(linha), f) && count < MAX_ENTRADAS) {
        char nome_temp[50]; // Buffer temporário para o nome lido da linha.
        double tempo_temp;  // Variável temporária para o tempo lido da linha.


        // Tenta parsear a linha lida para extrair o nome e o tempo.
        // "%49[^,],%lf" é o formato para sscanf:
        //   %49[^,] -> Lê até 49 caracteres que não sejam vírgula (para evitar overflow em nome_temp).
        //   ,       -> Corresponde ao caractere vírgula (delimitador).
        //   %lf     -> Lê um double (long float).
        // sscanf retorna o número de itens atribuídos com sucesso. Espera-se 2 (nome e tempo).
        if (sscanf(linha, "%49[^,],%lf", nome_temp, &tempo_temp) == 2) {
            // Se o parseamento foi bem-sucedido, copia os dados para o array 'entradas'.
            // strncpy é usado para copiar o nome, garantindo que não haja estouro de buffer
            // no campo 'nome' da estrutura EntradaRanking.
            strncpy(entradas[count].nome, nome_temp, sizeof(entradas[count].nome) - 1);
            entradas[count].nome[sizeof(entradas[count].nome) - 1] = '\0'; // Garante terminação nula.
            entradas[count].tempo = tempo_temp;
            count++; // Incrementa o contador de entradas válidas.
        }
    }


    // Fecha o arquivo após terminar de lê-lo.
    fclose(f);


    // Ordena o array 'entradas' usando a função qsort.
    // - entradas: ponteiro para o início do array a ser ordenado.
    // - count: número de elementos no array.
    // - sizeof(EntradaRanking): tamanho de cada elemento no array.
    // - comparar_tempos: ponteiro para a função de comparação.
    qsort(entradas, count, sizeof(EntradaRanking), comparar_tempos);


    // Imprime o cabeçalho do ranking na tela.
    printf("\n======== RANKING ========\n");
    // Formata a saída em colunas: Posição (#), Nome, Tempo.
    // %-5s -> string alinhada à esquerda, 5 caracteres de largura.
    // %-20s -> string alinhada à esquerda, 20 caracteres de largura.
    // %-10s -> string alinhada à esquerda, 10 caracteres de largura.
    printf("%-5s %-20s %-10s\n", "#", "Nome", "Tempo(s)");


    // Itera sobre as entradas ordenadas e as imprime.
    for (int i = 0; i < count; i++) {
        // %-5d -> inteiro alinhado à esquerda, 5 caracteres de largura.
        // %.2fs -> float com 2 casas decimais, seguido pela letra 's'.
        printf("%-5d %-20s %.2fs\n", i + 1, entradas[i].nome, entradas[i].tempo);
    }


    // Imprime uma mensagem para o usuário voltar.
    printf("\nPressione ENTER para voltar...\n");
    // Aguarda o usuário pressionar Enter antes de sair da tela de ranking.
    // getchar() lê um único caractere (neste caso, o Enter).
    // Pode ser necessário um getchar() adicional se houver um '\n' pendente no buffer de entrada
    // de alguma leitura anterior no jogo.
    getchar();
    // Nota: Se screenClear() não foi chamado por quem chamou mostrar_ranking(),
    // o ranking permanecerá na tela até que outra parte do jogo a limpe.
}
