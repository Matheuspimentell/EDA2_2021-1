#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (){
    char num;
    int n;
    scanf("%d", &n);
    int somas[n];
    for (int i = 0; i < n; i++){
        scanf("%c" ,&num);
        printf("%c\n", num);
    }
    // for(int j = 0; j < n; j++){
    //     printf("%d\n", somas[j]);
    // }
    return 0;
}