#include "../calc.h"
#include <check.h>

START_TEST(calc_test) {
    char *og = "sin(3.1415)+80-90+cos(3.1415)^2*((2/2)mod(2))+ln(1)+log(1)
                +asin(0)+acos(1)+atan(0)+tan(0)+sqrt(4)=";
    int errCode = 0;
    stack_n N;
    N.count = 0;
    stack_s S;
    S.count = 0;
    double result = 0;
    
    errCode = stacker(og, &N, &S, 0.0, &result);
    ck_assert_double_eq_tol(result, -8, 1e-3);
}

int main(void) {
    Suite *smc = suite_create("Core");
    TCase *sc_1 = tcase_create("Core");
    SRunner *sr = srunner_create(smc);
    int fail;

    suite_add_tcase(smc, sc_1);
    tcase_add_test(sc_1, calc_test);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_ENV);
    fail = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}