#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

enum possible_outcomes
{
    NO_SOLUTIONS    = 0,
    ONE_SOLUTION    = 1,
    TWO_SOLUTIONS   = 2,
    MANY_SOLUTIONS  = 3,
    INCORRECT_INPUT = 4
};

enum coefficient_numbers
{
    A = 0,
    B = 1,
    C = 2
};

double const LOW_NUMBER = 10e-5;

int input_coefficients(double coefficients[]);
void cleaning_buffer(void);

enum possible_outcomes solve_equation(double *coefficients, double *solutions);
enum possible_outcomes solve_linear_equation(double *coefficients, double *solutions);
enum possible_outcomes solve_square_equation(double *coefficients, double *solutions);
bool check_equal_zero(double number);
void test_solve_equation(void);
bool solutions_equal(double *actual, double *expected, int count);

void output_received_solution(double *solutions, enum possible_outcomes type_output);
bool get_users_answer (void);

int main()
{
    double coefficients[3] = {NAN, NAN, NAN};
    double solutions[2] = {NAN, NAN};
    enum possible_outcomes type_output = INCORRECT_INPUT;
    bool need_repetition = true;
    bool is_correctness_input = true;

    printf("Эта программа решает уравнения вида ax^2+bx+c=0\n\n");
    printf("Хотите ли вы протестировать программу перед решением?\n");
    
    if (get_users_answer ())
        test_solve_equation();

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
        printf("Хотите решить еще одно уравнение?\n");
        need_repetition = get_users_answer();

    } while (need_repetition);

    return 0;
}

int input_coefficients(double *coefficients)
{
    assert(coefficients != 0);

    printf("Введите параметры уравнения:\n");
    printf("a= ");

    if (scanf("%lf", &coefficients[A]) != 1)
    {
        cleaning_buffer();
        return false;
    }

    printf("b= ");

    if (scanf("%lf", &coefficients[B]) != 1)
    {
        cleaning_buffer();
        return false;
    }

    printf("c= ");

    if (scanf("%lf", &coefficients[C]) != 1)
    {
        cleaning_buffer();
        return false;
    }

    return true;
}

void cleaning_buffer(void)
{
    while (getchar() != '\n')
        continue;
}

enum possible_outcomes solve_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));

    if (check_equal_zero(coefficients[A]))
        return solve_linear_equation(coefficients, solutions);

    else
        return solve_square_equation(coefficients, solutions);
}

enum possible_outcomes solve_linear_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));

    if (check_equal_zero(coefficients[B]))
    {
        if (check_equal_zero(coefficients[C]))
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

enum possible_outcomes solve_square_equation(double *coefficients, double *solutions)
{
    assert(coefficients);
    assert(solutions);
    assert(coefficients != solutions);
    assert(!isnan(float (coefficients[A])));
    assert(!isnan(float (coefficients[B])));
    assert(!isnan(float (coefficients[C])));

    double discriminant = coefficients[B] * coefficients[B] - 4 * coefficients[A] * coefficients[C];

    if (discriminant < 0)
        return NO_SOLUTIONS;

    else if (check_equal_zero(discriminant))
    {
        solutions[0] = (fabs(coefficients[B])< LOW_NUMBER) ? 0 : -coefficients[B] / (2 * coefficients[A]);
        return ONE_SOLUTION;
    }

    else
    {
        solutions[0] = (fabs((-coefficients[B] + sqrt(discriminant)) / (2 * coefficients[A])) < LOW_NUMBER) ? 0 : (-coefficients[B] + sqrt(discriminant)) / (2 * coefficients[A]);
        solutions[1] = (fabs((-coefficients[B] - sqrt(discriminant)) / (2 * coefficients[A])) < LOW_NUMBER) ? 0 : (-coefficients[B] - sqrt(discriminant)) / (2 * coefficients[A]);
        return TWO_SOLUTIONS;
    }
}

void test_solve_equation()
{
    double coefficients[3] = {NAN, NAN, NAN};
    double solutions[2] = {NAN, NAN};
    enum possible_outcomes result;

    coefficients[A] = 0.0;
    coefficients[B] = 2.0;
    coefficients[C] = -4.0;
    result = solve_equation(coefficients, solutions);
    if (result != ONE_SOLUTION)
        printf ("Ошибка в тесте 1 : неверное определение типа вывода\n");
    else if (!(check_equal_zero(solutions[0] - 2.0)))
        printf ("Ошибка в тесте 1 : неверные ответы\n");

    coefficients[A] = 1.0;
    coefficients[B] = -3.0;
    coefficients[C] = 2.0;
    result = solve_equation(coefficients, solutions);
    if (result != TWO_SOLUTIONS)
        printf ("Ошибка в тесте 2 : неверное определение типа вывода\n");
    double expected[2] = {2.0, 1.0};
    if (!(solutions_equal(solutions, expected, 2)))
        printf ("Ошибка в тесте 1 : неверные ответы\n");

    coefficients[A] = 1.0;
    coefficients[B] = 0.0;
    coefficients[C] = 1.0;
    result = solve_equation(coefficients, solutions);
    if (result != NO_SOLUTIONS)
        printf ("Ошибка в тесте 3 : неверное определение типа вывода\n");

    coefficients[A] = 0.0;
    coefficients[B] = 0.0;
    coefficients[C] = 0.0;
    result = solve_equation(coefficients, solutions);
    if(result != MANY_SOLUTIONS)
        printf ("Ошибка в тесте 4 : неверное определение типа вывода\n");

    coefficients[A] = 0.0;
    coefficients[B] = 0.0;
    coefficients[C] = 1.0;
    result = solve_equation(coefficients, solutions);
    if(result != NO_SOLUTIONS)
        printf ("Ошибка в тесте 5 : неверное определение типа вывода\n");

    coefficients[A] = 1.0;
    coefficients[B] = 2.0;
    coefficients[C] = 1.0;
    result = solve_equation(coefficients, solutions);
    if(result != ONE_SOLUTION)
        printf ("Ошибка в тесте 6 : неверное определение типа вывода\n");
    if(!(check_equal_zero(solutions[0] + 1.0)))
        printf ("Ошибка в тесте 1 : неверные ответы\n");

    printf("Все тесты пройдены!\n");
}
bool solutions_equal(double *actual, double *expected, int count) 
{
    for (int i = 0; i < count; i++)
    {
        if (fabs(actual[i] - expected[i]) > LOW_NUMBER)
        {
            return false;
        }
    }
    return true;
}
bool check_equal_zero(double number)
{
    return fabs(number) < LOW_NUMBER;
}

void output_received_solution(double *solutions, enum possible_outcomes type_output)
{
    assert(solutions);
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
    const char answer_yes[5][4] = {"YES", "yes", "Yes", "y", "Y"};
    const char answer_no[5][3] = {"NO", "no", "No", "n", "N"};

    while(true)
    {
        int equality = 0;
        char answer[5];
        scanf("%s", answer);
        for (int index = 0; index < 5; index++)
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
            return false;

        else
            printf("Введите YES / NO\n");
    }
}
