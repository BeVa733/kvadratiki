#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "kvvadratiki.h"

void output_received_solution(double *solutions, enum possible_outcomes n_roots)
{
    assert(solutions);

    switch (n_roots)
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
        case ERROR_SOLUTIONS:
            printf("%sincorrect coefficients have been introduce%s\n", RED, BASIS);
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
        enum type_answer users_answer = ANOTHER;
        char answer[LEN_STR];

        scanf("%s", answer);

        for (int index = 0; index < LEN_STR; index++)
        {
            if (!strcmp(answer_yes[index], answer))
            {
                users_answer = YES;
                break;
            }
            else if (strcmp(answer_no[index], answer) == 0)
            {
                users_answer = NO;
                break;
            }
        }

        if (users_answer == YES)
        {
            return true;
        }

        else if (users_answer == NO)
        {
            return false;
        }

        else
        {
            printf("Enter %sYES%s / %sNO%s\n", GREEN, BASIS, RED, BASIS);
        }
    }

    return 0;
}
