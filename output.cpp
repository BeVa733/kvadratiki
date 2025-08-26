#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "kvvadratiki.h"

void output_received_solution(double *solutions, enum possible_outcomes type_output)
{
    assert(solutions);

    switch (type_output)
    {
        case NO_SOLUTIONS:
            printf("This equation has no solutions.\n");
            break;
        case ONE_SOLUTION:
            printf("This equation has one solution x = %.2f\n", solutions[0]);
            break;
        case TWO_SOLUTIONS:
            printf("This equation has two solutions x=%.2f and x=%.2f\n", solutions[0], solutions[1]);
            break;
        case MANY_SOLUTIONS:
            printf("This equation has an infinite number of solutions.\n");
            break;
        case INCORRECT_INPUT:
            printf("incorrect coefficients have been introduced\n");
            break;
        default:
            printf("the program is broken......\n");
            break;
    }
}

bool get_users_answer (void)
{
    const int LEN_STR = 5;
    const char answer_yes[5][LEN_STR] = {"YES", "yes", "Yes", "y", "Y"};
    const char answer_no[5][LEN_STR] = {"NO", "no", "No", "n", "N"};

    while(true)
    {
        int equality = 0;
        char answer[LEN_STR];

        scanf("%s", answer);

        for (int index = 0; index < LEN_STR; index++)
        {
            if (strcmp(answer_yes[index], answer) == 0)
            {
                equality = 1;
                break;
            }
            else if (strcmp(answer_no[index], answer) == 0)
            {
                equality = -1;
                break;
            }
        }

        if ( equality == 1)
            return true;

        else if (equality == -1)
        {
            printf("COMMIT GITHUB");
            return false;
        }
        else
            printf("enter YES / NO\n");
    }
}
