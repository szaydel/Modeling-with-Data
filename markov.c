#include <apop.h>
int main(){
    apop_data *t = apop_text_to_data("data-markov", .has_row_names='n', 
                                    .has_col_names='n', .delimiters=" ");
    apop_data *out  = apop_dot(t, t);
    apop_data_show(out);
}
