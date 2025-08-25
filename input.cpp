#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "kvvadratiki.h"

int input_coefficients(double *coefficients)
{
    assert(coefficients != 0);

    printf("enter the coefficients of the equation:\n");
    printf("a= ");

    if (scanf("%lf", &coefficients[A]) != 1)
    {
        cleaning_buffer();
        return false;
    }

    printf("b= ");

    if (scanf("%lf", &coefficients[B]) != 1)
    {
        cleaning_buffer();
        return false;
    }

    printf("c= ");

    if (scanf("%lf", &coefficients[C]) != 1)
    {
        cleaning_buffer();
        return false;
    }

    return true;
}

void cleaning_buffer(void)
{
    while (getchar() != '\n')
        continue;
}
