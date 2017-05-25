#include <apop.h>

typedef double (*dfn) (double);

double sample_function (double in){
    return log(in)+ sin(in);
}

void plot_a_fn(double min, double max, dfn plotme){
  double    val;
  FILE      *f = popen("gnuplot -persist", "w");
    if (!f)
        printf("Couldn't find Gnuplot.\n");
    fprintf(f, "set key off\n plot '-' with lines\n");
    for (double i=min; i<max; i+= (max-min)/100.0){
        val = plotme(i);
        fprintf(f, "%g\t%g\n", i, val);
    }
    fprintf(f, "e\n");
}

int main(){
    plot_a_fn(0, 15, sample_function);
}
