#include "calc.h"

/* All this functions are made to emulate stack 
    behavior in current program. 'Push' functions
    are adding another element in stack and 'pull'
    functions are taking the last one in the line */

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
    if (N->count >= 0) {
        *token = N->num[N->count];
        N->num[N->count] = 0;
    }
}

void pull_sign(stack_s *S, char *token) {
    S->count -= 1;
    if (S->count >= 0) {
        S->priority[S->count] = 0;
        *token = S->sign[S->count];
        S->sign[S->count] = 0;
    }
}

void clear_stacks(stack_n *N, stack_s *S) {
    while (N->count >= 0) {
        N->num[N->count] = 0;
        N->count--;
    }
    while (S->count >= 0) {
        S->sign[S->count] = '\0';
        S->count--;
    }
}
