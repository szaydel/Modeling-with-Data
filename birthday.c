#include <math.h>
#include <stdio.h>

int main(){
  double    no_match    = 1;
  double    matches_me;
  int       ct;
    printf("People\t Matches me\t Any match\n");
    for (ct=2; ct<=40; ct ++){
        matches_me   = 1- pow(364/365., ct-1);
        no_match    *= (1 - (ct-1)/365.);
        printf("%i\t %.3f\t\t %.3f\n", ct, matches_me, (1-no_match));
    }
    return 0;
}
