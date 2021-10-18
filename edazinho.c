// O objetivo do jogo é crescer o máximo possível adiquirindo a maior quantidade de pontos.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Variáveis fixadas no início do jogo
long long int LINHA_INCIAL, COLUNA_INICIAL, PONTOS_INCIAL; //long long int suporta dados entre -2^63 e 2^63 - 1
unsigned int TURNOS, tamanhoHash; // unsigned int para armazenar dado da quantidade de turnos
long MAX = ((pow(2,21))-1), MIN = -(pow(2,21)); // MAX = 2^21, MIN = -2^21

//Para gerar números aleatórios entre MAX e MIN
#define geraPontuacao() \
    ((rand()%(MAX-MIN))+MIN);

//Gerar código hash para saber posições disponíveis para sondagem
#define geraHash(linha, coluna) \
    (abs((linha+coluna)%tamanhoHash));

//Lista simplemente encadeada com todos os edazinhos
typedef struct edazinhos{
    //Linha e coluna do edazinho atual
    long long int linha, coluna;
    //Ponteiro para o próximo edazinho
    struct edazinhos *prox;
}edazinhos;

//Implementar fila de prioridade para as células sondadas com base na pontuação (Binary heap)
typedef struct filaDominacao{
    //Linha e coluna da célula sondada
    long long int linha, coluna;
    //Ponteiro para a próxima célula já sondada
    struct filaDominacao *prox;
}filaDominacao;

//Lógica para sondar uma posição
edazinhos *sondar(edazinhos *listaEdazinhos, long long int Linha, long long int Coluna){
    //Checar posições válidas para sondagem
    return listaEdazinhos;
}

//Lógica para dominar uma posição
edazinhos *dominar(edazinhos *listaEdazinhos, long long int Linha, long long int Coluna){
    
    //Inserir um edazinho no final da lista de edazinhos
    edazinhos *aux, *novoEdazinho;
    
    //Aloca memória para +1 edazinho e seta a sua linha e coluna
    novoEdazinho = (edazinhos *) malloc(sizeof(edazinhos));
    novoEdazinho->linha = Linha;
    novoEdazinho->coluna = Coluna;
    novoEdazinho->prox = NULL;
    
    //Faz o ponteiro auxiliar ir até o final da lista de edazinhos
    aux = listaEdazinhos;
    while(aux->prox != NULL){
        aux = aux->prox;
    }

    //Insere o novo edazinho no final da lista
    aux->prox = novoEdazinho;

    return listaEdazinhos;
}

//Implementação do jogador: Reagir às entradas do árbitro
int main(){
    
    scanf("%u", &TURNOS);    

    tamanhoHash = (9+(5*(TURNOS-1)));

    if(tamanhoHash%2 == 0){
        tamanhoHash++;
    }

    long long int linhaI = geraPontuacao();
    long long int colunaI = geraPontuacao();

    long long int linhaJ = linhaI;
    long long int colunaJ = colunaI;

    int i = 1;
    while(i <= 30){
        printf("linha:%lld coluna:%lld\n", linhaI, colunaI);
        unsigned int teste = geraHash(linhaI, colunaI);
        printf("hashKey:%u\n\n", teste);
        linhaI++;
        colunaI++;
        i++;
    }


    printf("===================================================\n");

    int j = 1;
    while(j <= 30){
        printf("linha:%lld coluna:%lld\n", linhaJ, colunaJ);
        unsigned int teste = geraHash(linhaJ, colunaJ);
        printf("hashKey:%u\n\n", teste);
        linhaJ--;
        colunaJ--;
        j++;
    }

    return 0;

}