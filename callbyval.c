#include <stdio.h>  //printf
double globe=1;          //a global variable.

double factorial (int a_c){
    while (a_c){
        globe   *= a_c;
        a_c --;
    }
     return globe;
}

int main(void){
    int a = 10;
    printf("%i factorial is %f.\n", a, factorial(a));
    printf("a= %i\n", a);
    printf("globe= %f\n", globe);
    return 0;
}
