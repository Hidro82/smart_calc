#include "calc.h"

int num_checker(char *buffer) {
    int errCode = 0;
    int dot = 0;
    int i = 0;

    while (*buffer && !errCode) {
        if (((*buffer < '0') || (*buffer > '9')) && (*buffer != '.') || (dot > 1))
            errCode = 8;
        if (*buffer == '.')
            dot++;
        i++;
        buffer++;
    }
    buffer -= i;
    return errCode;
}