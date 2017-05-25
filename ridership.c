#include <apop.h>

void with_means(){
    apop_data *d2 = apop_query_to_data("select avg(riders), year-1977 \
            from riders natural join lines \
            group by lines.line, year");
    apop_model_show(apop_estimate(d2, apop_ols));
}

void by_lines(){
    apop_data *lines = apop_query_to_text("select distinct line from lines");
    int linecount = lines->textsize[0];
    apop_data *parameters = apop_data_alloc(linecount, 2);
    for(int i=0; i < linecount; i ++){
        char *color = lines->text[i][0];
        apop_data *d = apop_query_to_data("select riders, year-1977 "
                "from riders natural join lines "
                "where riders is not null "
                "and lines.line = '%s'", color);
        apop_model *m = apop_estimate(d, apop_ols);
        Apop_row_v(parameters, i, r);
        gsl_vector_memcpy(r, m->parameters->vector);
        apop_name_add(parameters->names, color, 'r');
    }
    apop_data_show(parameters);
    apop_data *s = apop_data_summarize(parameters);
    printf("\n\n");
    apop_data_show(s);
}

int main(){
    apop_db_open("data-metro.db");
    printf("Regression parent, Normal child:\n\n");  with_means();
    printf("\n\nNormal parent, regression child:\n\n");  by_lines();
}
