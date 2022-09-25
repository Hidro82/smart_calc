#include <check.h>

#include "../brains/calc.h"

START_TEST(calc_test) {
  char og[255] =
      "sin(3.14)-(-8)-9+cos(3.14)^2*(2mod(2/"
      "2))+ln(1)+log(1)+asin(0)+acos(1)+atan(0)+tan(0)+sqrt(4)=";
  stack_n N;
  N.count = 0;
  stack_s S;
  S.count = 0;
  double result = 0.0;

  stacker(og, &N, &S, 0.0, &result);
  ck_assert_double_eq_tol(result, 1, 1e-2);
}

START_TEST(credit_test_1) {
  cred_in I;
  I.cash = 300000;
  I.differ = 0;
  I.month = 0;
  I.time = 2;
  I.percent = 5;
  cred_out O;
  O.monthly[0] = 0;
  O.monthly[1] = 0;
  O.over = 0;
  O.whole = 0;

  credit_calculus(&I, &O);
  ck_assert_double_eq_tol(O.whole, 315874, 10);
}

START_TEST(credit_test_2) {
  cred_in I;
  I.cash = 300000;
  I.differ = 1;
  I.month = 0;
  I.time = 1;
  I.percent = 5;
  cred_out O;
  O.monthly[0] = 0;
  O.monthly[1] = 0;
  O.over = 0;
  O.whole = 0;

  credit_calculus(&I, &O);
  ck_assert_double_eq_tol(O.whole, 308125, 100);
}

START_TEST(credit_test_3) {
  cred_in I;
  I.cash = 300000;
  I.differ = 0;
  I.month = 1;
  I.time = 24;
  I.percent = 5;
  cred_out O;
  O.monthly[0] = 0;
  O.monthly[1] = 0;
  O.over = 0;
  O.whole = 0;

  credit_calculus(&I, &O);
  ck_assert_double_eq_tol(O.whole, 315874, 100);
}

START_TEST(credit_test_4) {
  cred_in I;
  I.cash = 300000;
  I.differ = 1;
  I.month = 1;
  I.time = 1;
  I.percent = 5;
  cred_out O;
  O.monthly[0] = 0;
  O.monthly[1] = 0;
  O.over = 0;
  O.whole = 0;

  credit_calculus(&I, &O);
  ck_assert_double_eq_tol(O.whole, 301250, 100);
}

int main(void) {
  Suite *smc = suite_create("Core");
  TCase *sc_1 = tcase_create("Core");
  SRunner *sr = srunner_create(smc);
  int fail;

  suite_add_tcase(smc, sc_1);
  tcase_add_test(sc_1, calc_test);
  tcase_add_test(sc_1, credit_test_1);
  tcase_add_test(sc_1, credit_test_2);
  tcase_add_test(sc_1, credit_test_3);
  tcase_add_test(sc_1, credit_test_4);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  fail = srunner_ntests_failed(sr);
  srunner_free(sr);

  return fail == 0 ? 0 : 1;
}