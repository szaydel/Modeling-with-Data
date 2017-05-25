#include <apop.h>

double calc_taxes(double income){
  double cutoffs[] = {0, 11200, 42650, 110100, 178350, 349700, INFINITY};
  double rates[]   = {0, 0.10, .15, .25, .28, .33, .35};
  double tax       = 0;
  int    bracket   = 1;
    income -= 7850;   //Head of household standard deduction
    income -= 3400*3; //exemption: self plus two dependents.
    while (income > 0){
        tax     += rates[bracket] * GSL_MIN(income, cutoffs[bracket]-cutoffs[bracket-1]);
        income  -= cutoffs[bracket];
        bracket ++;
    }
    return tax;
}

int main(){
    apop_db_open("data-census.db");
    apop_opts.db_name_column = "geo_name";
    apop_data *d = apop_query_to_data("select geo_name, Household_median_in as income\
                        from income where sumlevel = '040'\
                        order by household_median_in desc");
    Apop_col_tv(d, "income", income_vector);
    d->vector = apop_vector_map(income_vector, calc_taxes);
    apop_name_add(d->names, "tax owed", 'v');
    apop_data_show(d);
}
