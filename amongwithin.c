#include <apop.h> 

void variance_breakdown(char *table, char *data, char *grouping){
    apop_data* aggregates = apop_query_to_mixed_data("mmw", 
               "select var_pop(%s) var, avg(%s) avg, count(*) from %s group by %s",
               data, data, table, grouping);
    Apop_col_tv(aggregates, "var", vars);
    Apop_col_tv(aggregates, "avg", means);
    double total= apop_query_to_float("select var_pop(%s) from %s", data, table);
    double mean_of_vars = apop_vector_mean(vars, aggregates->weights);
    double var_of_means = apop_vector_var(means, aggregates->weights);
    printf("total variance: %g\n", total);
    printf("within group variance: %g\n", mean_of_vars);
    printf("among  group variance: %g\n", var_of_means);
    printf("sum within+among: %g\n", mean_of_vars + var_of_means);
}

int main(){
    apop_db_open("data-metro.db");
    char joinedtab[] = "(select riders/100 as riders, line from riders, lines "
                " where lines.station = riders.station "
                " and riders is not null)";
    variance_breakdown(joinedtab, "riders", "line");
}
