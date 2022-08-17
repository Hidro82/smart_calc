#include "calc.h"

int stacker(char *og, stack_n *N, stack_s *S, double *result) {
    double number = 0;
    char buffer[256] = "";
    int i = 0;
    int brace_opened = 0;
    int errCode = 0;
    char oper;
    char backup = 'z';

    while (*og && !errCode) {
        if ((*og >= '0' && *og <= '9') || *og == '.') {
            buffer[i] = *og;
            i++;
        } else { 
            if (i) {
                number = atof(buffer);
                push_number(N, &number);
                printf("number: %f\n", number);
                while(i) {
                    buffer[i] = '\0';
                    i--;
                }
            }
            printf("current: %c\n", *og);
            if (S->count >= 1 && (S->priority[S->count - 1] > operand_priority(*og)) && (*og != '('))
                errCode = calc_brain(N, S);
            if (*og != '=') {
                if (backup == 'z' || backup == '(') {
                    if (*og == '-')
                        push_sign(S, "~");
                    else if (*og == '+')
                        push_sign(S, "p");
                    else if (*og == '(')
                        push_sign(S, "(");
                    else if (*og == '^' || *og == '*' || *og == '/' || *og == 'm' || *og == ')')
                        errCode = 6;
                } else if (backup == 'a') {
                    if (*og == 's')
                        push_sign(S, "S");
                    else if (*og == 'c')
                        push_sign(S, "C");
                    else if (*og == 't')
                        push_sign(S, "T");
                } else if (backup == 'l') {
                    if (*og == 'n')
                        push_sign(S, "l");
                    else if (*og == 'o')
                        push_sign(S, "L");
                } else if (backup == 's' && *og == 'q')
                    push_sign(S, "q");
                else if (backup == 's' && *og == 'i')
                    push_sign(S, "s");
                else if (backup == 'c' && *og == 'o')
                    push_sign(S, "c");
                else if (backup == 't' && *og == 'a')
                    push_sign(S, "t");
                else if (*og == '+' || *og == '-' || *og == '*'
                || *og == '/' || *og == '^' || *og == 'm'
                || *og == '(' || *og == ')') {
                    push_sign(S, og);
                }
            }
            if (*og == '(') {
                brace_opened++;
            } else if (*og == ')') {
                brace_opened--;
                if (brace_opened < 0) {
                    errCode = 4;
                } else {
                    do {
                        errCode = calc_brain(N, S);
                    } while (S->sign[S->count-1] != '(' && !errCode);
                    pull_sign(S, &oper);
                }
            }
            printf("sign: %s\n", S->sign);
        }
        backup = *og;
        og++;
    }
    if (S->count > 0)
        while(S->count > 0 && !errCode)
            errCode = calc_brain(N, S);
    if (brace_opened > 0)
        errCode = 5;
    *result = N->num[0];
    return errCode;
}
