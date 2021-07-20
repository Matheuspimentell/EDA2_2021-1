#include <stdio.h>
#include <stdlib.h>

int main (){
    int x, n = 0;

    while (scanf("%d", &x) != EOF){
        n++;
    }

    printf("%d\n", n);
    
    return 0;
}
