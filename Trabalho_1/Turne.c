#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tem que ser por filas
// Pegar a última letra da primeira palavra e compará-la com a primeira letra da segunda
// Caso a primeira letra da próxima palavra seja igual, mandar a palavra ao final da fila
// Caso contrário, a palavra permanece, e se repete o ciclo

typedef struct fila{
    char cidade[27];
    struct fila *prox;
} fila;

fila *enfileira (fila* primeiro, char *cidade){
    if (primeiro == NULL){
        fila *novo = malloc(sizeof(fila));
        strcpy(novo->cidade, cidade);
        novo->prox = NULL;
        primeiro = novo;
        return primeiro;
    } else {
        fila *aux, *novo;
        aux = primeiro;
        novo = malloc(sizeof(fila));
        strcpy(novo->cidade, cidade);
        novo->prox = NULL;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        return primeiro;
    }
}

void imprimeOrdem(fila *primeiro){
    if(primeiro == NULL){
        return;
    }
    char caracter;
    caracter = primeiro->cidade[strlen(primeiro->cidade)-1]-32;
    primeiro = primeiro->prox;
    if(primeiro == NULL){
        return;
    }
    if(caracter == primeiro->cidade[0]){
        fila *aux;
        aux = primeiro;
        while (aux->prox!=NULL){
            aux = aux->prox;
        }
        aux->prox = primeiro;
        primeiro = primeiro->prox;
        aux = aux->prox;
        aux->prox = NULL;
        printf("%s\n", primeiro->cidade);
        imprimeOrdem(primeiro);
        return;
    } else {
        printf("%s\n", primeiro->cidade);
        imprimeOrdem(primeiro);
    }
    return;
}

int main (){
    fila *primeiro = NULL;
    char input[27];

    while (scanf("%s", input) != EOF){
        primeiro = enfileira(primeiro, input);
    }

    // teste = input[strlen(input)-1] - 32;

    printf("\n%s\n", primeiro->cidade);
    imprimeOrdem(primeiro);   

    free(primeiro);
    return 0;
}