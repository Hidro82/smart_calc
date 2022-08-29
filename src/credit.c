#include "calc.h"

int credit_calculus(cred_in *I, cred_out *O) {
    int errCode = 0;

    if (I->cash <= 0)
        errCode = 1;
    else if (I->time <= 0)
        errCode = 2;
    else if (I->percent < 0.01 || I->percent > 999)
        errCode = 3;

    if (I->differ == 1)
        errCode = differential(I, O);
    else
        errCode = annuite(I, O);

    return errCode;
}

void differential(cred_in *I, cred_out *O) {
    int pay_count = 0;
    double payday = 0;  
    
    if (I->month == 1)
        pay_count = I->time;
    else
        pay_count = I->time * 12;
    payday = I->cash / pay_count;

    double rue[pay_count];

    for (int i = 0; i < pay_count; i++) {
        rue[i] = payday + (I->cash * procent / 1200);
        I->cash -= payday;
        O->whole += rue[i];
    }
    O->over = O->whole - payday * pay_count;
    O->monthly[0] = rue[0];
    O->monthly[1] = rue[pay_count - 1];
}

void annuite(cred_in *I, cred_out *O) {
    int pay_count = 0;
    double payday = 0;  
    
    if (I->month == 1)
        pay_count = I->time;
    else
        pay_count = I->time * 12;
    O->montly = I->cash * I->percent / 1200
    * pow((1 + (I->percent)/1200), pay_count)
    / (pow((1 + (I->percent)/1200), pay_count) - 1);
    O->whole = O->monthly * pay_count;
    O->over = O->whole - I->cash;
}