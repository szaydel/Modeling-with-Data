#include <stdio.h>  //printf
#include <stdlib.h> //malloc

int globe=1;          //a global variable.

int factorial (int *a_c){
    while (*a_c){
        globe   *= *a_c;
        (*a_c) --;
    }
     return globe;
}

int main(void){
  int *a  = malloc(sizeof(int));
    *a      = 10;
    printf("%i factorial ...", *a);
    printf(" is %i.\n", factorial(a));
    printf("*a= %i\n", *a);
    printf("globe= %i\n", globe);
    free(a);
    return 0;
}
