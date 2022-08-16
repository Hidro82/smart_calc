#include "calc.h"

int operand_priority(char sign) {
    int result = 9000;

    if (sign == '(')
        result = 0;
    else if (sign == '+' || sign == '-')
        result = 1;
    else if (sign == '*' || sign == '/')
        result = 2;
    else if (sign == '^')
        result = 3;
    else if (sign == 'p' || sign == '~')
        result = 4;
    else if (sign == 's' || sign == 'c' || sign == 't'
    || sign == 'S' || sign == 'C' || sign == 'T'
    || sign == 'q' || sign == 'l' || sign == 'L')
        result = 5;
    else if (sign == ')')
        result = 6;
    return result;
}

int calc_brain(stack_n *N, stack_s *S) {
    char oper = '\0';
    int errCode = 0;

    pull_sign(S, &oper);
    if (N->count <= 0) {
        errCode = 4;
    } else {
        if (oper == '+') {
            if (S->count == 0 || (S->count > 0 && S->sign[S->count - 1] != '-'))
                summer(N);
            else
                suber(N);
        } else if (oper == '-') {
            if (S->count == 0 || (S->count > 0 && S->sign[S->count - 1] != '-'))
                suber(N);
            else
                summer(N);
        } else if (oper == '*')
            multiplier(N);
        else if (oper == '/')
            errCode = divisor(N);
        else if (oper == '~')
            negativate(N);
        else if (oper == '^')
            errCode = power(N);
        else if (oper == 's')
            sinus(N);
        else if (oper == 'c')
            cosinus(N);
        else if (oper == 't')
            tangens(N);
        else if (oper == 'S')
            arcsin(N);
        else if (oper == 'C')
            arccos(N);
        else if (oper == 'T')
            arctan(N);
        else if (oper == 'q')
            errCode = square(N);
        else if (oper == 'l')
            errCode = log_nat(N);
        else if (oper == 'L')
            errCode = log_ten(N);
    }
    if (S->count < 0)
        S->count++;
    return errCode;
}