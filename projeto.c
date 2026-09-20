/*
 * Projeto e Análise de Algoritmos II - Universidade Presbiteriana Mackenzie
 * Backup offline do professor Leonardo
 *
 * Integrantes do grupo:
 *   - Beatriz Savazzi Del Bianco - RA: 10735936
 *   - Laura YUmmi - RA: 10735
 *
 * Uso: ./backup <ARQUIVO_ENTRADA> <ARQUIVO_SAÍDA>
 *
 * Técnica: Programação Dinâmica (problema da soma de subconjuntos).
 * Procuramos um subconjunto de arquivos (Pendrive A) cuja soma S satisfaça
 *      total - capacidade <= S <= capacidade
 * O restante dos arquivos (Pendrive B) cabe automaticamente no outro pendrive.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARQUIVOS 50

/* Mostra as mensagens de uso do programa. */
void imprimirUso(void) {
    printf("Utilizar comando:\n");
    printf("./programa <ARQUIVO_ENTRADA> <ARQUIVO_SAÍDA>\n");
}

/* Escreve no arquivo de saída os arquivos de um pendrive (um por linha). */
void imprimirPendrive(FILE *saida, int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        fprintf(saida, "%d GB\n", vetor[i]);
    }
}

/*
 * Tenta distribuir os arquivos entre os dois pendrives (cada um com 'cap' GB).
 * Retorna 1 se conseguiu (preenche A, B, *a e *b) ou 0 se é impossível.
 */
int organizarArquivos(int entrada[], int tamanho, int cap,
                      int A[], int *a, int B[], int *b) {
    int total = 0;
    for (int i = 0; i < tamanho; i++) total += entrada[i];

    /* Se a soma passa da capacidade dos dois pendrives, nem adianta tentar. */
    if (total > 2 * cap) return 0;

    /* alcancavel[s] = 1 se algum subconjunto dos arquivos soma exatamente s.
       origem[s]     = índice do último arquivo usado para formar s.          */
    char *alcancavel = calloc(cap + 1, sizeof(char));
    int *origem = malloc((cap + 1) * sizeof(int));
    if (alcancavel == NULL || origem == NULL) {
        free(alcancavel);
        free(origem);
        return 0;
    }
    alcancavel[0] = 1;
    origem[0] = -1;

    for (int i = 0; i < tamanho; i++) {
        /* Percorre de trás para frente para usar cada arquivo uma única vez. */
        for (int s = cap; s >= entrada[i]; s--) {
            if (!alcancavel[s] && alcancavel[s - entrada[i]]) {
                alcancavel[s] = 1;
                origem[s] = i;
            }
        }
    }

    /* Escolhe a soma válida mais equilibrada entre os dois pendrives. */
    int inferior = total - cap;
    if (inferior < 0) inferior = 0;
    int melhor = -1, melhorDif = 0;
    for (int s = inferior; s <= cap; s++) {
        if (alcancavel[s]) {
            int dif = total - 2 * s;
            if (dif < 0) dif = -dif;
            if (melhor == -1 || dif < melhorDif) {
                melhor = s;
                melhorDif = dif;
            }
        }
    }

    int achou = (melhor != -1);
    if (achou) {
        char usado[MAX_ARQUIVOS] = {0};
        *a = 0;
        *b = 0;

        /* Reconstrói o subconjunto do Pendrive A voltando pelas origens. */
        int s = melhor;
        while (s > 0) {
            int i = origem[s];
            usado[i] = 1;
            s -= entrada[i];
        }
        for (int i = 0; i < tamanho; i++) {
            if (usado[i]) A[(*a)++] = entrada[i];
            else          B[(*b)++] = entrada[i];
        }
    }

    free(alcancavel);
    free(origem);
    return achou;
}

/* Lê todos os testes do arquivo de entrada e grava os resultados na saída.
   Retorna 0 em caso de sucesso e 1 se o formato da entrada for inválido. */
int processarArquivo(FILE *entrada, FILE *saida) {
    int numeroTestes;

    if (fscanf(entrada, "%d", &numeroTestes) != 1 || numeroTestes < 0) {
        return 1;
    }

    for (int t = 0; t < numeroTestes; t++) {
        int L, quantidade;
        int documentos[MAX_ARQUIVOS];
        int pendriveA[MAX_ARQUIVOS], pendriveB[MAX_ARQUIVOS];
        int a = 0, b = 0;

        if (fscanf(entrada, "%d %d", &L, &quantidade) != 2) return 1;
        if (L <= 0 || quantidade < 0 || quantidade > MAX_ARQUIVOS) return 1;

        for (int j = 0; j < quantidade; j++) {
            if (fscanf(entrada, "%d", &documentos[j]) != 1 || documentos[j] <= 0) {
                return 1;
            }
        }

        int cap = L / 2; /* os dois pendrives têm o mesmo tamanho */

        fprintf(saida, "%d GB\n", L);

        if (organizarArquivos(documentos, quantidade, cap,
                              pendriveA, &a, pendriveB, &b)) {
            fprintf(saida, "Pendrive A (%d GB)\n", cap);
            imprimirPendrive(saida, pendriveA, a);
            fprintf(saida, "\nPendrive B (%d GB)\n", cap);
            imprimirPendrive(saida, pendriveB, b);
            fprintf(saida, "\n");
        } else {
            fprintf(saida, "Impossível gravar todos os arquivos nos pendrives.\n\n");
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Combinação não realizada. Parâmetros incorretos.\n");
        imprimirUso();
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) {
        printf("Combinação não realizada. Arquivo de entrada não existe.\n");
        imprimirUso();
        return 1;
    }

    FILE *saida = fopen(argv[2], "w");
    if (saida == NULL) {
        printf("Combinação não realizada. Não foi possível criar o arquivo de saída.\n");
        imprimirUso();
        fclose(entrada);
        return 1;
    }

    int resultado = processarArquivo(entrada, saida);
    fclose(entrada);
    fclose(saida);

    if (resultado != 0) {
        printf("Combinação não realizada. Formato do arquivo de entrada inválido.\n");
        return 1;
    }

    printf("Combinação realizada no arquivo %s.\n", argv[2]);
    printf("Arquivo de entrada: %s\n", argv[1]);
    return 0;
}
