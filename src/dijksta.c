#include "calc.h"

double stacker(char *og, stack_n *N, stack_s *S) {
    double number = 0;

    while (*og) {
        if (*og >= '0' && *og <= '9') {
            number = *og - 48;
            push_number(N, &number);
        }
        og++;
    }
    summer(N);
    return N->num[0];
}
