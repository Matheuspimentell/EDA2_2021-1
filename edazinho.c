// O objetivo do jogo é crescer o máximo possível adiquirindo a maior quantidade de pontos.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Variáveis fixadas no início do jogo
long long int LINHA_INCIAL, COLUNA_INICIAL, PONTOS_INCIAL; //long long int suporta dados entre -2^63 e 2^63 - 1
unsigned int TURNOS; // unsigned int para armazenar dado da quantidade de turnos: TURNOS varia de 10 à 2^31

//Lista simplemente encadeada com todos os edazinhos
typedef struct edazinhos{
    long long int linha, coluna; //Linha e coluna do edazinho atual
    int posicoesSondadas; // Varia entre 0 e 8. 8 = Todas as posições em volta foram sondadas | 0 = nenhuma posição foi sondada
    struct edazinhos *prox; //Ponteiro para o próximo edazinho
}edazinhos;

//Cada célula do jogo
typedef struct celula{
    long long int linha, coluna, pontos;
}celula;

/*
 *A implementação de uma HEAP é feita por meio de vetores. Onde não se usa o índice 0 do vetor.
 *A posição dos filhos de um nó da HEAP é dada por: 2*k e 2*k+1, respectivamente. Onde k é a posição do nó pai
 *Igualmente, pode-se encontrar a posição do nó pai com o resultado inteiro de k/2. Onde k é a posição do nó filho
 *A inserção deve começar pelo índice 1
 *Usar a implementação de uma MAXHeap
 *Utilizando o índice 0 para a última posição removida
 * */
celula heap[301];
int _sizeHeap = 0;

//Funções essenciais da Heap
int Pai(int index){return (index/2);}

int FilhoEsquerda(int index){return (index*2);}

int FilhoDireita(int index){return ((index*2)+1);}

//Troca simples entre 2 elementos da heap
void HeapSwap(int indexPai, int indexFilho){
    celula aux;
    aux = heap[indexPai];
    heap[indexPai] = heap[indexFilho];
    heap[indexFilho] = aux;
}

void insertHeap(celula nova){

    if(_sizeHeap == 300){
        printf("Overflow! nao foi possivel inserir na heap");
        return;
    }

    //Incrementa o tamanho da heap e insere a nova celula na primeira posição disponível
    _sizeHeap++;
    int i = _sizeHeap;
    heap[i] = nova;

    //Checar e consertar a Heap, caso necessário
    while(i > 1 && heap[Pai(i)].pontos < heap[i].pontos){
        HeapSwap(Pai(i), i);
        i = Pai(i);
    }
}

//Sondar a diagonal superior direita do edazinho
void sondar(edazinhos *playerList){

    //Linha e coluna a serem sondadas
    long long int linhaSondar;
    long long int colunaSondar;

    //Decidir qual posição sondar
    if(playerList->posicoesSondadas == 8){
        printf("Todas as posições em volta deste player foram sondadas.\n");
        //Avançar para o próximo player
        playerList = playerList->prox;
        //Se houver mais players, sondar. Senão, sair
        if(playerList!=NULL){
            sondar(playerList);
        } else {
            return;
        }
    } else if (playerList->posicoesSondadas == 0){
        //Sondar a diagonal direita superior
        linhaSondar = playerList->linha+1;
        colunaSondar = playerList->coluna+1;
    } else if (playerList->posicoesSondadas == 1){
        //Sondar a diagonal esquerda inferior
        linhaSondar = playerList->linha-1;
        colunaSondar = playerList->coluna-1;
    } else if (playerList->posicoesSondadas == 2){
        //Sondar a diagonal direita inferior
        linhaSondar = playerList->linha-1;
        colunaSondar = playerList->coluna+1;
    } else if (playerList->posicoesSondadas == 3){
        //Sondar a diagonal esquerda superior
        linhaSondar = playerList->linha+1;
        colunaSondar = playerList->coluna-1;
    } else if (playerList->posicoesSondadas == 4){
        //Sondar a posicao acima
        linhaSondar = playerList->linha+1;
        colunaSondar = playerList->coluna;
    } else if (playerList->posicoesSondadas == 5){
        //Sondar a posição abaixo
        linhaSondar = playerList->linha-1;
        colunaSondar = playerList->coluna+1;
    } else if (playerList->posicoesSondadas == 6){
        //Sondar a posição da direita
        linhaSondar = playerList->linha;
        colunaSondar = playerList->coluna+1;
    } else if (playerList->posicoesSondadas == 7){
        //Sondar a posição da esquerda
        linhaSondar = playerList->linha;
        colunaSondar = playerList->coluna-1;
    }

    //Impressão do comando
    printf("sondar %lld %lld\n", linhaSondar, colunaSondar);
    
    //Esperar a resposta do árbitro
    long long int l, c, p;
    char sondagem[8];
    scanf("%s %lld %lld %lld", sondagem, &l, &c, &p);

    //Inserir a nova célula na heap
    celula nova = {l,c,p};
    insertHeap(nova);
    playerList->posicoesSondadas++;

    //Chamada recursiva para a função de sondagem
    playerList = playerList->prox;
    if(playerList!=NULL){
        sondar(playerList);
    }
    return;
}

//Implementação do jogador: Reagir às entradas do árbitro
int main(){
    
    //Coloca um valor qualquer na posição 0 da heap
    heap[0].linha = -1;
    heap[0].coluna = -1;
    heap[0].pontos = -1;
    
    //Leitura inicial do jogo
    scanf("%lld %lld %lld %u", &LINHA_INCIAL, &COLUNA_INICIAL, &PONTOS_INCIAL, &TURNOS);

    //Variáveis que armazenam o total de pontos obtidos e de edazinhos em campo
    long long int totalPontos = 0,totalEdazinhos = 0;
    
    //Primeiro edazinho em campo
    struct edazinhos *listaEdazinhos;
    listaEdazinhos = (edazinhos *) malloc(sizeof(edazinhos));
    listaEdazinhos->linha = LINHA_INCIAL;
    listaEdazinhos->coluna = COLUNA_INICIAL;
    listaEdazinhos->posicoesSondadas = 0;
    listaEdazinhos->prox = NULL;
    totalEdazinhos++;
    totalPontos += PONTOS_INCIAL;
    unsigned int i = 0;

    //game loop
    do{
        printf("======Turno %d\n", i);
        
        /*
         *Lógica por turno:
         *
         *1° - Dominar uma posição
         *
         *2° - Sondar as posições baseado em algum algoritimo
         *
         *3° - fimturno
         * */

        if(_sizeHeap > 0){
            printf("pode dominar!\nHeap:\n");
            int i = 1;
            while(i <= _sizeHeap){
                printf("l:%lld, c:%lld, p:%lld\n", heap[i].linha, heap[i].coluna, heap[i].pontos);
                i++;
            }
        }

        //ponteiro auxiliar para a lista de edazinhos e suas posições
        struct edazinhos *aux = listaEdazinhos;
        sondar(aux);

        //Acabando o turno, invoca o comando "fimturno"
        printf("fimturno\n");
        fflush(stdout);
        i++;
    }while(i < TURNOS);

    printf("Total de edazinhos: %lld\n", totalEdazinhos);
    printf("Pontuacao final: %lld\n", totalPontos);
    free(listaEdazinhos);
    return 0;

}