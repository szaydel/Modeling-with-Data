#include <stdlib.h>

int main(){
    int out =0;
    for (int i=0; i< 12; i++){
        out += system("fortune");
        out += system("echo");
        out += system("sleep 6");
    }
    return out;
}
