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
    unsigned int time;
    /* time_flag:
        0 - years
        1 - months
        2 - days */
    unsigned int time_flag;
    unsigned int date;
    unsigned int month;
    unsigned int year;
    double percent;
    double tax_per;
    /* period:
        0 - dayly
        1 - weekly
        2 - monthly
        3 - quaterly
        4 - twice a year
        5 - once a year
        6 - in the end */
    unsigned int period;
    unsigned int capitalize;
} dep_in;

typedef struct calender {
    unsigned int date;
    unsigned int month;
    unsigned int year;
} tdy;

typedef struct deposit_raise {
    int count;
    double *cash;
    unsigned int *date;
    unsigned int *month;
    unsigned int *year;
} dep_r;

typedef struct deposit_withdrawal {
    int count;
    double *cash;
    unsigned int *date;
    unsigned int *month;
    unsigned int *year;
} dep_w;

typedef struct deposit_output {
    double percent;
    double tax;
    double leftover;
} dep_out;

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
