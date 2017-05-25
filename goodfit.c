#include <apop.h>

int main(){
    apop_db_open("data-climate.db");
    apop_data *precip = apop_query_to_data("select PCP from precip");
    apop_model *est = apop_estimate(precip, apop_normal);
    apop_data *precip_binned = apop_data_to_bins(precip/*, .bin_count=180*/);
    apop_model *datahist = apop_estimate(precip_binned, apop_pmf);
    apop_model *modelhist = apop_model_to_pmf(.model=est, .binspec=apop_data_get_page(precip_binned, "<binspec>"), .draws=1e5);
    double scaling = apop_sum(datahist->data->weights)/apop_sum(modelhist->data->weights);
    gsl_vector_scale(modelhist->data->weights, scaling);
    apop_data_show(apop_histograms_test_goodness_of_fit(datahist, modelhist));
}
