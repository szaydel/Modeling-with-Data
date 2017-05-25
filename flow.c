#include <stdio.h>
int main(){
    int i = 0;
    while (i < 5){
        printf("Hello.\n");
        i ++;
    }

    for (i=0; i < 5; i++){
        printf("Hi.\n");
    }

    i = 0;
    do {
        printf("Hello.\n");
        i ++;
    } while (i < 5);

    return 0;
}
