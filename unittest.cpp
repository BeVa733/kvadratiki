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
                                {{0, 2, -4}, {NAN, NAN}, {2, NAN},   ERROR_SOLUTIONS, ONE_SOLUTION  },
                                {{1, -3, 2}, {NAN, NAN}, {2, 1},     ERROR_SOLUTIONS, TWO_SOLUTIONS },
                                {{1, 0, 1},  {NAN, NAN}, {NAN, NAN}, ERROR_SOLUTIONS, NO_SOLUTIONS  },
                                {{0, 0, 0},  {NAN, NAN}, {NAN, NAN}, ERROR_SOLUTIONS, MANY_SOLUTIONS},
                                {{0, 0, 1},  {NAN, NAN}, {NAN, NAN}, ERROR_SOLUTIONS, NO_SOLUTIONS  },
                                {{1, 2, 1},  {NAN, NAN}, {-1, NAN},  ERROR_SOLUTIONS, ONE_SOLUTION  }
                              };

    for (int i = 0; i < N_TESTS; i++)
    {
        is_zalupa = one_test(tests, i);
    }

    if (!is_zalupa)
        printf("\nALL TESTS COMPLETE!\n\n");
 }

bool one_test(test_data *tests, int i)
{
    bool is_correctness_solutions = true;

    tests[i].test_n_roots = solve_equation(tests[i].test_coefficients, tests[i].test_solutions);

    if (tests[i].test_n_roots != tests[i].correct_n_roots)
    {
        printf("ERROR test %d : incorrect definition of the output type\n", i);

        return true;
    }
    else
    {
        is_correctness_solutions = check_solutions(tests[i].test_solutions, tests[i].correct_solutions);

        if (!is_correctness_solutions)
        {
            printf("ERROR test %d : incorrect answers: \n"
            "correct: %.2f and %.2f, "
            "test: %.2f and %.2f\n", i, tests[i].correct_solutions[0], tests[i].correct_solutions[1], tests[i].test_solutions[0], tests[i].test_solutions[1]);

            return true;
        }

    return false;
    }
}

bool check_solutions(double *test_solutions, double *correct_solutions)
{
    for (int i = 0; i < 2; i++)
    {
        if (!isnan(correct_solutions[i]) && !isnan(test_solutions[i]))
        {
            if (!(check_equal_zero(test_solutions[i] - correct_solutions[i])))
                return false;
        }
        else if ((!isnan(correct_solutions[i]) && isnan(test_solutions[i])) || (isnan(correct_solutions[i]) && !isnan(test_solutions[i])))
        {
            return false;
        }
    }
    return true;
}
