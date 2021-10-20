// O objetivo do jogo é crescer o máximo possível adiquirindo a maior quantidade de pontos.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Variáveis fixadas no início do jogo
long long int LINHA_INCIAL, COLUNA_INICIAL, PONTOS_INCIAL; //long long int suporta dados entre -2^63 e 2^63 - 1
unsigned int TURNOS; // unsigned int para armazenar dado da quantidade de turnos: TURNOS varia de 10 à 2^31
//Variáveis que armazenam o total de pontos obtidos e de edazinhos em campo
long long int totalPontos, totalEdazinhos;

//Lista duplamente encadeada com todos os edazinhos
typedef struct edazinhos{
    long long int linha, coluna; //Linha e coluna do edazinho atual
    int posicoesSondadas; // Varia entre 0 e 8. 8 = Todas as posições em volta foram sondadas | 0 = nenhuma posição foi sondada
    struct edazinhos *prox, *ant; //Ponteiro para o próximo edazinho
}edazinhos;

/*
 * Testar uma implementação de "balcklist" de posições
 * Cada posição que for sondada com sucesso deve ser adicionada à blacklist
 * Caso um edazinho encontre uma posição da blacklist, ele passa o turno
 * Caso não encontre, sonda normalmente
 * A "blacklist" pode ser implementada por meio de uma tabela hash
 **/

//Cada célula da blacklist
typedef struct Blacklist{
    long long int linha, coluna; //linha e coluna a serem armazenadas na "lista negra"
    struct Blacklist *prox; //ponteiro para o próximo elemento, em caso de colisão
}Blacklist;

//"lista negra" de posições (Tabela Hash)
Blacklist *blacklist[524287];

//Para obter a hash key
#define getHashKey(x, y) \
    ((abs(x+y))%524287);

//Caso a posição já tenha sido sondada, retorna 1. Caso contrário retorna 0
int confereBlacklist(long long int linha, long long int coluna){
    int key = getHashKey(linha, coluna);
    
    //Se não tiver item na blacklist na posição key
    if(blacklist[key] == NULL){
        blacklist[key] = (Blacklist *) malloc(sizeof(Blacklist));
        blacklist[key]->linha = linha;
        blacklist[key]->coluna = coluna;
        blacklist[key]->prox = NULL;
        return 0;
    //Caso tenha item na blacklist, conferir
    } else if (blacklist[key] != NULL){
        //Caso seja o item
        if(blacklist[key]->linha == linha && blacklist[key]->coluna == coluna){
            return 1;
        //Caso não seja o item
        } else {
            Blacklist *aux = blacklist[key];
            //Passar por toda a lista de colisões
            while(aux->prox!=NULL){
                if(aux->linha == linha && aux->coluna == coluna){
                    return 1;
                }
                aux = aux->prox;
            }
            //Caso no último elemento
            if(aux->prox==NULL){
                //Verificar se é o item
                if(aux->linha == linha && aux->coluna == coluna){
                    return 1;
                }
                //Adicionar um novo item
                Blacklist *novo;
                novo = (Blacklist *) malloc(sizeof(Blacklist));
                novo->linha = linha;
                novo->coluna = coluna;
                novo->prox = NULL;
                aux->prox = novo;
                return 0;
            }
        }
    }
}

//Cada célula do jogo
typedef struct celula{
    long long int linha, coluna, pontos;
}celula;

/*
 * A implementação de uma Heap é feita por meio de vetores. Onde não se usa o índice 0 do vetor.
 * A posição dos filhos de um nó da HEAP é dada por: 2*k e 2*k+1, respectivamente. Onde k é a posição do nó pai
 * Igualmente, pode-se encontrar a posição do nó pai com o resultado inteiro de k/2. Onde k é a posição do nó filho
 * A inserção deve começar pelo índice 1
 * Usar a implementação de uma MAXHeap
 * Utilizando o índice 0 para a última posição removida
 * */

//Heap e seu tamanho
celula heap[301];
int _sizeHeap = 0;

//Funções essenciais da Heap
#define Pai(i) (i/2);
#define FilhoEsquerda(i) (i*2);
#define FilhoDireita(i) ((i*2)+1);

