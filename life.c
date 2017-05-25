#include <apop.h>
int area_pop(gsl_matrix *a, int row, int col){
    Apop_submatrix(a, row-1, col-1, 3, 3, neighborhood);
    return apop_matrix_sum(neighborhood);
}

void calc_grid(gsl_matrix* active, gsl_matrix* inactive, int size){
  int i, j, s, live;
    gsl_matrix_set_all(inactive, 0);
    for(i=1; i< size-1; i++)
        for(j=1; j< size-1; j++){
            live    = gsl_matrix_get(active, i, j);
            s       = area_pop(active, i, j) - live;
            if ((live && (s == 2 || s == 3))
                || (!live && s == 3)){
                    gsl_matrix_set(inactive, i, j, 1);
                    printf("%i  %i\n", i, j);
            }
        }
}

int main(){
  int i, gridsize=100, periods = 850;
  gsl_matrix  *t, *active = gsl_matrix_calloc(gridsize,gridsize);
  gsl_matrix  *inactive = gsl_matrix_calloc(gridsize,gridsize);
    gsl_matrix_set(active, 50, 50, 1); gsl_matrix_set(active, 49, 51, 1);
    gsl_matrix_set(active, 49, 50, 1); gsl_matrix_set(active, 51, 50, 1);
    gsl_matrix_set(active, 50, 49, 1);
    printf("set xrange [1:%i]\n set yrange [1:%i]\n", gridsize, gridsize);
    for (i=0; i < periods; i++){
        printf("plot '-' with points pointtype 6\n");
        calc_grid(active, inactive, gridsize);
        t = inactive;
        inactive = active;
        active = t;
        printf("e\n");
    }
}
