#include <apop.h>

double find_lambda(double half_life){
  double  lambda = -half_life/log(1/2.); 
  return gsl_cdf_exponential_Q(1, lambda);
}

int main(){
    double li = 0, maoi = 0;
    int days = 10;
    gsl_matrix *d = gsl_matrix_alloc(days*24,4);
    double hourly_decay1 = find_lambda(20.); //hours; lithium carbonate
    double hourly_decay2 = find_lambda(11.); //hours; phenelzine
    for (size_t i=0; i < days*24; i ++){
      li    *= hourly_decay1;
      maoi  *= hourly_decay2;
      if (i % 24 == 0)
          li+= 600;
      if ((i+12) % 24 == 0)
          maoi+= 45;
      Apop_matrix_row(d, i, onehour);
      apop_vector_fill(onehour, i/24., li/10., maoi, maoi/li*100.);
    }
    printf("plot 'maoi.out' using 1:2 with lines title 'Li/10', \
                'maoi.out' using 1:3 with lines title 'MAOI', \
                'maoi.out' using 1:4 with lines title 'MAOI/Li, pct\n");
    remove("maoi.out");
    apop_matrix_print(d, "maoi.out");
}
