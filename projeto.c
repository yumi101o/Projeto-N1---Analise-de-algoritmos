#include <stdio.h>
#include <stdlib.h>

int lerArquivo() {
    FILE *arquivo;
    int numeroTeste;

    arquivo = fopen("/workspaces/Projeto-N1---Analise-de-algoritmos/entrada.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1; // erro
    }

    // Lendo um inteiro
    fscanf(arquivo, "%d", &numeroTeste);

    for (int i = 1, i <= nuemroTeste, i++){
        int gb;
        int nuemroArquivo;

        fscanf(arquivo, "%d", &gb);

        gb = gb/2;

        fscanf(arquivo, "%d", &numeroArquivo);

        for (int j = 1, j <= numeroArquivo, j++){
            
        }


    }

    fclose(arquivo);

    // Agora você pode usar os valores lidos
    printf("Testes: %d\n", numeroTeste);

    return 0; // sucesso
}

int main() {
    int resultado = lerArquivo();

    if (resultado != 0) {
        printf("Falha na leitura do arquivo.\n");
    }

    return 0;
}
