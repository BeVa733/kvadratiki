#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "kvvadratiki.h"

int input_coefficients(double *coefficients)
{
    assert(coefficients);

    struct coeff_identification id =
    {
        .literal = {'a', 'b', 'c'},
        .number = { A_INDEX,   B_INDEX,   C_INDEX}
    };

    bool is_input_incorrect = false;

    printf("enter the coefficients of the equation:\n");
    for (int i = 0; i < N_COEFFICIENTS; i++)
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

    printf("%c = ", id->literal[i]);

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
