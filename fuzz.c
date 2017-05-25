#include <stdio.h>

int main(){
  double t = 1.2;
    t -= 0.4;
    t -= 0.4;
    t -= 0.4;
    if (t<0)
        printf ("By the IEEE floating-point standard, 1.2 - 3*0.4 < 0.\n");
}
