// Inclui a biblioteca padrão de entrada/saída (para snprintf).
#include <stdio.h>
// Inclui a biblioteca padrão para manipulação de strings (embora não usada diretamente aqui,
// é comum em conjunto com manipulação de texto).
#include <string.h>
// Inclui a biblioteca padrão para funções de utilidade geral (para rand, srand).
#include <stdlib.h>
// Inclui a biblioteca padrão para manipulação de tempo (para time, usado em srand).
#include <time.h>


// Inclui o arquivo de cabeçalho "pistas.h".
// Este arquivo deve conter a definição da estrutura 'Pista' e do enum 'TipoPista'.
// Exemplo de definições esperadas em pistas.h:
/*
typedef enum {
    TIPO_NEGACAO,
    TIPO_OU,
    TIPO_SE_ENTAO
    // ... outros tipos de pista
} TipoPista;


typedef struct {
    TipoPista tipo;
    int id;
    char texto[256]; // Tamanho arbitrário para o texto da pista
} Pista;


// Também deve declarar ItensUsados, que é usado em gerar_pistas.
typedef struct {
    int suspeitos[USADOS_POR_CATEGORIA]; // USADOS_POR_CATEGORIA é uma constante
    int armas[USADOS_POR_CATEGORIA];
    int locais[USADOS_POR_CATEGORIA];
} ItensUsados;
*/
#include "pistas.h"


// Inclui o arquivo de cabeçalho "dados.h".
// Este arquivo deve conter os arrays de strings com os nomes dos itens do jogo, como:
// extern const char *NOMES_SUSPEITOS[];
// extern const char *NOMES_ARMAS[];
// extern const char *NOMES_LOCAIS[];
// E também as constantes relacionadas aos totais e itens usados, se não estiverem em pistas.h ou jogo.h.
#include "dados.h"




/**
 * @brief Cria (formata) o texto de uma pista e preenche seus campos.
 *
 * Esta função recebe um ponteiro para uma estrutura Pista, um tipo de pista, um ID,
 * uma string de formato (como em printf) e uma ou duas strings para substituição
 * no formato. O texto resultante é armazenado no campo 'texto' da estrutura Pista.
 *
 * @param pista Ponteiro para a estrutura Pista a ser preenchida.
 * @param tipo  O tipo da pista (ex: TIPO_NEGACAO, TIPO_OU, TIPO_SE_ENTAO).
 * @param id    Um identificador numérico para a pista.
 * @param formato String de formato para snprintf (ex: "O local não foi %s.").
 * @param s1    Primeira string a ser inserida no formato.
 * @param s2    Segunda string a ser inserida no formato (pode ser NULL se o formato usar apenas uma string).
 */
void criar_pista(Pista* pista, TipoPista tipo, int id, const char* formato, const char* s1, const char* s2) {
    // Define o tipo e o ID da pista na estrutura.
    pista->tipo = tipo;
    pista->id = id;


    // Formata o texto da pista usando snprintf para evitar estouro de buffer.
    // sizeof(pista->texto) garante que não se escreva além do tamanho alocado para pista->texto.
    if (s2) { // Se uma segunda string de substituição (s2) for fornecida:
        snprintf(pista->texto, sizeof(pista->texto), formato, s1, s2);
    } else {  // Se apenas uma string de substituição (s1) for fornecida:
        snprintf(pista->texto, sizeof(pista->texto), formato, s1);
    }
}


/**
 * @brief Gera um conjunto de 12 pistas para a rodada atual do jogo.
 *
 * As pistas são criadas com base nos itens sorteados para a rodada (fornecidos pela estrutura 'itens').
 * Os itens corretos (gabarito) são geralmente os que estão no índice [0] dos arrays em 'itens',
 * enquanto outros índices ([1], [2], etc.) são usados para criar pistas falsas ou condicionais.
 *
 * @param pistas Array de 12 estruturas Pista que será preenchido com as pistas geradas.
 * @param itens  Estrutura ItensUsados contendo os índices dos suspeitos, armas e locais
 * sorteados para a rodada atual.
 */
