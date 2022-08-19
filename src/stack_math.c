#include "calc.h"

/* This is a series of math functions, that can work with
    numbers in a stack */

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

int modder(stack_n *N) {
    double num_1 = 0;
    double num_2 = 0;
    double result = 0;
    int errCode = 0;

    pull_number(N, &num_2);
    pull_number(N, &num_1);
    if (num_2 == 0)
        errCode = 1;
    else {
        result = fmod(num_1, num_2);
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

void negativate(stack_n *N) {
    double num = 0;
    
    pull_number(N, &num);
    num = -num;
    push_number(N, &(num));
}

void sinus(stack_n *N) {
    double num = 0;
    double result = 0;

    pull_number(N, &num);
    result = sin(num);
    push_number(N, &(result));
}

void cosinus(stack_n *N) {
    double num = 0;
    double result = 0;

    pull_number(N, &num);
    result = cos(num);
    push_number(N, &(result));
}

void tangens(stack_n *N) {
    double num = 0;
    double result = 0;

    pull_number(N, &num);
    result = tan(num);
    push_number(N, &(result));
}

void arcsin(stack_n *N) {
    double num = 0;
    double result = 0;

    pull_number(N, &num);
    result = asin(num);
    push_number(N, &(result));
}

void arccos(stack_n *N) {
    double num = 0;
    double result = 0;

    pull_number(N, &num);
    result = acos(num);
    push_number(N, &(result));
}

void arctan(stack_n *N) {
    double num = 0;
    double result = 0;

    pull_number(N, &num);
    result = atan(num);
    push_number(N, &(result));
}

int square(stack_n *N) {
    double num = 0;
    double result = 0;
    int errCode = 0;

    pull_number(N, &num);
    if (num < 0)
        errCode = 2;
    else
        result = sqrt(num);
    push_number(N, &(result));
    return errCode;
}

int log_nat(stack_n *N) {
    double num = 0;
    double result = 0;
    int errCode = 0;

    pull_number(N, &num);
    if (num > 0)
        result = log(num);
    else
        errCode = 6;
    push_number(N, &(result));
    return errCode;
}

int log_ten(stack_n *N) {
    double num = 0;
    double result = 0;
    int errCode = 0;

    pull_number(N, &num);
    if (num > 0)
        result = log10(num);
    else
        errCode = 6;
    push_number(N, &(result));
    return errCode;
}
