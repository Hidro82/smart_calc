#include "calc.h"

char *error_codes(int errCode) {
    char *error;

    if (errCode == 1)
        error = "Zero division!";
    else if (errCode == 2)
        error = "Root of negative number!";
    else if (errCode == 3)
        error = "Not enough numbers!";
    else if (errCode == 4)
        error = "Open the bracket!";
    else if (errCode == 5)
        error = "Close the bracket!";
    else if (errCode == 6)
        error = "Logarithm incorrect argument!";
    else if (errCode == 7)
        error = "Too many characters!";
    return error;
}