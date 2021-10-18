// O objetivo do jogo é crescer o máximo possível adiquirindo a maior quantidade de pontos.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Variáveis fixadas no início do jogo
long long int LINHA_INCIAL, COLUNA_INICIAL, PONTOS_INCIAL; //long long int suporta dados entre -2^63 e 2^63 - 1
unsigned int TURNOS; // unsigned int para armazenar dado da quantidade de turnos
long MAX = pow(2,21), MIN = -(pow(2,21)); // MAX = 2^21, MIN = -2^21

//Para gerar números aleatórios entre max e min
#define geraPontuacao(max, min) \
    ((rand()%(max-min))+min); 

//Lista simplemente encadeada com todos os edazinhos
typedef struct edazinhos{
    //Linha e coluna do edazinho atual
    long long int linha, coluna;
    //Ponteiro para o próximo edazinho
    struct edazinhos *prox;
}edazinhos;

//Implementar fila de prioridade para as células sondadas com base na pontuação

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

    //Variável que armazena a pontuação total
    double pontuacaoTotal = 0;

    //Ler 3 long int e 1 unsigned int
    scanf("%lld %lld %lld %u", &LINHA_INCIAL, &COLUNA_INICIAL, &PONTOS_INCIAL, &TURNOS);

    //Cria a lista de edazinhos
    edazinhos *listaEdazinhos;
    //Aloca a memória para o 1° edazinho e insere ele na lista
    listaEdazinhos = (edazinhos *) malloc(sizeof(edazinhos));
    listaEdazinhos->linha = LINHA_INCIAL;
    listaEdazinhos->coluna = COLUNA_INICIAL;
    listaEdazinhos->prox = NULL;

    //Incrementa a pontuação total
    pontuacaoTotal += PONTOS_INCIAL;

    /*Formatos de saídas do árbitro: ("sondagem %lld %lld %lf", linha, coluna, pontuacao)
                                     ("dominacao %lf", pontuacao)
    */

    /*Formatos de saídas do jogador: ("sondar %lld %lld", linha, coluna)
                                     ("dominar %lld %lld", linha, coluna)
    */

    /*a posição a ser sondada deve estar no seguinte padrão:
        (linhaEdazinho-1,colunaEdazinho-1) <= (linha_a_ser_sondada, coluna_a_ser_sondada) <= ((linhaEdazinho-1,colunaEdazinho-1)) && 
        (linha_a_ser_sondada, coluna_a_ser_sondada) != (linhaEdazinho,colunaEdazinho)*/

    //Libera a memória usada para a lista de edazinhos
    free(listaEdazinhos);
    return 0;

}