#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Variáveis fixadas no início do jogo
long long int LINHA_INCIAL, COLUNA_INICIAL, PONTOS_INCIAL; //long long int suporta dados entre -2^63 e 2^63 - 1
unsigned int TURNOS; // unsigned int para armazenar dado da quantidade de turnos

//Cada célula contém
typedef struct celula{
    int temEdazinho; //0 caso não tenha um edazinho na celula, 1 caso tenha 
    long long int pontuacao, linha, coluna;
}celula;

//Sonda a posicao desejada e retorna a célula e seus atributos
celula sondar(long long int linha, long long int coluna){
    struct celula teste;

    //Define os valores para a célula
    teste.temEdazinho = 0;
    teste.pontuacao = (rand() % (100 - 10)) + 10; //Para gerar números aleatórios entre 100 e 10
    teste.linha = linha;
    teste.coluna = coluna;

    //Retorna a célula criada
    return teste;
}

//Checar a validade da linha, retornar 1 caso válida, 0 caso inválida
int linhaValida(long long int linha){
    //CHECANDO APENAS PARA O PRIMEIRO TURNO
    if(linha == LINHA_INCIAL+1 || linha == LINHA_INCIAL-1 || linha == LINHA_INCIAL){
        //Retorna 1 caso a linha seja válida
        return 1;
    } else {
        //Retorna 0 caso a linha seja inválida
        return 0;
    }
}
//Checar a validade da coluna, retornar 1 caso válida, 0 caso inválida
int colunaValida(long long int coluna){
    //CHECANDO APENAS PARA O PRIMEIRO TURNO
    if(coluna == COLUNA_INICIAL+1 || coluna == COLUNA_INICIAL-1 || coluna == COLUNA_INICIAL){
        //Retorna 1 caso a linha seja válida
        return 1;
    } else {
        //Retorna 0 caso a linha seja inválida
        return 0;
    }
}

// O objetivo do jogo é crescer o máximo possível adiquirindo a maior quantidade de pontos.

int main(){
    
    long long int pontuacaoTotal = 0; //pontuacao total de edazinhos
    unsigned int totalEdazinhos = 0; //total de edazinhos no mapa

    scanf("%lld %lld %lld %u", &LINHA_INCIAL, &COLUNA_INICIAL, &PONTOS_INCIAL, &TURNOS);
    
    //Definição da primeira célula
    struct celula inicial;
    inicial.linha = LINHA_INCIAL;
    inicial.coluna = COLUNA_INICIAL;
    inicial.pontuacao = PONTOS_INCIAL;
    inicial.temEdazinho = 1;
    totalEdazinhos++;
    pontuacaoTotal += PONTOS_INCIAL;
    
    //Variável de controle de turnos
    unsigned int i = 0;

    //Inicia o jogo
    do{
        //Fazer a cada turno
        i++;
        printf("Turno %d\n\n", i);
        char opcao[10];
        //Scan da opcao desejada
        scanf("%s", opcao);
        //Caso seja a opcao de sondagem
        if(strcmp(opcao, "sondar") == 0){
            long long int linha, coluna;
            scanf("%lld %lld", &linha, &coluna); //Ler a linha e coluna a sondar
            if(linhaValida(linha) && colunaValida(coluna)){
                struct celula testando = sondar(linha, coluna); //Retorna a linha e coluna sondada
                printf("linha: %lld\n", testando.linha);
                printf("coluna: %lld\n", testando.coluna);
                printf("pontuacao: %lld\n", testando.pontuacao);
                printf("Ocupada? %d\n", testando.temEdazinho);
            } else {
                printf("Jogada invalida.\n");
                pontuacaoTotal = 0;
                break;
            }
        }
    } while (i < TURNOS);

    printf("Game Over.\nPontuacao final: %lld\n", pontuacaoTotal);
    return 0;
}