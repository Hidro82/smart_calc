#include "calc.h"

void summer(stack_n *N) {
    double num_1 = 0;
    double num_2 = 0;
    double result = 0;

    pull_number(N, &num_2);
    pull_number(N, &num_1);
    result = num_1 + num_2;
    push_number(N, &(result));
}

void suber(stack_n *N) {
    double num_1 = 0;
    double num_2 = 0;
    double result = 0;

    pull_number(N, &num_2);
    pull_number(N, &num_1);
    result = num_1 - num_2;
    push_number(N, &(result));
}

void multiplier(stack_n *N) {
    double num_1 = 0;
    double num_2 = 0;
    double result = 0;

    pull_number(N, &num_2);
    pull_number(N, &num_1);
    result = num_1 * num_2;
    push_number(N, &(result));
}

int divisor(stack_n *N) {
    double num_1 = 0;
    double num_2 = 0;
    double result = 0;
    int errCode = 0;

    pull_number(N, &num_2);
    pull_number(N, &num_1);
    if (num_2 == 0)
        errCode = 1;
    else {
        result = num_1 / num_2;
        push_number(N, &(result));
    }
    return errCode;
}

int power(stack_n *N) {
    double num_1 = 0;
    double num_2 = 0;
    double result = 0;
    int errCode = 0;

    pull_number(N, &num_2);
    pull_number(N, &num_1);
    if ((num_1 == 0) && (num_2 < 0))
        errCode = 1;
    else if (num_1 < 0 && !floor(num_2))
        errCode = 2;
    else {
        result = pow(num_1, num_2);
        push_number(N, &(result));
    }
    return errCode;
}
