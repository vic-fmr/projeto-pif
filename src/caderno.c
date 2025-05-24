#include <stdio.h>
#include <stdlib.h> // Para system()
#include <termios.h>
#include <unistd.h> // Para STDIN_FILENO
#include <stdbool.h> // Para usar o tipo bool
#include <string.h> // Para snprintf

#include "pistas.h" // Inclui as definições de Pista e gerar_pistas
#include "dados.h"  // Inclui as definições dos nomes (NOMES_LOCAIS, etc.)

// Número total de pistas que podem ser geradas por pistas.c
#define TOTAL_PISTAS_POSSIVEIS 12

// Array para armazenar todas as pistas possíveis geradas
Pista todas_as_pistas[TOTAL_PISTAS_POSSIVEIS];

// Array para armazenar as pistas que o jogador coletou
Pista pistas_coletadas[TOTAL_PISTAS_POSSIVEIS];
int num_pistas_coletadas = 0;

// Array para verificar se uma pista com um dado ID já foi coletada
bool pista_id_ja_coletado[TOTAL_PISTAS_POSSIVEIS];

// Protótipos das funções
char getch();
void esconderCaderno();
void mostrarListaPistas();
void mostrarPistaDetalhada(int indiceListaColetadas);
void gerenciarCaderno();
void init_caderno();
void adicionar_pista_coletada(int id_pista_para_adicionar);

// Função para capturar um caractere sem precisar pressionar Enter
char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Inicializa o sistema do caderno, gerando todas as pistas e resetando as coletadas
void init_caderno() {
    gerar_pistas(todas_as_pistas, (ItensUsados){
        // Exemplo de itens sorteados - isto deve vir do seu jogo principal
        // Para fins de teste, estou usando valores fixos.
        // Na prática, você passaria os itens sorteados do seu jogo.
        .locais = {0, 1, 2}, // IDs de locais
        .suspeitos = {0, 1, 2}, // IDs de suspeitos
        .armas = {0, 1, 2} // IDs de armas
    });

    num_pistas_coletadas = 0;
    for (int i = 0; i < TOTAL_PISTAS_POSSIVEIS; ++i) {
        pista_id_ja_coletado[i] = false;
    }
}

// Adiciona uma pista à lista de pistas coletadas, verificando por ID
void adicionar_pista_coletada(int id_pista_para_adicionar) {
    // Verifica se o ID é válido e se a pista já não foi coletada
    if (id_pista_para_adicionar >= 0 && id_pista_para_adicionar < TOTAL_PISTAS_POSSIVEIS &&
        !pista_id_ja_coletado[id_pista_para_adicionar]) {

        // Marca como coletada
        pista_id_ja_coletado[id_pista_para_adicionar] = true;
        // Copia a pista da lista de todas as pistas para a lista de coletadas
        pistas_coletadas[num_pistas_coletadas] = todas_as_pistas[id_pista_para_adicionar];
        num_pistas_coletadas++;
        // Opcional: mostrar uma mensagem para o jogador
        // printf("Nova pista adicionada ao caderno!\n");
        // getch(); // Pausa para o jogador ver a mensagem
    }
}

// Função para "esconder" o caderno e mostrar o estado do jogo
void esconderCaderno() {
    system("clear");
    printf("Jogo rodando... Pressione 'C' para abrir o caderno.\n");
}

// Função para mostrar a lista de pistas coletadas
void mostrarListaPistas() {
    system("clear");
    printf("=====================================\n");
    printf("|           CADERNO DE PISTAS       |\n");
    printf("=====================================\n");
    if (num_pistas_coletadas == 0) {
        printf("| Nenhuma pista coletada ainda.     |\n");
        printf("|                                   |\n");
    } else {
        printf("| Selecione uma pista para ver:     |\n");
        for (int i = 0; i < num_pistas_coletadas; ++i) {
            // Usa o texto da pista coletada para exibir no menu
            printf("| %d. Pista: %-22.22s |\n", i + 1, pistas_coletadas[i].texto); // .22 para truncar se for muito longo
        }
    }
    printf("|                                   |\n");
    printf("| Pressione 'C' para fechar.        |\n");
    printf("=====================================\n");
}

