#include <math.h>
#include <stdio.h>

int main(){
    printf("Powers of two held in a double:\n");
    for(int i=0; i< 1400; i+=100)
        printf("%i\t %g \t %g\n", i, ldexp(1,i), ldexp(1,-i));
    printf("Powers of two held in a long double:\n");
    for(int i=0; i< 18000; i+=1000)
        printf("%i\t %Lg \t %Lg\n", i, ldexpl(1,i), ldexpl(1,-i));
}
