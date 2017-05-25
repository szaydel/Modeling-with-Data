#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int ct =0, keepgoing = 1;
int *primes   = NULL;

void breakhere(){ keepgoing   = 0; }

int main(){
  int i, testme = 2, isprime;
    signal(SIGINT, breakhere);
    while(keepgoing){
        isprime = 1;
        for (i=0; isprime && i< sqrt(testme) && i<ct; i++)
            isprime = testme % primes[i];
        if (isprime){
            printf("%i  \r", testme); fflush(NULL);
            primes      = realloc(primes, sizeof(int)*(ct+1));
            primes[ct]  = testme;
            ct          ++;
        }
        testme  ++;
    }
    printf("\n");
    for (i=0; i< ct; i++)
      printf("%i\t", primes[i]);
    printf("\n");
}
