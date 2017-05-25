#include <math.h>   //NaN handlers
#include <stdio.h>  //printf

int main(){
  double missing_data = NAN;
  double big_number = INFINITY;
  double negative_big_number = -INFINITY;
    if (isnan(missing_data))
        printf("missing_data is missing a data point.\n");
    if (isfinite(big_number)== 0)
        printf("big_number is not finite.\n");
    if (isfinite(missing_data)== 0)
        printf("missing_data isn't finite either.\n");
    if (isinf(negative_big_number)== -1)
        printf("negative_big_number is negative infinity.\n");
}
