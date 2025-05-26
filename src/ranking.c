#include "ranking.h"
#include "screen.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_RANKING "ranking.csv"
#define MAX_ENTRADAS 100

typedef struct {
    char nome[50];
    double tempo;
} EntradaRanking;

int validar_nome(const char *nome) {
    for (int i = 0; nome[i]; i++) {
        if (nome[i] == ',' || !isprint(nome[i])) return 0;
    }
    return 1;
}

void salvar_ranking(const char *nome, double tempo) {
    FILE *f = fopen(ARQUIVO_RANKING, "a");
    if (!f) return;

    fprintf(f, "%s,%.2f\n", nome, tempo);  // Remove o segundo tempo que estava duplicado
    fclose(f);
}

int comparar_tempos(const void *a, const void *b) {
    const EntradaRanking *ea = (const EntradaRanking *)a;
    const EntradaRanking *eb = (const EntradaRanking *)b;

    if (ea->tempo < eb->tempo) return -1;
    if (ea->tempo > eb->tempo) return 1;
    return 0;
}

void mostrar_ranking() {
    screenClear();

    FILE *f = fopen(ARQUIVO_RANKING, "r");
    if (!f) {
        printf("Ranking vazio ou arquivo não encontrado.\n");
        getchar();
        return;
    }

    EntradaRanking entradas[MAX_ENTRADAS];
    int count = 0;
    char linha[100];

    while (fgets(linha, sizeof(linha), f) && count < MAX_ENTRADAS) {
        char nome[50];
        double tempo;
        if (sscanf(linha, "%49[^,],%lf", nome, &tempo) == 2) {
            strncpy(entradas[count].nome, nome, sizeof(entradas[count].nome));
            entradas[count].tempo = tempo;
            count++;
        }
    }

    fclose(f);

    qsort(entradas, count, sizeof(EntradaRanking), comparar_tempos);

    printf("\n======== RANKING ========\n");
    printf("%-5s %-20s %-10s\n", "#", "Nome", "Tempo(s)");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2fs\n", i + 1, entradas[i].nome, entradas[i].tempo);
    }

    printf("\nPressione ENTER para voltar...\n");
    getchar();
}
