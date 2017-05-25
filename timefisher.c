#include <apop.h>
int main(){
    int i, test_ct  = 5e6;
    apop_data *testdata = apop_data_falloc((2,2),
                                30, 86,
                                24, 38);
    for (i = 0; i< test_ct; i++)
        apop_data_free_base(apop_test_fisher_exact(testdata));
}
