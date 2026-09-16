#include <stdio.h>
#include <stdlib.h>

void lerArquivo (){
    FILE *arquivo;
    int numeroTeste;

    arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Lendo um inteiro
    fscanf(arquivo, "%d", &numeroTeste);

    fclose(arquivo);

    // Agora você pode usar os valores lidos
    printf("Número: %d\n", numeroTeste);


    return 0;
}



int main(){
   lerArquivo();

   return 0;

}