#include <apop.h>

int main(){
    apop_db_open("data-census.db");
    gsl_vector *n = apop_query_to_vector("select in_per_capita from income "
            "where state= (select state from geography where name ='North Dakota')");
    gsl_vector *s = apop_query_to_vector("select in_per_capita from income "
            "where state= (select state from geography where name ='South Dakota')");
    apop_data *t = apop_t_test(n,s);
    apop_data_show(t);  //show the whole output set...
    printf ("\n confidence: %g\n", apop_data_get(t, .rowname="confidence, 2 tail")); //...or just one value.
}
