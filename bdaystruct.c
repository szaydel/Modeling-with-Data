#include <math.h>
#include <stdio.h>

typedef struct {
    double one_match;
    double none_match;
} bday_struct;

int main(){
  int ct, upto    = 40;
  bday_struct days[upto+1];
    days[1].none_match   = 1;
    for (ct=2; ct<=upto; ct ++){
        days[ct].one_match   = 1- pow(364/365., ct-1);
        days[ct].none_match    = days[ct-1].none_match * (1 - (ct-1)/365.);
    }
    printf("People\t Matches me\t Any match\n");
    for (ct=2; ct<=upto; ct ++){
        printf("%i\t %.3f\t\t %.3f\n", ct, days[ct].one_match, 1-days[ct].none_match);
    }
    return 0;
}
