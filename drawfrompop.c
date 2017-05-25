#include <apop.h>

int main(){ 
    apop_db_open("data-wb.db");
    apop_data *pops = apop_query_to_data("select population+0.0 p from pop where p>500");
    apop_data *binned = apop_data_to_bins(apop_data_copy(pops), .close_top_bin='y', .bin_count=50);
    apop_model*m=apop_model_to_pmf(.model=apop_estimate(pops, apop_lognormal), .bin_count=200);
    apop_vector_normalize(binned->weights);
    apop_vector_normalize(m->data->weights);
    apop_data_print(apop_data_sort(binned), .output_name="actual");
    apop_data_print(apop_data_sort(m->data), .output_name="simulated");
    printf("set xrange [0:3e5];# set yrange [0:0.12]; \n \
            plot 'actual' using 1:2 with boxes, 'simulated' using 1:2 with lines\n");
}
