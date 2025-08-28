#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "kvvadratiki.h"

int input_coefficients(double *coefficients)
{
    assert(coefficients != 0);

    struct coeff_identification id =
    {
        .litera = {'a', 'b', 'c'},
        .number = { A,   B,   C }
    };

    bool is_input_incorrect = false;

    printf("enter the coefficients of the equation:\n");
    for (int i = 0; i<3; i++)
    {
        is_input_incorrect = input_one_coefficient(&id, i, coefficients);

        if (is_input_incorrect)
        {
            return false;
        }
    }

    return true;
}

bool input_one_coefficient(struct coeff_identification *id, int i, double *coefficients)
{
    int ch = 0;

    printf("%c = ", id->litera[i]);

    if (scanf("%lf", &coefficients[id->number[i]]) != 1)
    {
        cleaning_buffer();
        return true;
    }

    while ((ch = getchar()) != '\n')
    {
        if (!isblank(ch))
        {
            cleaning_buffer();
            return true;
        }
    }

    return false;
}

void cleaning_buffer(void)
{
    while (getchar() != '\n')
        continue;
}
