#include<TXLib.h>
#include<stdio.h>
#include<math.h>

int input_coefficients (double *coefficient_a, double *coefficient_b, double *coefficient_c);
void output_received_solution (double sol_1, double sol_2, int count_solutions);
int solve_equation (double coefficient_a, double coefficient_b, double coefficient_c, double *sol_1, double *sol_2);

int main(void)
{
    double coefficient_a = 0, coefficient_b = 0, coefficient_c = 0;
    double sol_1 = 0, sol_2 = 0;
    int need_repetition = 1, check_correctness_input = 1, count_solutions = 0;
    printf("Эта программа решает уравнения вида ax^2+bx+c=0\n");

    do
    {
        check_correctness_input = 1;
        printf("Введите параметры уравнения:\n");
        check_correctness_input = input_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);

        if (check_correctness_input == 1)
            count_solutions = solve_equation(coefficient_a, coefficient_b, coefficient_c, &sol_1, &sol_2);
        else
            count_solutions = -1;

        output_received_solution(sol_1, sol_2, count_solutions);

        printf("Если хотите решить еще одно уравнение введите 1, для завершения программы введите 0\n");
        scanf("%d", &need_repetition);
    }while(need_repetition);

    return 0;
}


int input_coefficients (double *coefficient_a, double *coefficient_b, double *coefficient_c)
{
    int check_correctness_input = 1;
    printf("a= ");

    if (scanf("%lf", coefficient_a) != 1)
        check_correctness_input = 0;
    else
    {
        printf("b= ");
        if (scanf("%lf", coefficient_b) != 1)
            check_correctness_input = 0;
        else
        {
            printf("c= ");
            if (scanf("%lf", coefficient_c)!= 1)
                check_correctness_input = 0;
        }
    }

    if (check_correctness_input == 0)
    {
        while(getchar() != '\n')
            continue;
    }

    return check_correctness_input;
}


int solve_equation (double coefficient_a, double coefficient_b, double coefficient_c, double *sol_1, double *sol_2)
{
    double D = 0;
    int count_solutions;

    if (coefficient_a == 0)
    {
        if (coefficient_b ==0)
        {
            if (coefficient_c == 0)
                count_solutions = 3;
            else
               count_solutions = 0;
        }
        else
        {
            count_solutions = 1;
            *sol_1 = -coefficient_c/coefficient_b;
        }
    }
    else
    {
        D = coefficient_b*coefficient_b-4*coefficient_a*coefficient_c;
        if (D<0)
            count_solutions = 0;
        else if (D==0)
        {
            count_solutions = 1;
            *sol_1 = -coefficient_b/(2*coefficient_a);
        }
        else
        {
            count_solutions = 2;
            *sol_1 = (-coefficient_b+sqrt(D))/(2*coefficient_a);
            *sol_2 = (-coefficient_b-sqrt(D))/(2*coefficient_a);
        }
    }

    return count_solutions;
}


void output_received_solution (double sol_1, double sol_2, int count_solutions)
{
    switch(count_solutions)
    {

        case 0:
            printf("это уравнение не имеет решений\n");
            break;
        case 1:
            printf("Это уравнение имеет одно решение %.2f\n", sol_1);
            break;
        case 2:
            printf("Это уравнение имеет 2 решения x=%.2f и x=%.2f\n", sol_1, sol_2);
            break;
        case 3:
            printf("Это уравнение имеет бесконечное количество решений\n");
            break;
        default:
            printf("Введены некорректные коэффициены\n");
            break;
    }
}
