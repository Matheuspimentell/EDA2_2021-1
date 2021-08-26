#include <stdio.h>
#include <stdlib.h>
//Struct definindo os dados recebidos
typedef struct No{
    char letra;
    int indice;
} No; No NULLitem = {' ', -1};

//M é o tamanho da tabela hash, N é o número de elementos dentro da tabela hash
static int M, N;
static No *hashTable;
//Como N não é primo, esotu usando o número sugerido pelo prof
#define getHashKey(index)(((unsigned)index)%M)
//Definindo uma macro para referência do valor do índice de cada letra
#define index(x)(x.indice)
//Definindo macro para achar itens nulos
#define isNull(A)(index(hashTable[A]) == index(NULLitem))

void InitHashTable(int max){
    N = 0;
    M = max;
    hashTable = malloc(M*sizeof(No));
    for(int i = 0; i < M; i++){
        hashTable[i] = NULLitem;
    }
}

void HashTableInsert(No caracter){
    int v = index(caracter);
    int i = getHashKey(v);
    if  (hashTable[i].letra != caracter.letra){
        hashTable[i] = caracter;
        N++;
    } else {
        return;
    }
}

int main(){
    InitHashTable(1048583);
    No item;
    int menor, j;
    while (scanf("%d %c", &item.indice, &item.letra)!=EOF){
        if(N==0){
            menor = item.indice;
        } else {
            if(item.indice < menor){
                menor = item.indice;
            }
        }
        HashTableInsert(item);
    }
    for(int i = menor; i < menor+N ; i++){
        j = getHashKey(i);
        printf("%c", hashTable[j].letra);
    }
    printf("\n");
    return 0;
}