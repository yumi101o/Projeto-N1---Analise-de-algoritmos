#include <stdio.h>
#include <stdlib.h>

void OrganizarArq (int A[]; int B[]){

}

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

    for (int i = 1; i <= nuemeroTeste; i++){
        int gb;
        int numeroArquivo;
        int soma = 0

        fscanf(arquivo, "%d", &gb);

        gb = gb/2;

        fscanf(arquivo, "%d", &numeroArquivo);

        int Documentos [numeroArquivo];
        int PenDriveA [gb];
        int PenDriveB [gb];

        for (int j = 0; j <= numeroArquivo && soma < gb*2; j++){
            fscanf(arquivo, "%d", &Documentos[j]);
            soma = soma + Documentos[j];

            if (soma > gb*2) {
                printf("Impossível gravar todos os arquivos nos pendrives.\n");
            }
        }

        if (soma < gb*2){



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
