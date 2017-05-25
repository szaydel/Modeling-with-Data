#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void add_a_prime(int addme, int *ct, int **primes){
    *primes      = realloc(*primes, sizeof(int)*(*ct+1));
    (*primes)[*ct]  = addme;
    (*ct)++;
}

int main(){
  int ct =0, i, j, testme = 2, isprime, max = 1000;
  int *primes   = NULL;
    for (j=0; j< max; j++){
        isprime = 1;
        for (i=0; isprime && i< sqrt(testme) && i<ct; i++)
            isprime = testme % primes[i];
        if (isprime)
            add_a_prime(testme, &ct, &primes);
        testme  ++;
    }
    for (i=0;i< ct; i++)
      printf("%i\t", primes[i]);
    printf("\n");
}
