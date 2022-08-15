#include "calc.h"

int main() {
    stack_n N;
    stack_s S;
    N.count = 0;
    S.count = 0;
    char *og = "3 + 2";
    double result = stacker(og, &N, &S);
    printf("result: %f\n", result);
    return 0;
}