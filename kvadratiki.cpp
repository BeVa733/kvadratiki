#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

enum possible_outcomes
{
    NO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS,
    MANY_SOLUTIONS,
    INCORRECT_INPUT
};

const int A = 0, B = 1, C = 2;

int input_coefficients(double coefficients[]);
void cleaning_excess(void);
enum possible_outcomes solve_equation(double coefficients[], double solutions[]);
enum possible_outcomes solve_linear_equation(double coefficients[], double solutions[]);
enum possible_outcomes solve_square_equation(double coefficients[], double solutions[]);
void output_received_solution(double solutions[], enum possible_outcomes type_output);
bool get_users_answer (void);

int main()
{
    double coefficients[3] = {0};
    double solutions[2] = {0};
    enum possible_outcomes type_output = INCORRECT_INPUT;
    bool need_repetition = true;
    bool is_correctness_input = true;

    printf("Эта программа решает уравнения вида ax^2+bx+c=0\n");

    do
    {
        is_correctness_input = input_coefficients(coefficients);

        if (is_correctness_input)
        {
            type_output = solve_equation(coefficients, solutions);
        }

        else
        {
            type_output = INCORRECT_INPUT;
        }

        output_received_solution(solutions, type_output);
        printf("Если хотите решить еще одно уравнение введите 1, для завершения программы введите 0\n");
        need_repetition = get_users_answer();

    } while (need_repetition);

    return 0;
}

int input_coefficients(double coefficients[])
{
    bool is_correctness_input = true;

    printf("Введите параметры уравнения:\n");
    printf("a= ");

    if (scanf("%lf", &coefficients[A]) != 1)
        is_correctness_input = false;

    else
    {
        printf("b= ");

        if (scanf("%lf", &coefficients[B]) != 1)
            is_correctness_input = false;

        else
        {
            printf("c= ");

            if (scanf("%lf", &coefficients[C]) != 1)
                is_correctness_input = false;
        }
    }

    if (!is_correctness_input)
        cleaning_excess();

    return is_correctness_input;
}

void cleaning_excess(void)
{
    while (getchar() != '\n')
        continue;
}

enum possible_outcomes solve_equation(double coefficients[], double solutions[])
{
    if (fabs(coefficients[A]) < 0.0000001)
        return solve_linear_equation(coefficients, solutions);

    else
        return solve_square_equation(coefficients, solutions);
}

enum possible_outcomes solve_linear_equation(double coefficients[], double solutions[])
{
    if (fabs(coefficients[B]) < 0.0000001)
    {
        if (fabs(coefficients[C]) < 0.0000001)
            return MANY_SOLUTIONS;

        else
            return NO_SOLUTIONS;
    }

    else
    {
        solutions[0] = -coefficients[C] / coefficients[B];
        return ONE_SOLUTION;
    }
}

enum possible_outcomes solve_square_equation(double coefficients[], double solutions[])
{
    double D = coefficients[B] * coefficients[B] - 4 * coefficients[A] * coefficients[C];

    if (D < 0)
        return NO_SOLUTIONS;

    else if (fabs(D) < 0.0000000000000001)
    {
        solutions[0] = -coefficients[B] / (2 * coefficients[A]);
        return ONE_SOLUTION;
    }

    else
    {
        solutions[0] = (-coefficients[B] + sqrt(D)) / (2 * coefficients[A]);
        solutions[1] = (-coefficients[B] - sqrt(D)) / (2 * coefficients[A]);
        return TWO_SOLUTIONS;
    }
}

void output_received_solution(double solutions[], enum possible_outcomes type_output)
{
    switch (type_output)
    {
        case NO_SOLUTIONS:
            printf("Это уравнение не имеет решений\n");
            break;
        case ONE_SOLUTION:
            printf("Это уравнение имеет одно решение %.2f\n", solutions[0]);
            break;
        case TWO_SOLUTIONS:
            printf("Это уравнение имеет 2 решения x=%.2f и x=%.2f\n", solutions[0], solutions[1]);
            break;
        case MANY_SOLUTIONS:
            printf("Это уравнение имеет бесконечное количество решений\n");
            break;
        case INCORRECT_INPUT:
            printf("Введены некорректные коэффициенты\n");
            break;
        default:
            printf("Поломалось......");
            break;
    }
}
bool get_users_answer (void)
{
    int answer = 0;

    scanf("%d", &answer);
    cleaning_excess();

    return (answer == 1);
}
