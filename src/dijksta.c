#include "calc.h"

int stacker(char *og, stack_n *N, stack_s *S, double *result) {
    double number = 0;
    char buffer[256] = "";
    int i = 0;
    int brace_opened = 0;
    int errCode = 0;

    while (*og && !errCode) {
        if ((*og >= '0' && *og <= '9') || *og == '.') {
            buffer[i] = *og;
            i++;
        } else if (i) {
            number = atof(buffer);
            push_number(N, &number);
            while(i) {
                buffer[i] = '\0';
                i--;
            }
        } else {
            if (S->count > 1 && (S->priority[S->count - 2] > operand_priority(*og)))
                errCode = calc_brain(N, S);
            push_sign(S, og);
            if (*og == '(') {
                brace_opened++;
            } else if (*og == ')') {
                brace_opened--;
            }
            if (brace_opened < 0)
                errCode = 5;
        }
        og++;
    }
    if (S->count != 0)
        calc_brain(N, S);
    if (brace_opened > 0)
        errCode = 6;
    *result = N->num[0];
    return errCode;
}
