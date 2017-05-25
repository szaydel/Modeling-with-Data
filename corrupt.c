#include <apop.h>

int main(){
    apop_db_open("data-corruption.db");
    apop_data *corrupt = apop_db_to_crosstab("cpi", "country", "year", "score");
    apop_data *clean   = apop_data_listwise_delete(corrupt);
    apop_model *mlv = apop_estimate(clean, apop_multivariate_normal);
    apop_ml_imputation(corrupt, mlv);
    apop_crosstab_to_db(corrupt, "cpi_clean", "country", "year", "score");
}
