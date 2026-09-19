#include <stdio.h>
#include <stdlib.h>

void imprimirPendrive(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d GB\n", vetor[i]);
    }
}

void OrganizarArq(int entrada[], int tamanho, int gb, int A[], int *a, int B[], int *b) {
    int somaA = 0, somaB = 0;
    *a = 0;
    *b = 0;

    for (int i = 0; i < tamanho; i++) {
        int valor = entrada[i];

        if (somaA + valor <= gb && somaB + valor <= gb) {
            if (somaA <= somaB) {
                A[*a] = valor;
                somaA += valor;
                (*a)++;
            } else {
                B[*b] = valor;
                somaB += valor;
                (*b)++;
            }
        }
        else if (somaA + valor <= gb) {
            A[*a] = valor;
            somaA += valor;
            (*a)++;
        }
        else if (somaB + valor <= gb) {
            B[*b] = valor;
            somaB += valor;
            (*b)++;
        }
        else {
            printf("Número %d não pode ser colocado sem ultrapassar gb\n", valor);
        }
    }
}

int lerArquivo() {
    FILE *arquivo;
    int numeroTeste;

    arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1; // erro
    }

    fscanf(arquivo, "%d", &numeroTeste);

    for (int i = 0; i < numeroTeste; i++) {
        int gb;
        int numeroArquivo;
        int soma = 0;
        int a, b;

        fscanf(arquivo, "%d", &gb);
        gb = gb / 2; // cada pendrive tem metade

        fscanf(arquivo, "%d", &numeroArquivo);

        int Documentos[numeroArquivo];
        int PenDriveA[gb];
        int PenDriveB[gb];

        for (int j = 0; j < numeroArquivo; j++) {
            fscanf(arquivo, "%d", &Documentos[j]);
            soma += Documentos[j];
        }

        printf("%d GB\n", gb * 2); // capacidade total

        if (soma > gb * 2) {
            printf("Impossível gravar todos os arquivos nos pendrives.\n\n");
        } else {
            OrganizarArq(Documentos, numeroArquivo, gb, PenDriveA, &a, PenDriveB, &b);

            printf("Pendrive A (%d GB)\n", gb);
            imprimirPendrive(PenDriveA, a);

            printf("\nPendrive B (%d GB)\n", gb);
            imprimirPendrive(PenDriveB, b);

            printf("\n");
        }
    }

    fclose(arquivo);
    return 0; // sucesso
}

int main() {
    int resultado = lerArquivo();

    if (resultado != 0) {
        printf("Falha na leitura do arquivo.\n");
    }

    return 0;
}
