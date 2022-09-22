#include "calc.h"

/* This functions are doing calculation operations
    with stacks */

int operand_priority(char sign) {
  /* This function decides the priority of the current
      operator. In the main function if the pointer sees, that
      the current operator is less valuable than the last one - it
      starts counting, until the priority of the last operator in
      stack is equal or less than a current */
  int result = 9000;

  if (sign == '(')
    result = 0;
  else if (sign == '+' || sign == '-')
    result = 1;
  else if (sign == '*' || sign == '/' || sign == 'm')
    result = 2;
  else if (sign == '^')
    result = 3;
  else if (sign == 'p' || sign == '~')
    result = 4;
  else if (sign == 's' || sign == 'c' || sign == 't' || sign == 'S' ||
           sign == 'C' || sign == 'T' || sign == 'q' || sign == 'l' ||
           sign == 'L')
    result = 5;
  else if (sign == ')')
    result = 6;
  return result;
}

int calc_brain(stack_n *N, stack_s *S) {
  /* This masterpiece of Indian code calculates the last
      one or two numbers in number stack, depending on the last
      operator in operator stack */
  char oper = '\0';
  int errCode = 0;

  pull_sign(S, &oper);
  if (N->count <= 0 ||
      (N->count == 1 && (oper == '+' || oper == '-' || oper == '*' ||
                         oper == '/' || oper == 'm' || oper == '^'))) {
    errCode = 3;
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
    else if (oper == 'm')
      errCode = modder(N);
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
      errCode = arcsinus(N);
    else if (oper == 'C')
      errCode = arccosinus(N);
    else if (oper == 'T')
      arctangens(N);
    else if (oper == 'q')
      errCode = square(N);
    else if (oper == 'l')
      errCode = log_nat(N);
    else if (oper == 'L')
      errCode = log_ten(N);
  }
  if (S->count < 0) S->count++;
  return errCode;
}
