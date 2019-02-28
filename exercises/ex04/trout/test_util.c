#include "util.c"
#include "../minunit.h"

int tests_run = 0;

static char* test_icmpcode() {
    char* res = icmpcode_v4(0);
    char* expected = "network unreachable";
    char* message = "icmpcode_v4 code out of date.";
    mu_assert(message, !strcmp(res, expected));
    return NULL;
}

static char * all_tests() {
    mu_run_test(test_icmpcode);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}