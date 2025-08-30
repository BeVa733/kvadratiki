#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "kvvadratiki.h"

enum possible_outcomes solve_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(is_double(coefficients[A_INDEX]));
    assert(is_double(coefficients[B_INDEX]));
    assert(is_double(coefficients[C_INDEX]));

    if (check_equal_zero(coefficients[A_INDEX]))
        return solve_linear_equation(coefficients, solutions);

    else
        return solve_square_equation(coefficients, solutions);
}

enum possible_outcomes solve_linear_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(is_double(coefficients[A_INDEX]));
    assert(is_double(coefficients[B_INDEX]));
    assert(is_double(coefficients[C_INDEX]));

    if (check_equal_zero(coefficients[B_INDEX]))
    {
        if (check_equal_zero(coefficients[C_INDEX]))
            return MANY_SOLUTIONS;

        else
            return NO_SOLUTIONS;
    }

    else
    {
        solutions[0] = -coefficients[C_INDEX] / coefficients[B_INDEX];
        return ONE_SOLUTION;
    }
}

enum possible_outcomes solve_square_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(is_double(coefficients[A_INDEX]));
    assert(is_double(coefficients[B_INDEX]));
    assert(is_double(coefficients[C_INDEX]));

    double discriminant = coefficients[B_INDEX] * coefficients[B_INDEX] - 4 * coefficients[A_INDEX] * coefficients[C_INDEX];

    if (discriminant < 0)
        return NO_SOLUTIONS;

    else if (check_equal_zero(discriminant))
    {
        solutions[0] = (fabs(coefficients[B_INDEX])< LOW_NUMBER) ? 0 : -coefficients[B_INDEX] / (2 * coefficients[A_INDEX]);
        return ONE_SOLUTION;
    }

    else
    {
        solutions[0] = (fabs((-coefficients[B_INDEX] + sqrt(discriminant)) / (2 * coefficients[A_INDEX])) < LOW_NUMBER) ? 0 : (-coefficients[B_INDEX] + sqrt(discriminant)) / (2 * coefficients[A_INDEX]);
        solutions[1] = (fabs((-coefficients[B_INDEX] - sqrt(discriminant)) / (2 * coefficients[A_INDEX])) < LOW_NUMBER) ? 0 : (-coefficients[B_INDEX] - sqrt(discriminant)) / (2 * coefficients[A_INDEX]);
        return TWO_SOLUTIONS;
    }
}

bool check_equal_zero(double number)
{
    return fabs(number) < LOW_NUMBER;
}

bool is_double(double x)
{
    return !(isnan(x) || isinf(x));
}

