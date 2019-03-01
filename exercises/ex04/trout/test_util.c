#include "util.c"
#include "../minunit.h"

int tests_run = 0;

static char* test_icmpcode() {
    char* message = "icmpcode_v4 code out of date.";

    mu_assert(message, !strcmp(icmpcode_v4(0), "network unreachable"));
    mu_assert(message, !strcmp(icmpcode_v4(1), "host unreachable"));
    mu_assert(message, !strcmp(icmpcode_v4(2), "protocol unreachable"));
    mu_assert(message, !strcmp(icmpcode_v4(3), "port unreachable"));
    mu_assert(message, !strcmp(icmpcode_v4(4), "fragmentation required but DF bit set"));
    mu_assert(message, !strcmp(icmpcode_v4(5), "source route failed"));
    mu_assert(message, !strcmp(icmpcode_v4(6), "destination network unknown"));
    mu_assert(message, !strcmp(icmpcode_v4(7), "destination host unknown"));
    mu_assert(message, !strcmp(icmpcode_v4(8), "source host isolated (obsolete)"));
    mu_assert(message, !strcmp(icmpcode_v4(9), "destination network administratively prohibited"));
    mu_assert(message, !strcmp(icmpcode_v4(10), "destination host administratively prohibited"));
    mu_assert(message, !strcmp(icmpcode_v4(11), "network unreachable for TOS"));
    mu_assert(message, !strcmp(icmpcode_v4(12), "host unreachable for TOS"));
    mu_assert(message, !strcmp(icmpcode_v4(13), "communication administratively prohibited by filtering"));
    mu_assert(message, !strcmp(icmpcode_v4(14), "host recedence violation"));
    mu_assert(message, !strcmp(icmpcode_v4(15), "precedence cutoff in effect"));
    mu_assert(message, !strcmp(icmpcode_v4(20), "[unknown code]"));
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