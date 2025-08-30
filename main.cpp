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

    enum possible_outcomes n_roots = ERROR_SOLUTIONS;

    bool need_repetition = true;
    bool is_correctness_input = true;

    welcome();

    if (get_users_answer())
        test_solve_equation();

    do
    {
        is_correctness_input = input_coefficients(coefficients);

        n_roots = (is_correctness_input) ? solve_equation(coefficients, solutions) : ERROR_SOLUTIONS;

        output_received_solution(solutions, n_roots);

        printf("Would you like to solve another equation?\nEnter %sYES%s / %sNO%s\n", GREEN, BASIS, RED, BASIS);

        need_repetition = get_users_answer();

    } while (need_repetition);

    printf("%sCOMMIT GITHUB!%s", PURPLE, BASIS);

    return 0;
}

void welcome(void)
{
    printf("%sMEOW%s\n", PURPLE, BASIS);

    printf("This program solves equations like ax^2+bx+c=0\n"
    "Do you want to test the program before?\nenter %sYES%s/%sNO%s\n", GREEN, BASIS, RED, BASIS);
}
