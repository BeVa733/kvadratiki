#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

enum possible_outcomes
{
    NO_SOLUTIONS = 0,
    ONE_SOLUTION = 1,
    TWO_SOLUTIONS = 2,
    MANY_SOLUTIONS = 3,
    INCORRECT_INPUT = 4
};

enum coefficient_numbers
{
    A = 0,
    B = 1,
    C = 2
};

#define scan_coeff(litera, number)  printf(litera);                              \
                                                                                    \
                                    if (scanf("%lf", &coefficients[number]) != 1)   \
                                    {                                              \
                                        is_correctness_input = false;            \
                                        cleaning_buffer();                       \
                                    }                                            \

double const LOW_NUMBER = 0.0000000001;

int input_coefficients(double coefficients[]);
void cleaning_buffer(void);
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
    {
        is_correctness_input = false;
        cleaning_buffer();
    }

    else
    {
        printf("b= ");

        if (scanf("%lf", &coefficients[B]) != 1)
        {
            is_correctness_input = false;
            cleaning_buffer();
        }

        else
        {
            printf("c= ");

            if (scanf("%lf", &coefficients[C]) != 1)
            {
                is_correctness_input = false;
                cleaning_buffer();
            }
        }
    }

    if (!is_correctness_input)
        cleaning_buffer();

    return is_correctness_input;
}

void cleaning_buffer(void)
{
    while (getchar() != '\n')
        continue;
}

enum possible_outcomes solve_equation(double coefficients[], double solutions[])
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));
    assert(!isnan(float (solutions[0])));
    assert(!isnan(float (solutions[1])));

    if (fabs(coefficients[A]) < LOW_NUMBER)
        return solve_linear_equation(coefficients, solutions);

    else
        return solve_square_equation(coefficients, solutions);
}

enum possible_outcomes solve_linear_equation(double coefficients[], double solutions[])
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));
    assert(!isnan(float (solutions[0])));
    assert(!isnan(float (solutions[1])));

    if (fabs(coefficients[B]) < LOW_NUMBER)
    {
        if (fabs(coefficients[C]) < LOW_NUMBER)
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
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));
    assert(!isnan(float (solutions[0])));
    assert(!isnan(float (solutions[1])));
    
    double D = coefficients[B] * coefficients[B] - 4 * coefficients[A] * coefficients[C];

    if (D < 0)
        return NO_SOLUTIONS;

    else if (fabs(D) < LOW_NUMBER)
    {
        solutions[0] = (fabs(coefficients[B])< LOW_NUMBER) ? 0 : -coefficients[B] / (2 * coefficients[A]);
        return ONE_SOLUTION;
    }

    else
    {
        solutions[0] = (fabs((-coefficients[B] + sqrt(D)) / (2 * coefficients[A])) < LOW_NUMBER) ? 0 : (-coefficients[B] + sqrt(D)) / (2 * coefficients[A]);
        solutions[1] = (fabs((-coefficients[B] - sqrt(D)) / (2 * coefficients[A])) < LOW_NUMBER) ? 0 : (-coefficients[B] - sqrt(D)) / (2 * coefficients[A]);
        return TWO_SOLUTIONS;
    }
}

void output_received_solution(double solutions[], enum possible_outcomes type_output)
{
    assert(solutions);
    assert(!isnan(float (solutions[0])));
    assert(!isnan(float (solutions[1])));
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
            printf("Поломалось......\n");
            break;
    }
}

bool get_users_answer (void)
{
    int answer = -1;
    while(answer != 0 && answer != 1)
    {
        scanf("%d", &answer);
        cleaning_buffer();
    }

    return (answer == 1);
}
