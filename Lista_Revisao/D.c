#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    char resposta[3];
    int contagem = 0, triagens = 0, linhas = 0;

    while (scanf("%s", resposta) != EOF){
        linhas++;
        if(strcmp(resposta, "sim") == 0)
            contagem++;
        if(linhas == 10){
            if(contagem >= 2){
                triagens++;
            }
            linhas = 0;
            contagem = 0;
        }
    }

    printf("%d\n", triagens);

    return 0;
}