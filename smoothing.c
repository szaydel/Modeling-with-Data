/* Apophenia now has the apop_pmf, which is preferable over the Histogram 
   in a few ways, and so this script has been entirely rewritten. */

#include <apop.h> 

void plot(apop_model *k, char *outname){
    double max = 4.3, increment = 0.01;
    apop_data *out = apop_data_alloc(max/increment+1);
    out->weights =  gsl_vector_alloc(max/increment+1);
    for (int c=0; c<max/increment; c++){
        Apop_row(out, c, a_point);
        gsl_vector_set(a_point->vector, 0, c* increment);
        gsl_vector_set(a_point->weights, 0, apop_p(a_point, k));
    }
    apop_vector_normalize(out->weights); //Q: why is this always necessary?
    apop_data_print(out, .output_name=outname);
}

int main(){
    apop_db_open("data-climate.db");

    apop_data *data = apop_query_to_data("select pcp from precip");
    apop_data_pmf_compress(data); //creates a weights vector
    apop_vector_normalize(data->weights);
    apop_data_sort(data);
    apop_model *pmf = apop_estimate(data, apop_pmf);
    FILE *outfile = fopen("out.h", "w");
    apop_model_print(pmf, outfile);
    apop_model *kernel = apop_model_set_parameters(apop_normal, 0., 0.1);
    apop_model *k = apop_model_copy(apop_kernel_density);
    Apop_settings_add_group(k, apop_kernel_density, .base_pmf=pmf, .kernel=kernel);
    plot(k, "out.k");
    printf("plot 'out.h' with lines title 'data', 'out.k' with lines title 'smoothed'\n");
}
