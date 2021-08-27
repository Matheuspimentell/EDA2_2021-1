#include <stdio.h>
#include <stdlib.h>

//Definir um vetor de 100 elementos com todos os elementos iguais a nulo
static int *placas, M = 100, N;
void InitVetPlacas(){
    N = 0;
    placas = malloc(M*sizeof(int));
    /*Preencher todos os elementos com 10⁷ + 1, porque assim, garantimos que nenhum elemento
     novo estará à direita*/
    for (int i = 0; i < M; i++){
        placas[i] = 100000001;
    }
}
//Adicionar sempre o valor ao final do elemento e ordenar após a inserção

//Macro de troca de itens inteiros.
#define troca(a, b) {int t = a; a = b; b = t;}
//Macro para saber se c é menor que d.
#define menor(c, d) (c < d)

//Implementação do ShellSort
static void insertionsortH(int *v, int l, int r, int h){
    for(int i=l+h;i<=r;i++){
    int j = i; 
    int tmp = v[j];
    while(j >= l+h && menor(tmp, v[j-h])){
        v[j] = v[j-h];
        j -= h;
    }
    v[j] = tmp;
  }
}

void shellsort(int *v, int l, int r){
    int h;
    int t = (r-l)+1;
    for(h = 1; h <= (t-1)/9; h = 3*h+1);
    for( ; h > 0; h /= 3){
        insertionsortH(v, 0, t-1, h);
    }
}

void insere(int placa){
    if(placa < placas[M-1]){
        placas[M-1] = placa;
        N++;
        shellsort(placas, 0, 99);
    }
}

int main (){
    InitVetPlacas();
    int opcao, num;
    while(scanf("%d %d", &opcao, &num) != EOF ){
        if(opcao == 1){
            insere(num);
        } else if(opcao == 2){
            if(num > N){
                num = N;
            }
            for(int i = 0; i < num; i++){
                if(i == num-1){
                    printf("%d\n", placas[i]);
                } else {
                    printf("%d ", placas[i]);
                }
            }
        }
    }
    return 0;
}