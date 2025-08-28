#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "kvvadratiki.h"

enum possible_outcomes solve_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));

    if (check_equal_zero(coefficients[A]))
        return solve_linear_equation(coefficients, solutions);

    else
        return solve_square_equation(coefficients, solutions);
}

enum possible_outcomes solve_linear_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));

    if (check_equal_zero(coefficients[B]))
    {
        if (check_equal_zero(coefficients[C]))
            return MANY_SOLUTIONS;

        else
            return NO_SOLUTIONS;
    }

    else
    {
        solutions[0] = -coefficients[C] / coefficients[B];
        return ONE_SOLUTION;
    }
}

enum possible_outcomes solve_square_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));

    double discriminant = coefficients[B] * coefficients[B] - 4 * coefficients[A] * coefficients[C];

    if (discriminant < 0)
        return NO_SOLUTIONS;

    else if (check_equal_zero(discriminant))
    {
        solutions[0] = (fabs(coefficients[B])< LOW_NUMBER) ? 0 : -coefficients[B] / (2 * coefficients[A]);
        return ONE_SOLUTION;
    }

    else
    {
        solutions[0] = (fabs((-coefficients[B] + sqrt(discriminant)) / (2 * coefficients[A])) < LOW_NUMBER) ? 0 : (-coefficients[B] + sqrt(discriminant)) / (2 * coefficients[A]);
        solutions[1] = (fabs((-coefficients[B] - sqrt(discriminant)) / (2 * coefficients[A])) < LOW_NUMBER) ? 0 : (-coefficients[B] - sqrt(discriminant)) / (2 * coefficients[A]); //TODO func
        return TWO_SOLUTIONS;
    }
}

bool check_equal_zero(double number)
{
    return fabs(number) < LOW_NUMBER;
}
