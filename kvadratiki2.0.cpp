#include<TXLib.h>
#include<stdio.h>
#include<math.h>

int input_coefficients (double *coefficient_a,double *coefficient_b,double *coefficient_c);
void output_received_solution (double sol_1, double sol_2, int type_of_output);
int the_quadratic_equation_solver (double coefficient_a,double coefficient_b,double coefficient_c, double *sol_1, double *sol_2);

int main(void)
{
    double coefficient_a = 0;
    double coefficient_b = 0;
    double coefficient_c = 0;
    double sol_1 = 0;
    double sol_2 = 0;
    int need_for_repetition = 1;
    int check_correctness_input, type_of_output;
    printf("Эта программа решает уравнения вида ax^2+bx+c=0\n");

    do
    {
        check_correctness_input = 1;
        printf("Введите параметры уравнения:\n");
        check_correctness_input = input_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);

        if (check_correctness_input == 1)
            type_of_output = the_quadratic_equation_solver(coefficient_a, coefficient_b, coefficient_c, &sol_1, &sol_2);
        else
            type_of_output = -1;

        output_received_solution(sol_1, sol_2, type_of_output);

        printf("Если хотите решить еще одно уравнение введите 1, для завершения программы введите 0\n");
        scanf("%d", &need_for_repetition);
    }while(need_for_repetition);

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


int the_quadratic_equation_solver (double coefficient_a,double coefficient_b,double coefficient_c, double *sol_1, double *sol_2)
{
    double D = 0;
    int type_of_output;

    if (coefficient_a == 0)
    {
        if (coefficient_b ==0)
        {
            if (coefficient_c == 0)
                type_of_output = 0;
            else
               type_of_output = 1;
        }
        else
        {
            type_of_output = 2;
            *sol_1 = -coefficient_c/coefficient_b;
        }
    }
    else
    {
        D = coefficient_b*coefficient_b-4*coefficient_a*coefficient_c;
        if (D<0)
            type_of_output = 3;
        else if (D==0)
        {
            type_of_output = 4;
            *sol_1 = -coefficient_b/(2*coefficient_a);
        }
        else
        {
            type_of_output = 5;
            *sol_1 = (-coefficient_b+sqrt(D))/(2*coefficient_a);
            *sol_2 = (-coefficient_b-sqrt(D))/(2*coefficient_a);
        }
    }

    return type_of_output;
}


void output_received_solution (double sol_1, double sol_2, int type_of_output)
{
    switch(type_of_output)
    {
        case -1:
            printf("Введены некорректные коэффициены\n");
            break;
        case 0:
            printf("Это уравнение имеет бесконечное количество решений\n");
            break;
        case 1:
        case 3:
            printf("это уравнение не имеет решений\n");
            break;
        case 2:
        case 4:
            printf("Это уравнение имеет одно решение %.2f\n", sol_1);
            break;

        case 5:
            printf("Это уравнение имеет 2 решения x=%.2f и x=%.2f\n", sol_1, sol_2);
            break;
        default:
            printf("Что-то поломалось.....\n");
            break;
    }
}
