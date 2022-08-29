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

typedef struct credit_input {
    double cash;
    int time;
    int month;
    double percent;
    int differ;
} cred_in;

typedef struct credit_output {
    double monthly[2];
    double over;
    double whole;
} cred_out;

typedef struct deposit_input {
    double cash;
    int time;
    /* time_flag == 0 => years
        time_flag == 1 => months
        time_flag == 2 => days */
    int time_flag;
    int date;
    int month;
    int year;
    double percent;
    double tax_per;
    /* 0 - every day
        1 - every week
        2 - every month
        3 - every quater
        4 - twice a year
        5 - once a year
        6 - at the end */
    int period;
    int capitalize;

} dep_in;

typedef deposit_raise {
    double cash;
    int date;
    int month;
    int year;
} dep_r;

typedef deposit_withdrawal {
    double cash;
    int date;
    int month;
    int year;
} dep_w;

typedef deposit_output {
    double percent;
    double tax;
    double leftover;
}

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

int credit_calculus(cred_in *I, cred_out *O);
void differential(cred_in *I, cred_out *O);
void annuite(cred_in *I, cred_out *O);

#endif // SRC_CALC_H_
