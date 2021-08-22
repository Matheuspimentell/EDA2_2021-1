#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char cidade[27];
    struct No *prox;
} No;

typedef struct fila{
    struct No *ini, *fim;
} fila;

fila enfileira(fila controle, char *input){
    No *nova = malloc(sizeof(No));
    nova->prox = NULL;
    strcpy(nova->cidade, input);
    if(controle.ini == NULL){
        controle.ini = nova;
        controle.fim = controle.ini;
        return controle;
    } else {
        controle.fim->prox = nova;
        controle.fim = controle.fim->prox;
        return controle;
    }
}

void imprimeOrdenado(fila controle){
    if (controle.ini == NULL){
        return;
    }
    char caracter;
    caracter = controle.ini->cidade[strlen(controle.ini->cidade)-1] - 32;
    controle.ini = controle.ini->prox;
    if(controle.ini == NULL){
        return;
    }
    if(caracter == controle.ini->cidade[0]){
        //Jogar para o final
        controle.fim->prox = controle.ini;
        controle.ini = controle.ini->prox;
        printf("%s\n", controle.ini->cidade);
        controle.fim = controle.fim->prox;
        controle.fim->prox = NULL;
        imprimeOrdenado(controle);
        return;
    } else {
        //Imprime e chama a função novamente
        printf("%s\n", controle.ini->cidade);
        imprimeOrdenado(controle);
    }
    return;
}

int main (){
    fila controle;
    controle.ini = NULL;
    controle.fim = controle.ini;
    char entrada[27];

    while(scanf("%s", entrada)!=EOF){
        controle = enfileira(controle, entrada);
    }

    if(controle.ini != NULL){
        printf("\n%s\n", controle.ini->cidade);
        imprimeOrdenado(controle);
    }
    
    
    free(controle.ini);
    free(controle.fim);
    return 0;
}