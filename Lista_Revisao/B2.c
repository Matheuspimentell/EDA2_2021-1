#include <stdio.h>
#include <stdlib.h>

int main (){
    int soma = 0, x = 0, n = 0;

    scanf("%d", &n);

    while( n!=0 ){
        scanf("%d", &x);
        soma = soma + x;
        n--;
    }

    printf("%d\n", soma);
    
    return 0;
}