#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct number_stack {
    double num[256];
    int count;
} stack_n;

typedef struct sign_stack {
    int priority[256];
    char sign[256];
    int count;
} stack_s;

int operand_priority(char sign);
int calc_brain(stack_n *N, stack_s *S);

int stacker(char *og, stack_n *N, stack_s *S, double *result);

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
