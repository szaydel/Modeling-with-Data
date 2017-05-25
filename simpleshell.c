#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    if (argc==1){
        printf("Give me a command to run.\n");
        return 1;
    }
    int return_value = system(argv[1]);
    printf("The program returned %i.\n", return_value);
    return return_value;
}
