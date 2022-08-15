#include "calc.h"

int operand_priority(char sign) {
    int result = 0;

    if (sign == '(')
        result = 0;
    else if (sign == '+' || sign == '-')
        result = 1;
    else if (sign == '*' || sign == '/')
        result = 2;
    else if (sign == '^')
        result = 3;
    else if (sign == ')')
        result = 4;
    return result;
}

int calc_brain(stack_n *N, stack_s *S) {
    char oper = '\0';
    int errCode = 0;
    int bracket = 0;

    pull_sign(S, &oper);
    if (oper == ')')
        bracket = 1;
    while (S->count >= 0 && !errCode && oper != '(') {
        if (N->count <= 0) {
            errCode = 4;
        } else {
            if (oper == '+')
                summer(N);
            else if (oper == '-')
                suber(N);
            else if (oper == '*')
                multiplier(N);
            else if (oper == '/')
                errCode = divisor(N);
            else if (oper == '^')
                errCode = power(N);
        }
        pull_sign(S, &oper);
    }
    if (oper == '(') {
        if (!bracket)
            push_sign(S, &oper);
    }
    if (S->count < 0)
        S->count++;
    return errCode;
}