// Função para mostrar uma pista específica em detalhe
void mostrarPistaDetalhada(int indiceListaColetadas) {
    system("clear");
    printf("=====================================\n");
    printf("|           PISTA DETALHADA         |\n");
    printf("=====================================\n");
    printf("|                                   |\n");
    
    // Obtém o texto da pista da lista de coletadas
    char texto_pista_formatado[100];
    snprintf(texto_pista_formatado, sizeof(texto_pista_formatado), " - %s", pistas_coletadas[indiceListaColetadas].texto);
    
    // Imprime a pista com formatação para caber na caixa
    // Calcula o preenchimento para centralizar ou manter o layout
    int len = strlen(texto_pista_formatado);
    int max_len_inside_box = 33; // Considerando 35 de largura total - 2 para bordas
    
    if (len > max_len_inside_box) { // Se a pista for muito longa, trunca
        texto_pista_formatado[max_len_inside_box] = '\0';
        printf("| %-33s |\n", texto_pista_formatado);
    } else {
        printf("| %-*s |\n", max_len_inside_box, texto_pista_formatado);
    }

    printf("|                                   |\n");
    printf("| Pressione 'V' para voltar a lista.|\n");
    printf("| Pressione 'C' para fechar.        |\n");
    printf("=====================================\n");
}

// Função para gerenciar a navegação dentro do caderno de pistas
void gerenciarCaderno() {
    char opcaoCaderno;
    int estadoInternoCaderno = 0; // 0: mostrando lista, 1: mostrando detalhe
    int pistaSelecionadaIndex = -1; // Índice na lista de pistas_coletadas

    mostrarListaPistas(); // Começa mostrando a lista

    while (1) {
        opcaoCaderno = getch();

        if (estadoInternoCaderno == 0) { // Se está na lista de pistas
            if (opcaoCaderno >= '1' && opcaoCaderno < ('1' + num_pistas_coletadas)) {
                pistaSelecionadaIndex = opcaoCaderno - '1';
                mostrarPistaDetalhada(pistaSelecionadaIndex);
                estadoInternoCaderno = 1; // Muda para o estado de mostrar detalhe
            } else if (opcaoCaderno == 'c' || opcaoCaderno == 'C') {
                break; // Sai do loop do caderno
            }
        } else if (estadoInternoCaderno == 1) { // Se está mostrando uma pista detalhada
            if (opcaoCaderno == 'v' || opcaoCaderno == 'V') {
                mostrarListaPistas();
                estadoInternoCaderno = 0; // Volta para a lista
                pistaSelecionadaIndex = -1;
            } else if (opcaoCaderno == 'c' || opcaoCaderno == 'C') {
                break; // Sai do loop do caderno
            }
        }
    }
    esconderCaderno(); // Ao sair, "fecha" o caderno e limpa a tela
}

int main() {
    // É crucial que `init_caderno` seja chamado antes de qualquer tentativa de adicionar ou exibir pistas.
    // O `main` aqui é apenas para demonstração do caderno.
    // No seu jogo final, `init_caderno()` seria chamado uma vez no início do jogo,
    // e `adicionar_pista_coletada()` seria chamado pela lógica de movimento.

    init_caderno(); // Inicializa as pistas e o estado do caderno

    printf("Simulando a coleta de algumas pistas:\n");
    printf("Pressione qualquer tecla para continuar...\n");
    getch();

    // Simulação de coleta de pistas ao entrar em áreas
    adicionar_pista_coletada(0); // Ex: Pista do Auditório
    adicionar_pista_coletada(3); // Ex: Pista da Garagem
    adicionar_pista_coletada(0); // Tentativa de adicionar a mesma pista (não deve adicionar)
    adicionar_pista_coletada(5); // Ex: Outra pista

    printf("Pistas simuladas adicionadas. Pressione 'C' para abrir o caderno.\n");
    printf("Pressione ESC para sair da simulação.\n");

    char tecla;
    esconderCaderno(); // Estado inicial do jogo

    while (1) {
        tecla = getch();

        if (tecla == 'c' || tecla == 'C') {
            gerenciarCaderno();
        }

        if (tecla == 27) { // Tecla Esc para sair do jogo
            break;
        }
    }

    // Restaura configurações do terminal
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    system("clear"); // Limpa a tela ao sair

    return 0;
}