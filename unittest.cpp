#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "kvvadratiki.h"

void test_solve_equation()
{
    FILE *file = fopen("test_data.txt", "r");
    if (file == NULL)
    {
        printf("%sError: Could not open test_data.txt%s\n", RED, BASIS);

        return;
    }

    bool is_zalupa = false;
    int test_count = 0;

    while (true)
    {
        test_data test ={   .test_coefficients = {NAN, NAN, NAN},
                            .test_solutions    = {NAN, NAN},
                            .correct_solutions = {NAN, NAN},
                            .test_n_roots      = ERROR_SOLUTIONS,
                            .correct_n_roots   = ERROR_SOLUTIONS,
                        };
        int correct_n_roots_int;

        int read_count = fscanf(file, "%lf %lf %lf %lf %lf %d\n",
            &(test.test_coefficients[A_INDEX]),
            &(test.test_coefficients[B_INDEX]),
            &(test.test_coefficients[C_INDEX]),
            &(test.correct_solutions[0]),
            &(test.correct_solutions[1]),
            &(correct_n_roots_int));

        if (read_count != 6)
        {
            if (feof(file))
                break;

            printf("%sError reading test %d from file%s\n",RED, test_count, BASIS);
            is_zalupa = true;
            test_count++;

            continue;
        }

        test.correct_n_roots = (enum possible_outcomes)correct_n_roots_int;
        test.test_n_roots = ERROR_SOLUTIONS;
        test.test_solutions[0] = NAN;
        test.test_solutions[1] = NAN;

        if (one_test(&test, test_count)) {
            is_zalupa = true;
        }
        test_count++;
    }

    fclose(file);

    if (!is_zalupa) {
        printf("\n%sALL TESTS COMPLETE!%s\n\n", GREEN, BASIS);
    }
}

bool one_test(test_data *test, int test_index)
{

    test->test_n_roots = solve_equation(test->test_coefficients, test->test_solutions);

    if (test->test_n_roots != test->correct_n_roots) {
        printf("%s ERROR test %d: incorrect number of roots. Expected: %d, Got: %d%s\n",
               RED, test_index, test->correct_n_roots, test->test_n_roots, BASIS);
        return true;
    }

    if (!check_solutions(test->test_solutions, test->correct_solutions) && (test->correct_n_roots == 1 || test->correct_n_roots ==2))
    {
        printf("%sERROR test %d: incorrect solutions. Expected: %.2lg and %.2lg, Got: %.2lg and %.2lg%s\n",
               RED, test_index,
               test->correct_solutions[0], test->correct_solutions[1],
               test->test_solutions[0], test->test_solutions[1], BASIS);
        return true;
    }

    return false;
}

bool check_solutions(double *test_solutions, double *correct_solutions)
{
    for (int i = 0; i < N_SOLUTIONS; i++)
    {
        if (!isnan(test_solutions[i]))
        {
            if (isnan(correct_solutions[i]) != isnan(test_solutions[i]))
            {
                return false;
            }

            if (!isnan(correct_solutions[i]) && fabs(test_solutions[i] - correct_solutions[i]) > LOW_NUMBER )
            {
                return false;
            }
        }
    }
    return true;
}
