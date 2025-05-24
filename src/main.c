#include <stdio.h>
#include <stdlib.h> // Para system()
#include <termios.h>
#include <unistd.h> // Para STDIN_FILENO, getch (read)

// Constantes para as pistas
#define NUM_PISTAS 3
const char *pistas[NUM_PISTAS] = {
    "A porta da cozinha range.",
    "O mordomo estava na biblioteca.",
    "Ha uma chave no jardim." // Removido acento para compatibilidade simples de console
};

// Protótipos das funções
char getch();
void esconderCaderno();
void mostrarListaPistas();
void mostrarPistaDetalhada(int indicePista);
void gerenciarCaderno();

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

// Função para "esconder" o caderno e mostrar o estado do jogo
void esconderCaderno() {
    system("clear");
    printf("Jogo rodando... Pressione 'C' para abrir o caderno.\n");
}

// Função para mostrar a lista de pistas selecionáveis
void mostrarListaPistas() {
    system("clear");
    printf("=====================================\n");
    printf("|       CADERNO DE PISTAS           |\n");
    printf("=====================================\n");
    printf("| Selecione uma pista para ver:     |\n");
    for (int i = 0; i < NUM_PISTAS; ++i) {
        // Ajusta o espaçamento para manter o layout
        printf("| %d. Pista %-26d|\n", i + 1, i + 1);
    }
    printf("|                                   |\n");
    printf("| Pressione 'C' para fechar.        |\n");
    printf("=====================================\n");
}

// Função para mostrar uma pista específica em detalhe
void mostrarPistaDetalhada(int indicePista) {
    system("clear");
    printf("=====================================\n");
    printf("|           PISTA DETALHADA         |\n");
    printf("=====================================\n");
    printf("|                                   |\n");
    
    char texto_pista_formatado[100];
    // Adiciona " - " antes da pista, como no original
    snprintf(texto_pista_formatado, sizeof(texto_pista_formatado), " - %s", pistas[indicePista]);
    // %-33s garante que o texto seja alinhado à esquerda e ocupe 33 caracteres
    // (se for menor, preenche com espaços; se for maior, pode quebrar o layout)
    printf("| %-33s |\n", texto_pista_formatado); 
    
    printf("|                                   |\n");
    printf("| Pressione 'V' para voltar a lista.|\n");
    printf("| Pressione 'C' para fechar.        |\n");
    printf("=====================================\n");
}

// Função para gerenciar a navegação dentro do caderno de pistas
void gerenciarCaderno() {
    char opcaoCaderno;
    // 0: mostrando lista de pistas, 1: mostrando pista detalhada
    int estadoInternoCaderno = 0; 
    int pistaSelecionadaIndex = -1;

    mostrarListaPistas(); // Começa mostrando a lista

    while (1) {
        opcaoCaderno = getch();

        if (estadoInternoCaderno == 0) { // Se está na lista de pistas
            if (opcaoCaderno >= '1' && opcaoCaderno < ('1' + NUM_PISTAS)) {
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
    char tecla;
    esconderCaderno(); // Estado inicial do jogo

    while (1) {
        tecla = getch();

        if (tecla == 'c' || tecla == 'C') {
            // 'C' agora abre o caderno e entra no modo de gerenciamento
            // A função gerenciarCaderno só retorna quando o usuário decide fechar o caderno por dentro dela
            gerenciarCaderno(); 
        }

        // Tecla Esc para sair do jogo (opcional, mantido do original)
        if (tecla == 27) { 
            break;
        }
        // Outras teclas pressionadas no "jogo" poderiam ser tratadas aqui
    }

    // Restaura configurações do terminal (importante se o jogo terminasse abruptamente)
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    system("clear"); // Limpa a tela ao sair

    return 0;
}