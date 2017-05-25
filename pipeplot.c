#include <apop.h>

void plot_matrix_now(gsl_matrix *data){
  static FILE *gp = NULL;
    if (!gp)
        gp = popen("gnuplot -persist", "w");
    if (!gp){
        printf("Couldn't open Gnuplot.\n");
        return;
    }
    fprintf(gp,"reset; plot '-' \n");
    apop_matrix_print(data, .output_pipe=gp);
    fflush(gp);
}

int main(){
    apop_db_open("data-climate.db");
    plot_matrix_now(apop_query_to_data("select (year*12+month)/12., temp from temp")->matrix);
}