//Troca simples entre 2 elementos da heap
void HeapSwap(int indexA, int indexB){
    celula aux;
    aux = heap[indexA];
    heap[indexA] = heap[indexB];
    heap[indexB] = aux;
}

//Reorganiza a Heap "para baixo"
void heapifyDown(int index){

    //Filho da direita e da esquerda do nó "i"
    int Esquerda = FilhoEsquerda(index);
    int Direita = FilhoDireita(index);

    //Assumindo que o index seja o maior elemento
    int i = index;

    //Caso não seja fora do tamanho da heap e o filho da esquerda seja maior que o index
    if(Esquerda < _sizeHeap && heap[Esquerda].pontos > heap[index].pontos){
        i = Esquerda;
    }
    //Caso não seja fora do tamanho da heap e o filho da direita seja maior que o index
    if(Direita < _sizeHeap && heap[Direita].pontos > heap[i].pontos){
        i = Direita;
    }
    //Caso exista algum numero maior que o index, trocar o maior deles de posição com o index
    if(i != index){
        HeapSwap(index, i);
        heapifyDown(i);
    }
}

//Reorganiza a Heap "para cima"
void heapifyUp(int index){

    //Pai do nó "i"
    int pai = Pai(index);

    //Caso não seja fora do tamanho da heap e o pai seja menor que o index
    if(pai >= 1 && heap[pai].pontos < heap[index].pontos){
        HeapSwap(pai, index);
        heapifyUp(pai);
    }
}

//Inserção de um elemento na heap
void insertHeap(celula nova){

    if(_sizeHeap == 300){
        printf("Overflow! nao foi possivel inserir na heap");
        return;
    }

    //Incrementa o tamanho da heap e insere a nova celula na primeira posição disponível
    _sizeHeap++;
    int i = _sizeHeap;
    heap[i] = nova;

    heapifyUp(i);
}

//Remover o maior elemento
celula removeMAX(){
    
    //Célula que irá conter o maior elemento da heap
    celula max;
    max = heap[1];
    
    //Pegar o último item da heap e colocar no início dela
    if(_sizeHeap > 1){
        int i = _sizeHeap;
        HeapSwap(1, i);
    }
    _sizeHeap--;

    //Reorganizar a heap
    heapifyDown(1);

    return max;
}

//Sondar a diagonal superior direita do edazinho
void sondar(edazinhos *playerList){

    //Caso o player atual seja nulo
    if(playerList == NULL){
        return;
    }

    //Linha e coluna a serem sondadas
    long long int linhaSondar;
    long long int colunaSondar;
    int sondado = 1;

    //Decidir qual posição sondar
    if(playerList->posicoesSondadas == 8){
        // !!Implementar a retirada do player, caso todas as posições em volta dele forem sondadas!! (Para economia de memória)
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

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    } else if (playerList->posicoesSondadas == 1){
        //Sondar a diagonal esquerda inferior
        linhaSondar = playerList->linha-1;
        colunaSondar = playerList->coluna-1;

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    } else if (playerList->posicoesSondadas == 2){
        //Sondar a diagonal direita inferior
        linhaSondar = playerList->linha-1;
        colunaSondar = playerList->coluna+1;

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    } else if (playerList->posicoesSondadas == 3){
        //Sondar a diagonal esquerda superior
        linhaSondar = playerList->linha+1;
        colunaSondar = playerList->coluna-1;

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    } else if (playerList->posicoesSondadas == 4){
        //Sondar a posicao acima
        linhaSondar = playerList->linha+1;
        colunaSondar = playerList->coluna;

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    } else if (playerList->posicoesSondadas == 5){
        //Sondar a posição abaixo
        linhaSondar = playerList->linha-1;
        colunaSondar = playerList->coluna+1;

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    } else if (playerList->posicoesSondadas == 6){
        //Sondar a posição da direita
        linhaSondar = playerList->linha;
        colunaSondar = playerList->coluna+1;

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    } else if (playerList->posicoesSondadas == 7){
        //Sondar a posição da esquerda
        linhaSondar = playerList->linha;
        colunaSondar = playerList->coluna-1;

        //Conferir na blacklist se a posição já foi sondada
        sondado = confereBlacklist(linhaSondar, colunaSondar);
    }

    //Só sonda se disponível para a sondagem
    if(sondado == 0){
        //Impressão do comando
        printf("sondar %lld %lld\n", linhaSondar, colunaSondar);
    
        //Esperar a resposta do árbitro
        long long int l, c, p;
        char sondagem[8];
        scanf("%s %lld %lld %lld", sondagem, &l, &c, &p);

        //Inserir a nova célula na heap
        celula nova = {l,c,p};
        insertHeap(nova);
    }

    //Avisa que já foi sondado
    playerList->posicoesSondadas++;
    //Chamada recursiva para a função de sondagem
    playerList = playerList->prox;
    if(playerList!=NULL){
        sondar(playerList);
    }
    return;
}

