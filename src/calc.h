#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <stdio.h>
#include <math.h>

typedef struct number_stack {
    double num[10];
    int count;
} stack_n;

typedef struct sign_stack {
    char sign[10];
    int count;
} stack_s;

double stacker(char *og, stack_n *N, stack_s *S);

void push_number(stack_n *N, double *token);
void push_sign(stack_s *S, char *token);
void pull_number(stack_n *N, double *token);
void pull_sign(stack_s *S, char *token);

void summer(stack_n *N);
void suber(stack_n *N);
void multiplier(stack_n *N);
int divisor(stack_n *N);
int power(stack_n *N);

#endif // SRC_CALC_H_
