#include <apop.h>

int main(){
    apop_db_open("data-climate.db");
  apop_data *d = apop_query_to_data("select "
          " (yearmonth/100. - round(yearmonth/100.))*100 as month,  "
          " avg(tmp), stddev(tmp) "
          " from precip group by month");
    printf("set xrange[0:13]; plot '-' with errorbars\n");
    apop_matrix_show(d->matrix);
}
