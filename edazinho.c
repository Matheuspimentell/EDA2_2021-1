#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Variáveis fixadas no início do jogo
long long int LINHA_INCIAL, COLUNA_INICIAL, PONTOS_INCIAL; //long long int suporta dados entre -2^63 e 2^63 - 1
unsigned int TURNOS; // unsigned int para armazenar dado da quantidade de turnos
int PONTUACAOMAXIMA = 100, PONTUACAOMINIMA = -100;

//Cada célula contém
typedef struct celula{
    int recemDominada; //1 caso recém dominada, 0 caso contrário 
    long long int pontuacao, linha, coluna; //pontuação da célula, linha e coluna.
}celula;

//Cada edazinho
typedef struct edazinho{
    long long int linha, coluna; //linha e coluna que o edazinho se encontra
    struct edazinho *prox; //ponteiro para o próximo edazinho
}edazinho;

//Sonda a posicao desejada e retorna a célula e seus atributos
celula sondar(long long int linha, long long int coluna){
    struct celula teste;

    //Define os valores para a célula
    teste.temEdazinho = 0;
    teste.pontuacao = (rand() % (PONTUACAOMAXIMA - PONTUACAOMINIMA)) + PONTUACAOMINIMA; //Para gerar números aleatórios entre MAX e MIN
    teste.linha = linha;
    teste.coluna = coluna;

    //Retorna a célula criada
    return teste;
}

edazinho *dominar(edazinho listaEdazinhos){
    

    return Edazinhos
}

//Checar a validade da linha, retornar 1 caso válida, 0 caso inválida
int linhaValida(long long int linha, edazinho *atual){
    //CHECANDO APENAS PARA O PRIMEIRO TURNO
    if(linha == atual->linha + 1 || linha == atual->linha - 1 || linha == atual->linha){
        //Retorna 1 caso a linha seja válida
        return 1;
    } else {
        //Retorna 0 caso a linha seja inválida
        return 0;
    }
}
//Checar a validade da coluna, retornar 1 caso válida, 0 caso inválida
int colunaValida(long long int coluna, edazinho *atual){
    //CHECANDO APENAS PARA O PRIMEIRO edazinho
    if(coluna == atual->coluna + 1 || coluna == atual->coluna - 1 || coluna == atual->coluna){
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
    struct edazinho *Edazinhos = malloc(sizeof(edazinho));

    //Pede a linha inicial, coluna inicial, quantidades de pontos da celula inicial e a quantidade de turnos do jogo
    scanf("%lld %lld %lld %u", &LINHA_INCIAL, &COLUNA_INICIAL, &PONTOS_INCIAL, &TURNOS);
    
    //Total de edazinhos aumenta
    totalEdazinhos++;
    //Soma a pontuação inicial
    pontuacaoTotal += PONTOS_INCIAL;

    //Cria o primeiro edazinho
    Edazinhos->linha = LINHA_INCIAL;
    Edazinhos->coluna = COLUNA_INICIAL;
    Edazinhos->prox = NULL;

    //Variável de controle de turnos
    unsigned int i = 0;
    int jogadaInvalida = 0;
    
    //Game Loop
    do{
        //Lógica do turno
        i++;
        printf("Turno %d\n\n", i);
        
        char opcao[10];

        //Para cada edazinho
        for(int i = 1; i <= totalEdazinhos; i++){
            //Scan da opcao desejada
            scanf("%s", opcao);
        
            //Caso seja a opcao de sondagem
            if(strcmp(opcao, "sondar") == 0){

                long long int linha, coluna;

                scanf("%lld %lld", &linha, &coluna); //Ler a linha e coluna a sondar

                if(linhaValida(linha, Edazinhos) && colunaValida(coluna, Edazinhos)){

                    struct celula testando = sondar(linha, coluna); //Retorna a linha e coluna sondada
                    printf("linha: %lld\n", testando.linha);
                    printf("coluna: %lld\n", testando.coluna);
                    printf("pontuacao: %lld\n", testando.pontuacao);
                    printf("Recem dominada? %d\n", testando.recemDominada);

                } else {

                    //Em caso de jogada inválida, zerar a pontuação
                    printf("\nJogada invalida.\n");
                    pontuacaoTotal = 0;
                    jogadaInvalida = 1;
                    break;
                }
            }
        }
        //Caso jogada inválida, acabar o jogo
        if(jogadaInvalida){
            break;
        }
        printf("\n");
    } while (i < TURNOS);

    printf("Game Over.\nPontuacao final: %lld\n", pontuacaoTotal);
    return 0;
}