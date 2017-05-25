#include "eigenbox.h"

apop_data *query_data(){
    apop_db_open("data-census.db");
    return apop_query_to_data(" select postcode as row_names, "
                        " m_per_100_f, population/1e6 as population, median_age "
                        " from geography, income,demos,postcodes "
                        " where income.sumlevel= '040' "
                        " and geography.geo_id = demos.geo_id  "
                        " and income.geo_name = postcodes.state "
                        " and geography.geo_id = income.geo_id ");
}

void show_projection(gsl_matrix *pc_space, apop_data *data){
    fprintf(stderr,"The eigenvectors:\n");
    apop_matrix_print(pc_space, .output_pipe=stderr);
    apop_data *projected = apop_dot(data, &(apop_data){.matrix=pc_space});
    printf("plot '-' using 2:3:1 with labels\n");
    apop_data_show(projected);
}
