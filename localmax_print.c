#include "sinsq.c"

void do_search(char *methodstring, char *name, char *trace){
    apop_data *path;
    Apop_model_add_group(sin_sq_model, apop_mle,
            .starting_pt= (double[]){0},
            .method= methodstring, .tolerance= 1e-4,
            .mu_t= 1.25, .path=&path);
    apop_model *out = apop_estimate(NULL, sin_sq_model);
    double result = gsl_vector_get(out->parameters->vector, 0);
    printf("The %s algorithm found %g.\n", name, result);
    Apop_settings_rm_group(sin_sq_model, apop_mle);
    char *outf;
    asprintf(&outf, "localmax_out/%s.gplot", trace);
    apop_data_print(path, .output_name=outf);
}

int main(){
    Apop_settings_add_group(sin_sq_model, apop_parts_wanted);
    system ("mkdir -p localmax_out; rm -f localmax_out/*.gplot");
    apop_opts.verbose ++;
    do_search("NM simplex", "N-M Simplex", "simplex");
    do_search("FR CG", "F-R Conjugate gradient", "fr");
    do_search("Annealing", "Simulated annealing", "siman");
    do_search("Newton", "Root-finding", "root");
    fflush(NULL);
    system("sed -i \"1iplot '-'\" localmax_out/*.gplot");
}
