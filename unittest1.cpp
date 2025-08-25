#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "kvvadratiki.h"

void test_solve_equation()
{
    const int N_TESTS = 6;
    bool zalupa = false;
    bool is_correctness_solutions = true;
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
        tests[i].test_type_output = solve_equation(tests[i].test_coefficients, tests[i].test_solutions);

        if (tests[i].test_type_output != tests[i].correct_type_output)
        {
            zalupa = true;
            printf("ERROR test %d : incorrect definition of the output type\n", i);
            continue;
        }
        else
        {
            is_correctness_solutions = check_solutions(tests[i].test_solutions, tests[i].correct_solutions);
            if (!is_correctness_solutions)
            {
                printf("ERROR test %d : incorrect answers\n", i);
                zalupa = true;
            }
        }
     }

    if (zalupa == false)
        printf("ALL TESTS COMPLETE!\n\n");
 }

bool check_solutions(double *test_solutions, double *correct_solutions)
{
    if (!isnan(correct_solutions[1]))
    {
        if (!(check_equal_zero(test_solutions[0] - correct_solutions[0])))
            return false;
    }

    if (!isnan(correct_solutions[1]))
    {
        if (!(check_equal_zero(test_solutions[1] - correct_solutions[1])))
            return false;
    }
    return true;
}
