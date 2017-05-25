#include <stdio.h>

#define test(in) printf("%s", (#in)[0]=='\0' ? "null\n" : "zero\n");

int main(){
    test( 	 );
    test(0);
    test();
}
