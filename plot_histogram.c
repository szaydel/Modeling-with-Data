/* The apop_plot_histogram function used to be a part of Apophenia, but all
 Gnuplot-specific parts were removed in version 0.999c. This slightly simplified
 version is sufficient to run all examples. Note that it is largely just a wrapper
 for apop_data_to_bins. */


/* This convenience function will take in a \c gsl_vector of data and put out a histogram, ready to pipe to Gnuplot.

\param data A \c gsl_vector holding the data. Do not pre-sort or bin; this function does that for you via apop_data_to_bins.
\param bin_count   The number of bins in the output histogram (if you send zero, I set this to \f$\sqrt(N)\f$, where \f$N\f$ is the length of the vector.)
\param with The method for Gnuplot's plotting routine. Default is \c "boxes", so the gnuplot call will read <tt>plot '-' with boxes</tt>. The \c "lines" option is also popular, and you can add extra terms if desired, like <tt> "boxes linetype 3"</tt>.
*/
void plot_histogram(gsl_vector *data, FILE *f, size_t bin_count, char *with){
    Apop_stopif(!data, return, 0, "Input vector is NULL.");
    if (!with) with="impulses";
    apop_data vector_as_data = (apop_data){.vector=data};
    apop_data *histodata = apop_data_to_bins(&vector_as_data, .bin_count=bin_count, .close_top_bin='y');
    apop_data_sort(histodata);
    apop_data_free(histodata->more); //the binspec.

    fprintf(f, "set key off ;\n"
               "plot '-' with %s\n", with);
    apop_data_print(histodata, .output_pipe=f);
    fprintf(f, "e\n");

    fflush(f);
    apop_data_free(histodata);
}
