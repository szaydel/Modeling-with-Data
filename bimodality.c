#include "oneboot.h"

double  modect_scale,  modect_min, modect_max,
        h_min=25,      h_max=500,  max_k = 20,
        boot_iterations = 1000,
        pauselength = 0.1;
char    outfile[]   = "kernelplot";

void plot(apop_data *d, FILE *f){
    fprintf(f, "plot '-' with lines\n");
    apop_data_print(d, .output_pipe=f); 
    fprintf(f, "e\npause %g\n", pauselength);
}

int countmodes(gsl_vector *data, double h, FILE *plothere){
  int       len     =(modect_max-modect_min)/modect_scale;
  apop_data *ddd    = apop_data_calloc(0, len, 2);
  double    sum, i=modect_min;
    for (size_t j=0; j < ddd->matrix->size1; j ++){
        sum = 0;
        for (size_t k = 0; k< data->size; k++)
            sum += gsl_ran_gaussian_pdf((i-gsl_vector_get(data,k))/h,1)/(data->size*h);
        apop_data_set(ddd, j, 0, i);
        apop_data_set(ddd, j, 1, sum);
        i+=modect_scale;
    }
    int     modect  =0;
    for (i = 1; i< len-1; i++)
        if(apop_data_get(ddd,i,1)>=apop_data_get(ddd,i-1,1) 
            && apop_data_get(ddd,i,1)>apop_data_get(ddd,i+1,1))
                modect++;
    if (plothere) plot(ddd, plothere);
    apop_data_free(ddd);
    return modect;
}

void fill_kmap(gsl_vector *data, FILE *f, double *ktab){
    for (double h = h_max; h> h_min; h*=0.99){
        int val = countmodes(data, h, f);
        if (val <max_k)
            ktab[val - 1] = h;
    }
}

double boot(gsl_vector *data, double h0, int modect_target, gsl_rng *r){
  double    over_ct = 0;
  gsl_vector *boots = gsl_vector_alloc(data->size);
    for (int i=0; i < boot_iterations; i++){
        one_boot(data, r, boots);
        if (countmodes(boots, h0, NULL) > modect_target)
            over_ct++;
    }
    gsl_vector_free(boots);
    return over_ct/boot_iterations;
}

apop_data *produce_p_table(gsl_vector *data, double *ktab, gsl_rng *r){
  apop_data *ptab = apop_data_alloc(0, max_k, 2);
    apop_name_add(ptab->names, "Mode", 'c');
    apop_name_add(ptab->names, "Likelihood of more", 'c');
    for (int i=0; i< max_k; i++){
        apop_data_set(ptab, i, 0, i);
        apop_data_set(ptab, i, 1, boot(data, ktab[i], i, r));
    }
    return ptab;
}

void setvars(gsl_vector *data){	//rescale based on the data.
    double m1 = gsl_vector_max(data);
    double m2 = gsl_vector_min(data);
    modect_scale = (m1-m2)/200;
    modect_min = m2-(m1-m2)/100;
    modect_max = m1+(m1-m2)/100;
}

int main(){
    Apop_col_v(apop_text_to_data("data-tv", 0,0), 0, data);
    setvars(data);
    FILE  *f  = fopen(outfile, "w");
    double  *ktab = calloc(max_k, sizeof(double));
    fill_kmap(data, f, ktab);
    fclose(f);
    gsl_rng *r  = apop_rng_alloc(3);
    apop_data_show(produce_p_table(data, ktab, r));
}
