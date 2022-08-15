#include "calc.h"

int stacker(char *og, stack_n *N, stack_s *S, double *result) {
    double number = 0;
    char buffer[256] = "";
    int i = 0;
    int brace_opened = 0;
    int be_negative = 0;
    int errCode = 0;
    char kostil = '+';

    while (*og && !errCode) {
        if ((*og >= '0' && *og <= '9') || *og == '.') {
            buffer[i] = *og;
            i++;
        } else { 
            if (i) {
                number = atof(buffer);
                if (be_negative) {
                    number = -number;
                }
                push_number(N, &number);
                while(i) {
                    buffer[i] = '\0';
                    i--;
                }
            }
            if (S->count >= 1 && (S->priority[S->count - 1] > operand_priority(*og)) && (*og != 40))
                errCode = calc_brain(N, S);
            if (*og != '=') {
                if (*og == '-') {
                    be_negative = 1;
                    push_sign(S, &kostil);
                } else {
                    be_negative = 0;
                    push_sign(S, og);
                }
            }
            if (*og == 40) {
                brace_opened++;
            } else if (*og == ')') {
                brace_opened--;
            }
            if (brace_opened < 0)
                errCode = 5;
            printf("sign: %s\n", S->sign);
        }
        og++;
    }
    if (S->count > 0)
        calc_brain(N, S);
    if (brace_opened > 0)
        errCode = 6;
    *result = N->num[0];
    return errCode;
}