edazinhos *dominar(edazinhos *playerList){
    
    //Remover o maior elemento da lista
    celula aDominar = removeMAX();

    //Imprime o comando
    printf("dominar %lld %lld\n", aDominar.linha, aDominar.coluna);
    
    char dominacao[10];
    long long int pontuacao;

    //Espera a saida do arbitro
    scanf("%s %lld", dominacao, &pontuacao);

    //Criar o novo edazinho
    struct edazinhos *novo;
    novo = (edazinhos *) malloc(sizeof(edazinhos));
    novo->linha = aDominar.linha;
    novo->coluna = aDominar.coluna;
    novo->posicoesSondadas = 0;
    novo->prox = NULL;
    novo->ant = NULL;
    totalEdazinhos++;
    totalPontos+=pontuacao;

    //Retorna o novo edazinho
    return novo;
}

//Implementação do jogador: Reagir às entradas do árbitro
int main(){
    
    //Inicializa as variáveis de pontos e quantidade de edazinhos
    totalPontos = 0;
    totalEdazinhos = 0;

    //Coloca um valor qualquer na posição 0 da heap
    heap[0].linha = -1;
    heap[0].coluna = -1;
    heap[0].pontos = -1;
    
    //Leitura inicial do jogo
    scanf("%lld %lld %lld %u", &LINHA_INCIAL, &COLUNA_INICIAL, &PONTOS_INCIAL, &TURNOS);
    
    //Coloca a posição inicial na blacklist de sondagens
    int keyInicial = getHashKey(LINHA_INCIAL,COLUNA_INICIAL);
    blacklist[keyInicial] = (Blacklist *) malloc(sizeof(Blacklist));
    blacklist[keyInicial]->linha = LINHA_INCIAL;
    blacklist[keyInicial]->coluna = COLUNA_INICIAL;
    blacklist[keyInicial]->prox = NULL;


    //Primeiro edazinho em campo
    struct edazinhos *listaEdazinhos;
    listaEdazinhos = (edazinhos *) malloc(sizeof(edazinhos));
    listaEdazinhos->linha = LINHA_INCIAL;
    listaEdazinhos->coluna = COLUNA_INICIAL;
    listaEdazinhos->posicoesSondadas = 0;
    listaEdazinhos->prox = NULL;
    listaEdazinhos->ant = NULL;
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

        //ponteiro auxiliar para a lista de edazinhos e suas posições
        struct edazinhos *aux = listaEdazinhos;
        struct edazinhos *novo = NULL;

        //Caso existam elementos na heap
        if(_sizeHeap > 0){
            novo = dominar(aux);
        }

        //Sondar
        sondar(aux);

        //Acabando o turno, invoca o comando "fimturno"
        printf("fimturno\n");
        fflush(stdout);

        //Se houver edazinho novo, adiciona à lista (Só adicionando ao final do turno)
        if(novo != NULL){
            aux = listaEdazinhos;
            while(aux->prox!=NULL){
                aux=aux->prox;
            }
            aux->prox = novo;
            novo->ant = aux;
        }

        //Incrementa o turno
        i++;
    }while(i < TURNOS);

    printf("Total de edazinhos: %lld\n", totalEdazinhos);
    printf("Pontuacao final: %lld\n", totalPontos);
    free(listaEdazinhos);
    return 0;

}