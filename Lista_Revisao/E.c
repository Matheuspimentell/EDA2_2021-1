#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (){
    int TotalLinhas, LinhaAtual, ColunaAtual, i = 0;
    char comando [1];
    
    scanf("%d\n", &TotalLinhas);

    char **linhas;

    linhas = malloc (TotalLinhas*sizeof(char));

    while (i < TotalLinhas){
        linhas[i] = malloc(1000*sizeof(char));
        fgets(linhas[i], 1000, stdin);
        i++;
    }

    scanf("%d %d", &LinhaAtual, &ColunaAtual);

    while (scanf("%c", comando) != EOF){
        // Lógica para subir e descer linhas aqui
    }


    printf("linha: %d coluna: %d\n", LinhaAtual, ColunaAtual);
    printf("%s", linhas[0]);
    printf("%s", linhas[1]);

    free(linhas);
    return 0;
}