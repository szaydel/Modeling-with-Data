#include <math.h>
#include <stdio.h>

typedef struct {
    double one_match;
    double none_match;
} bday_struct;

int upto    = 40;
void calculate_days(bday_struct days[]);
void print_days(bday_struct days[]);

int main(){
    bday_struct days[upto+1];
    calculate_days(days);
    print_days(days);
    return 0;
}

void calculate_days(bday_struct days[]){
  int       ct;
    days[1].none_match   = 1;
    for (ct=2; ct<=upto; ct ++){
        days[ct].one_match   = 1- pow(364/365., ct-1);
        days[ct].none_match    = days[ct-1].none_match * (1 - (ct-1)/365.);
    }
}

void print_days(bday_struct days[]){
  int       ct;
    printf("People\t Matches me\t Any match\n");
    for (ct=2; ct<=upto; ct ++){
        printf("%i\t %.3f\t\t %.3f\n", ct, days[ct].one_match, 1-days[ct].none_match);
    }
}
