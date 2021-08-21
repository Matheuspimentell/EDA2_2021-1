#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (){
    int numeroLinhas, numeroAlunos = 0;
    scanf("%d", &numeroLinhas);
    int listaPresenca[numeroLinhas];
    for (int i = 0; i < numeroLinhas; i++){
        scanf("%d", &listaPresenca[i]);
    }
    //v[9] = {1, 2, 3, 4, 1, 3, 6, 7, 1}
    for (int j = 0; j < numeroLinhas; j++){
        for(int k = j-1; k >= 0; k--){
            if (listaPresenca[j] == listaPresenca[k]){
                numeroAlunos--;
            }
        }
        numeroAlunos++;
    }
    printf("%d\n", numeroAlunos);
}