#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand.h"

int main (int argc, char *argv[])
{
    int num_trials = 10000;
    // int num_trials = 5;
    int i;
    double x;

    srandom (time (NULL));

    for (i=0; i<num_trials; i++) {
        x = my_random_double();
        printf ("%.15lf\n", x);
    }

    return 0;
}
