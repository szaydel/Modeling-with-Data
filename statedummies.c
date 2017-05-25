#include <apop.h>

char *build_a_query(){
  char *q = NULL;
    apop_data *state = apop_query_to_text("select Name as state, State as id \
                from geography where sumlevel+0.0 = 40");
    asprintf(&q, "select in_per_capita as income, ");
    for (int i=1; i< state->textsize[0]; i++)
       asprintf(&q, "%s (case state when '%s' then 1 else 0 end) '%s' %c \n", 
                    q, state->text[i][1], state->text[i][0],
                    (i< state->textsize[0]-1) ? ',':' ');
    asprintf(&q,"%s from income\n", q);
    return q;
}

int main(){
    apop_db_open("data-census.db");
    apop_data *d = apop_query_to_data("%s", build_a_query());
    apop_model *e = apop_estimate(d, apop_ols);
    apop_data_rm_page(e->parameters, "<covariance>"); //don't show it.
    apop_model_show(e);
}
