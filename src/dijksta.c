#include "calc.h"

/* This Gargantua is the main function of this calculator
    it reads the entry string, parses the numbers and
    operators from it and, finally, calculates */

int sign_operator(stack_s *S, char og, char backup) {
    int errCode = 0;

    if (og != '=') {
        if (backup == 'z' || backup == '(') {
            if (og == '-')
                push_sign(S, "~");
            else if (og == '+')
                push_sign(S, "p");
            else if (og == '(')
                push_sign(S, "(");
            else if (og == '^' || og == '*'
            || og == '/' || og == 'm' || og == ')')
                errCode = 6;
        } else if (backup == 'a') {
            if (og == 's')
                push_sign(S, "S");
            else if (og == 'c')
                push_sign(S, "C");
            else if (og == 't')
                push_sign(S, "T");
            } else if (backup == 'l') {
                if (og == 'n')
                    push_sign(S, "l");
                else if (og == 'o')
                    push_sign(S, "L");
        } else if (backup == 's' && og == 'q')
            push_sign(S, "q");
        else if (backup == 's' && og == 'i')
            push_sign(S, "s");
        else if (backup == 'c' && og == 'o')
            push_sign(S, "c");
        else if (backup == 't' && og == 'a')
            push_sign(S, "t");
        else if (og == '+' || og == '-' || og == '*'
                || og == '/' || og == '^' || og == 'm'
                || og == '(' || og == ')') {
            push_sign(S, &og);
        }
    }
    return errCode;
}

int brace_operator(stack_s *S, stack_n *N,
                    char og, char *oper, int *brace_opened) {
    int errCode = 0;
    
    if (og == '(') {
        *brace_opened = *brace_opened + 1;
    } else if (og == ')') {
        *brace_opened = *brace_opened - 1;
        if (*brace_opened < 0) {
            errCode = 4;
        } else {
            do {
                errCode = calc_brain(N, S);
            } while (S->sign[S->count-1] != '(' && !errCode);
            pull_sign(S, oper);
        }
    }
    return errCode;
}

int string_processor(char *og, stack_n *N, stack_s *S, double x_var) {
    double number = 0;
    int i = 0;
    int j = 0;
    int errCode = 0;
    int brace_opened = 0;
    char oper;
    char backup = 'z';
    char buffer[256] = "";

    while (*og && !errCode) {
        if ((*og >= '0' && *og <= '9') || *og == '.') {
            buffer[i] = *og;
            i++;
        } else if (*og == 'X') {
            push_number(N, &x_var);
        } else { 
            if (i) {
                number = atof(buffer);
                push_number(N, &number);
                while(i) {
                    buffer[i] = '\0';
                    i--;
                }
            }
            if (S->count >= 1 && (S->priority[S->count - 1] > operand_priority(*og))
                && (*og != '('))
                errCode = calc_brain(N, S);
            errCode = sign_operator(S, *og, backup);
            errCode = brace_operator(S, N, *og, &oper, &brace_opened);
        }
        backup = *og;
        og++;
        j++;
    }
    if (brace_opened > 0)
        errCode = 5;
    og = og - j - 1;
    return errCode;
}

int stacker(char *og, stack_n *N, stack_s *S, double x_var, double *result) {
    int errCode = 0;

    errCode = string_processor(og, N, S, x_var);
    if (S->count > 0 && !errCode)
        while(S->count > 0 && !errCode)
            errCode = calc_brain(N, S);
    *result = N->num[0];
    clear_stacks(N, S);
    return errCode;
}
