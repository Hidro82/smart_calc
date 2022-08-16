#include "calc.h"

int main()
{
    int errCode = 0;
    stack_n N;
    stack_s S;
    N.count = 0;
    S.count = 0;
    char *og = "cos(3.14159265)=";
    double result = 0;
    errCode = stacker(og, &N, &S, &result);
    if (!errCode) {
        printf("result: %f\n", result);
    } else
        printf("errCode: %d\n", errCode);
    return 0;
}