void gerar_pistas(Pista pistas[12], ItensUsados itens) {
    // Pistas de Negação (indicam o que NÃO é o correto)
    // Usa itens dos índices [1] ou [2] para criar pistas que excluem opções.
    criar_pista(&pistas[0], TIPO_NEGACAO, 0, "O local não foi %s.", NOMES_LOCAIS[itens.locais[2]], NULL);
    criar_pista(&pistas[1], TIPO_NEGACAO, 1,"O assassino não foi %s.", NOMES_SUSPEITOS[itens.suspeitos[1]], NULL);
    criar_pista(&pistas[2], TIPO_NEGACAO, 2, "A arma não foi %s.", NOMES_ARMAS[itens.armas[1]], NULL);


    // Pistas do tipo "OU" (uma das duas afirmações é verdadeira)
    // A pista 3 sugere que ou o suspeito correto (itens.suspeitos[0]) é o assassino,
    // OU a arma foi uma arma incorreta (itens.armas[2]).
    // A pista 4 sugere que ou a arma correta (itens.armas[0]) foi usada,
    // OU o local foi um local incorreto (itens.locais[1]).
    criar_pista(&pistas[3], TIPO_OU, 3,"O assassino é %s ou a arma foi %s.", NOMES_SUSPEITOS[itens.suspeitos[0]], NOMES_ARMAS[itens.armas[2]]);
    criar_pista(&pistas[4], TIPO_OU, 4, "A arma foi %s ou o local foi %s.", NOMES_ARMAS[itens.armas[0]], NOMES_LOCAIS[itens.locais[1]]);


    // Pistas do tipo "SE ... ENTÃO ..." (condicionais)
    // Estas pistas estabelecem relações entre os itens corretos e incorretos.
    // Ex: Pista 5: Se o assassino é o correto (suspeitos[0]), então a arma NÃO foi armas[1].
    // Ex: Pista 7: Se a arma foi a correta (armas[0]), então o local foi o correto (locais[0]).
    // Ex: Pista 8: Se o local foi o correto (locais[0]), então o assassino foi o correto (suspeitos[0]).
    criar_pista(&pistas[5], TIPO_SE_ENTAO, 5,"Se o assassino é %s, então a arma não foi %s.", NOMES_SUSPEITOS[itens.suspeitos[0]], NOMES_ARMAS[itens.armas[1]]);
    criar_pista(&pistas[6], TIPO_SE_ENTAO, 6, "Se o local foi %s, então o assassino não foi %s.", NOMES_LOCAIS[itens.locais[1]], NOMES_SUSPEITOS[itens.suspeitos[2]]);
    criar_pista(&pistas[7], TIPO_SE_ENTAO, 7, "Se a arma foi %s, então o local foi %s.", NOMES_ARMAS[itens.armas[0]], NOMES_LOCAIS[itens.locais[0]]);
    criar_pista(&pistas[8], TIPO_SE_ENTAO, 8, "Se o local foi %s, então o assassino foi %s.", NOMES_LOCAIS[itens.locais[0]], NOMES_SUSPEITOS[itens.suspeitos[0]]);
    criar_pista(&pistas[9], TIPO_SE_ENTAO, 9, "Se o assassino foi %s, então a arma foi %s.", NOMES_SUSPEITOS[itens.suspeitos[2]], NOMES_ARMAS[itens.armas[1]]); // Esta pista parece contraditória se suspeitos[2] e armas[1] não forem a solução. A lógica das pistas deve ser cuidadosamente verificada para garantir que sejam úteis e não enganosas de forma injusta.
    criar_pista(&pistas[10], TIPO_SE_ENTAO, 10, "Se a arma foi %s, então o local não foi %s.", NOMES_ARMAS[itens.armas[2]], NOMES_LOCAIS[itens.locais[1]]);
    criar_pista(&pistas[11], TIPO_SE_ENTAO, 11, "Se o local foi %s, então a arma não foi %s.", NOMES_LOCAIS[itens.locais[2]], NOMES_ARMAS[itens.armas[0]]);
}


/**
 * @brief Embaralha a ordem das pistas em um array.
 *
 * Usa o algoritmo de Fisher-Yates (modern version) para randomizar a ordem
 * das 12 pistas no array fornecido.
 *
 * @param pistas Array de 12 estruturas Pista a ser embaralhado.
 */
void embaralhar_pistas(Pista pistas[12]){
    // Inicializa o gerador de números aleatórios usando o tempo atual como semente.
    // NOTA: Idealmente, srand() deve ser chamado apenas UMA VEZ no início do programa
    // (por exemplo, na função main) para garantir melhor aleatoriedade. Se esta função
    // e outras que chamam srand(time(NULL)) (como gerar_rodada) forem chamadas
    // muito próximas no tempo, elas podem usar a mesma semente, resultando em
    // sequências de números "aleatórios" idênticas ou previsíveis.
    srand(time(NULL));


    // Algoritmo de embaralhamento de Fisher-Yates.
    // Itera do último elemento (índice 11) até o segundo elemento (índice 1).
    for (int i = 11; i > 0; i--) {
        // Gera um índice aleatório 'j' entre 0 e 'i' (inclusive).
        int j = rand() % (i + 1);
        // Troca a pista na posição 'i' com a pista na posição 'j'.
        Pista temp = pistas[i]; // Armazena temporariamente a pista em 'i'.
        pistas[i] = pistas[j];  // Copia a pista de 'j' para 'i'.
        pistas[j] = temp;       // Copia a pista original de 'i' (armazenada em temp) para 'j'.
    }
}
