#include<TXLib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>
enum possible_outcomes {no_solutions, one_solution, two_solutions, many_solutions, incorrect_input};

int input_coefficients (double *coefficient_a, double *coefficient_b, double *coefficient_c);
void output_received_solution (double sol_1, double sol_2, enum possible_outcomes type_output);
enum possible_outcomes solve_equation (double coefficient_a, double coefficient_b, double coefficient_c, double *sol_1, double *sol_2);

int main(void)
{
    double coefficient_a = 0, coefficient_b = 0, coefficient_c = 0;
    double sol_1 = 0, sol_2 = 0;
    enum possible_outcomes type_output = incorrect_input;
    int need_repetition = 1;
    bool check_correctness_input = true;

    printf("Эта программа решает уравнения вида ax^2+bx+c=0\n");

    do
    {
        check_correctness_input = input_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);

        if (check_correctness_input)
            type_output = solve_equation(coefficient_a, coefficient_b, coefficient_c, &sol_1, &sol_2);
        else
            type_output = incorrect_input;

        output_received_solution(sol_1, sol_2, type_output);
        printf("Если хотите решить еще одно уравнение введите 1, для завершения программы введите 0\n");
        scanf("%d", &need_repetition);
    }while(need_repetition);

    return 0;
}


int input_coefficients (double *coefficient_a, double *coefficient_b, double *coefficient_c)
{
    bool check_correctness_input = true;

    printf("Введите параметры уравнения:\n");
    printf("a= ");

    if (scanf("%lf", coefficient_a) != 1)
        check_correctness_input = false;
    else
    {
        printf("b= ");

        if (scanf("%lf", coefficient_b) != 1)
            check_correctness_input = false;
        else
        {
            printf("c= ");

            if (scanf("%lf", coefficient_c) != 1)
                check_correctness_input = false;
        }
    }

    if (!check_correctness_input)
    {
        while(getchar() != '\n')
            continue;
    }

    return check_correctness_input;
}


enum possible_outcomes solve_equation (double coefficient_a, double coefficient_b, double coefficient_c, double *sol_1, double *sol_2)
{
    double D = 0;
    enum possible_outcomes type_output = no_solutions;

    if (fabs(coefficient_a) < 0.00001)
    {
        if (fabs(coefficient_b) < 0.00001)
        {
            if (fabs(coefficient_c) < 0.00001)
                type_output = many_solutions;
            else
               type_output = no_solutions;
        }
        else
        {
            type_output = one_solution;
            *sol_1 = - coefficient_c / coefficient_b;
        }
    }
    else
    {
        D = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;

        if (D < 0)
            type_output = no_solutions;
        else if (fabs(D) < 0.0000000001)
        {
            type_output = one_solution;
            *sol_1 = - coefficient_b / (2 * coefficient_a);
        }
        else
        {
            type_output = two_solutions;  
            *sol_1 = (- coefficient_b + sqrt(D)) / (2 * coefficient_a);
            *sol_2 = (- coefficient_b - sqrt(D)) / (2 * coefficient_a);
        }
    }

    return type_output;
}


void output_received_solution (double sol_1, double sol_2, enum possible_outcomes type_output)
{
    switch(type_output)
    {

        case no_solutions:
            printf("это уравнение не имеет решений\n");
            break;
        case one_solution:
            printf("Это уравнение имеет одно решение %.2f\n", sol_1);
            break;
        case two_solutions:
            printf("Это уравнение имеет 2 решения x=%.2f и x=%.2f\n", sol_1, sol_2);
            break;
        case many_solutions:
            printf("Это уравнение имеет бесконечное количество решений\n");
            break;
        case incorrect_input:
            printf("Введены некорректные коэффициены\n");
            break;
        default:
            printf("Поломалось......");
            break;
    }
}
