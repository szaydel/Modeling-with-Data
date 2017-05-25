#include <stdio.h>
#include <string.h> //strlen

int main(){
  float indata;
  char  s[100];
    printf("Give me a number: ");
    scanf("%g", &indata);
    printf("Your number squared: %g\n", indata*indata);
    printf("OK, now give me a string (max length, 100):\n");
    fgets(s, 99, stdin); //eat a newline.
    fgets(s, 99, stdin);
    printf("Here it is backward:\n");
    for (int i=strlen(s)-2; i>=0; i--)
        printf("%c", s[i]);
    printf("\n");
}
