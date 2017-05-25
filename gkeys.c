#include <glib.h>
#include <apop.h>

int main(){
    GKeyFile  *keys   = g_key_file_new();
    GError    *e      = NULL;
    char      *config = "chi squared configuration";
//  char      *config = "exponential configuration";
    double   (*distribution)(double, double) = NULL;
    if (!g_key_file_load_from_file(keys, "glib.config", 0, &e))
        fprintf(stderr, "%s", e->message);
    double    param = g_key_file_get_double(keys, config, "parameter", &e);
    if (e) fprintf(stderr, "%s", e->message);
    char*  name = g_key_file_get_string(keys, config, "distribution name", &e);
    if (e) fprintf(stderr, "%s", e->message);

    if (!strcmp(name, "Chi squared"))
        distribution = gsl_cdf_chisq_Pinv;
    else if (!strcmp(name, "Exponential"))
        distribution = gsl_cdf_exponential_Pinv;

    printf("Mean of a %s distribution with parameter %g: %g\n", name,
            param, distribution(0.5, param));
}
