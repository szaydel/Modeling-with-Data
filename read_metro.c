//This script produces data-metro.db from the raw text files. The first
//half reads text; the second half converts the crosstab-style data into
//something more database appropriate.

#include <apop.h>
int main(){
    int out = system("sed -e  \"s/'//g\" < metro_ridership.csv | apop_text_to_db -O '-' rawriders data-metro.db");
    out += system("sed \"s/'//g\" < metro-lines.csv | apop_text_to_db -O '-' lines data-metro.db");
    if (out) {printf("Glitch reading in data.\n"); return 1;}

    apop_db_open("data-metro.db");
    apop_opts.db_name_column = "year";
    apop_data *stations = apop_query_to_data("select * from rawriders");
    apop_table_exists("riders", 'd');
    apop_crosstab_to_db(stations, "riders", "year", "station", "riders");
    apop_query("drop table rawriders");
}
