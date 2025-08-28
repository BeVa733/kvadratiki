#ifndef KVVADRATIKI_H
#define KVVADRATIKI_H

enum possible_outcomes
{
    NO_SOLUTIONS    = 0,
    ONE_SOLUTION    = 1,
    TWO_SOLUTIONS   = 2,
    MANY_SOLUTIONS  = 3,
    ERROR_SOLUTIONS = 4
};

enum type_answer
{
    NO      = 0,
    YES     = 1,
    ANOTHER = 3
};

enum coefficient_numbers
{
    A = 0,
    B = 1,
    C = 2
};

double const LOW_NUMBER = 10e-5;

struct coeff_identification
{
    char litera[3];
    enum coefficient_numbers number[3];
};

struct test_data
{
     double test_coefficients[3];
     double test_solutions[2];
     double correct_solutions[2];
     enum possible_outcomes test_n_roots;
     enum possible_outcomes correct_n_roots;
};

void welcome(void);

int input_coefficients(double coefficients[]);
bool input_one_coefficient(coeff_identification *identificators, int i, double *coefficients);
void cleaning_buffer(void);

enum possible_outcomes solve_equation(double *coefficients, double *solutions);
enum possible_outcomes solve_linear_equation(double *coefficients, double *solutions);
enum possible_outcomes solve_square_equation(double *coefficients, double *solutions);
bool check_equal_zero(double number);

void output_received_solution(double *solutions, enum possible_outcomes type_output);
bool get_users_answer (void);

void test_solve_equation(void);
bool one_test(test_data *tests, int i);
bool check_solutions(double *test_solutions, double *correct_solutions);

#endif
