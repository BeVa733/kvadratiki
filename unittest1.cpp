#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "kvvadratiki.h"

void test_solve_equation()
{
    const int N_TESTS = 6;
    bool is_zalupa = false;
    test_data tests[N_TESTS] ={
                                {{0, 2, -4}, {NAN, NAN}, {2, NAN},   INCORRECT_INPUT, ONE_SOLUTION  },
                                {{1, -3, 2}, {NAN, NAN}, {2, 1},     INCORRECT_INPUT, TWO_SOLUTIONS },
                                {{1, 0, 1},  {NAN, NAN}, {NAN, NAN}, INCORRECT_INPUT, NO_SOLUTIONS  },
                                {{0, 0, 0},  {NAN, NAN}, {NAN, NAN}, INCORRECT_INPUT, MANY_SOLUTIONS},
                                {{0, 0, 1},  {NAN, NAN}, {NAN, NAN}, INCORRECT_INPUT, NO_SOLUTIONS  },
                                {{1, 2, 1},  {NAN, NAN}, {-1, NAN},  INCORRECT_INPUT, ONE_SOLUTION  }
                              };

    for (int i = 0; i < N_TESTS; i++)
    {
        is_zalupa = one_test(tests, i);
    }

    if (is_zalupa == false)
        printf("ALL TESTS COMPLETE!\n\n");
 }

bool one_test(test_data *tests, int i)
{
    bool is_correctness_solutions = true;

    tests[i].test_type_output = solve_equation(tests[i].test_coefficients, tests[i].test_solutions);

    if (tests[i].test_type_output != tests[i].correct_type_output)
    {
        printf("ERROR test %d : incorrect definition of the output type\n", i);
        return true;
    }
    else
    {
    is_correctness_solutions = check_solutions(tests[i].test_solutions, tests[i].correct_solutions);

        if (!is_correctness_solutions)
        {
            printf("ERROR test %d : incorrect answers\n", i);
            return true;
        }
    return false;
    }
}

bool check_solutions(double *test_solutions, double *correct_solutions)
{
    for (int i = 0; i < 2; i++)
    {
        if (!isnan(correct_solutions[i]))
        {
            if (!(check_equal_zero(test_solutions[i] - correct_solutions[i])))
                return false;
        }
    }
    return true;
}
