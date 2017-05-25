#include <stdlib.h>
#include <stdio.h>

int main(){
  int array_length=1000;
  int *squares = malloc (array_length * sizeof(int));
    for (int i=0; i < array_length; i++)
          squares[i] = i * i;
}
