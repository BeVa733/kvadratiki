#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "kvvadratiki.h"

int main()
{
    double coefficients[3] = {NAN, NAN, NAN};
    double solutions[2] = {NAN, NAN};
    enum possible_outcomes type_output = INCORRECT_INPUT;
    bool need_repetition = true;
    bool is_correctness_input = true;

    printf("this program solves equations like ax^2+bx+c=0\n\n");
    printf("are you want to test program before?\nenter YES/NO\n");

    if (get_users_answer ())
        test_solve_equation();

    do
    {
        is_correctness_input = input_coefficients(coefficients);

        if (is_correctness_input)
            type_output = solve_equation(coefficients, solutions);

        else
            type_output = INCORRECT_INPUT;

        output_received_solution(solutions, type_output);

        printf("Would you like to solve another equation?\nenter YES/NO\n");

        need_repetition = get_users_answer();

    } while (need_repetition);

    return 0;
}
