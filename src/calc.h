#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <cairo.h>

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

int stacker(char *og, stack_n *N, stack_s *S, double x_var, double *result);

void push_number(stack_n *N, double *token);
void push_sign(stack_s *S, char *token);
void pull_number(stack_n *N, double *token);
void pull_sign(stack_s *S, char *token);
void clear_stacks(stack_n *N, stack_s *S);

void summer(stack_n *N);
void suber(stack_n *N);
void multiplier(stack_n *N);
int divisor(stack_n *N);
int modder(stack_n *N);
int power(stack_n *N);
void negativate(stack_n *N);
void sinus(stack_n *N);
void cosinus(stack_n *N);
void tangens(stack_n *N);
void arcsin(stack_n *N);
void arccos(stack_n *N);
void arctan(stack_n *N);
int square(stack_n *N);
int log_nat(stack_n *N);
int log_ten(stack_n *N);

char *error_codes(int errCode);
int num_checker(char *buffer);

#endif // SRC_CALC_H_
