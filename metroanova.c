#include <apop.h> 

int main(){
    apop_db_open("data-metro.db");
    char joinedtab[] = "(select year, riders, line "
                        "from riders, lines "
                        "where riders.station = lines.station "
                        "and riders is not null)";
    apop_data_show(apop_anova(joinedtab, "riders", "line", "year"));
}
