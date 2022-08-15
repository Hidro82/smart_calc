#include "calc.h"

void push_number(stack_n *N, double *token) {
    N->num[N->count] = *token;
    N->count += 1;
}

void push_sign(stack_s *S, char *token) {
    S->sign[S->count] = *token;
    S->count += 1;
}

void pull_number(stack_n *N, double *token) {
    N->count -= 1;
    *token = N->num[N->count];
}

void pull_sign(stack_s *S, char *token) {
    S->count -= 1;
    *token = S->sign[S->count];
}
