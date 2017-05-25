#include <apop.h>
#include <sys/stat.h> //chmod

int main(){
    char    filename[]  = "plot_me";
    FILE    *f = fopen(filename, "w");
    fprintf(f, "#!/usr/bin/gnuplot -persist\n\
                plot sin(x)");
    fclose(f);
    chmod(filename, 0755);
}
