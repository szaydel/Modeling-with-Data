#include <apop.h>

apop_model * logit(char *querytail){
    apop_data *d = apop_query_to_mixed_data("mmmmmt", "select 1, age, gender, \
            illegal_immigrants, aid_to_blacks,  %s", querytail);
    apop_data_to_factors(d);
    apop_model *m = apop_estimate(d, apop_logit);
    apop_data *ev = apop_predict(d, m);
    apop_data_show(apop_data_summarize(ev));
    return m;
}

int main(){
    apop_db_open("data-nes.db");
    logit("favorite from choices");
    logit("favorite from choices c, party p where p.person = c.favorite and p.party = 'R'");
    logit("favorite from choices c, party p where p.person = c.favorite and p.party = 'D'");
    logit("p.party from choices c, party p where p.person = c.favorite");
}
