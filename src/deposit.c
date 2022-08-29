#include "calc.h"

int leap_year(int year) {
    int leap = 1;

    if (((year % 4) != 0) || (((year % 100) == 0)
    && ((year % 400) != 0)))
        leap = 0;
    return leap;
}

int dayam(int month, int leap) {
    int days = 0;

    if (month == 4 || month == 6
    || month == 9 || month == 11) {
        days = 30;
    } else if (month == 2) {
        if (leap)
            days = 29;
        else
            days = 28;
    } else {
        days = 31;
    }
    return days;
}

int per_day(dep_in *I) {
    int pay_count = 0

    if (I->time_flag == 0)
        pay_count = I->time;
    else if (I->time_flag == 1)
        for (int i = 0; i < time; i++)
            pay_count += dayam(I->month + i,
            leap_year(I->year));
    else if (I->time_flag == 2)
        for (int i = 0; i < I->time; i++)
            if (leap_year(I->year + i))
                pay_count += 366;
            else
                pay_count += 365;
    return pay_count;
}

int per_week(dep_in *I) {
    int pay_count = 0;

    if (I->time_flag == 0)
        pay_count = I->time / 7;
    else if (I->time_flag == 1)
        for (int i = 0; i < time; i++)
            pay_count += dayam(I->month + i,
            leap_year(I->year)) / 7;
    else if (I->time_flag == 2)
        for (int i = 0; i < I->time; i++)
            if (leap_year(I->year + i))
                pay_count += 366 / 7;
            else
                pay_count += 365 / 7;
    return pay_count;
}

int per_month(dep_in *I) {
    int pay_count = 0;

    if (I->time_flag == 1)
        pay_count = I->time;
    else if (I->time_flag == 2)
        pay_count = I->time * 12;
    return pay_count;
}

int per_quat(dep_in *I) {
    int pay_count = 0;

    if (I->time_flag == 1)
        pay_count = I->time / 3;
    else if (I->time_flag == 2)
        pay_count = I->time * 4;
    return pay_count;
}

int per_half(dep_in *I) {
    int pay_count = 0;

    if (I->time_flag == 0) {
        pay_count = I->time / 182;
    } else if (I->time_flag == 1)
        pay_count = I->time / 6;
    else if (I->time_flag == 2)
        pay_count = I->time * 2;
    return pay_count;
}

int per_year(dep_in *I) {
    int pay_count = 0;

    if (I->time_flag == 0)
        pay_count = I->time / 365;
    else if (I->time_flag == 1)
        pay_count = I->time / 12;
    else if (I->time_flag == 2)
        pay_count = I->time;
    return pay_count;
}

int pay_counter(dep_in *I) {
    int pay_count = 0;
    
    if (I->period == 0) {
        pay_count = per_dayly(I);
    } else if (I->period == 1) {
        pay_count = per_week(I);
    } else if (I->period == 2) {
        pay_count = per_month(I);
    } else if (I->period == 3) {
        pay_count = per_quat(I);
    } else if (I->period == 4) {
        pay_count = per_half(I);
    } else if (I->period == 5) {
        pay_count = per_year(I);
    } else if (I->period == 6) {
        pay_count = 1;
    }
    return pay_count;
}

double capital(dep_in *I, int pay_count) {
    double all_in = I->cash;

    for (int i = 0; i < pay_count; i++) {
        all_in += all_in * (I->percent / 100)
    / pay_count;
    }
    return all_in;
}

double no_capital(dep_in, int pay_count) {
    double all_in = 0;

    for (int i = 0; i < pay_count; i++) {
        all_in += I->cash * (I->percent / 100)
    / pay_count;
    }
    return all_in;
}

int tax_dline(int date, int month, int year, int period) {
    int deadline = 0;
    int days = 0;
    int weeks = 0;
    int months = 0;
    int quarters = 0;

    for (; month < 12; month++) {
        days += (dayam(month, leap_year(year)) - date);
        date = 0;
        months++;
        if ((months / 3) > 0 && (months % 3) == 0)
            quarters++;
    }
    weeks = days / 7;
    if (period == 0)
        deadline = days;
    else if (period == 1)
        deadline = weeks;
    else if (period == 2)
        deadline = months;
    else if (period == 3)
        deadline = quarters;
    return deadline;
}

double tax_counter(double income) {
    double free_cash = 10000 * I->tax_per;
    double tax = 0;

    if (income > free_cash)
        tax = 0.13 * (income - free_cash);
    return tax;
}

void cash_bf_dline(dep_in *I, dep_out *O, int *pay_count) {
    int deadline = tax_dline(I->date, I->month, I->year, I->period);
    double tax = 0;
    double cash = 0;

    if (I->capitalize) {
        cash = capital(I, deadline);
        tax = tax_counter(cash);
        O->leftover = I->cash + cash;
        O->percent += cash;
    } else {
        cash = no_capital(I, deadline);
        tax = tax_counter(cash);
        O->leftover = I->cash;
        O->percent += cash;
    }
    O->tax += tax;
    *pay_count -= deadline;
}

int deposit(dep_in *I, dep_r *R, dep_w *W, dep_out *O) {
    int pay_count = pay_counter(I);
    
    cash_bf_dline(I, O, &pay_count);
    if (I->capitalize) {
        O->leftover = capital(I, pay_count);
        O->percent = O->leftover - I->cash;
    } else {
        O->leftover = I->cash;
        O->percent = no_capital(I, pay_count);
    }
}