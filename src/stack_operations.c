#include "calc.h"

void push_number(stack_n *N, double *token) {
    N->num[N->count] = *token;
    N->count += 1;
}

void push_sign(stack_s *S, char *token) {
    S->sign[S->count] = *token;
    S->priority[S->count] = operand_priority(*token);
    S->count += 1;
}

void pull_number(stack_n *N, double *token) {
    N->count -= 1;
    *token = N->num[N->count];
    N->num[N->count] = 0;
}

void pull_sign(stack_s *S, char *token) {
    S->count -= 1;
    if (S->count >= 0) {
        S->priority[S->count] = 0;
        *token = S->sign[S->count];
        S->sign[S->count] = 0;
    }
}
