#ifndef KVVADRATIKI_H
#define KVVADRATIKI_H

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

struct test_data
     {                                       
         double test_coefficients[3];
         double test_solutions[2];
         double correct_solutions[2];
         enum possible_outcomes test_type_output;
         enum possible_outcomes correct_type_output;
     };


int input_coefficients(double coefficients[]);
void cleaning_buffer(void);

enum possible_outcomes solve_equation(double *coefficients, double *solutions);
enum possible_outcomes solve_linear_equation(double *coefficients, double *solutions);
enum possible_outcomes solve_square_equation(double *coefficients, double *solutions);
bool check_equal_zero(double number);
void test_solve_equation(void);
bool check_solutions(double *test_solutions, double *correct_solutions);
void output_received_solution(double *solutions, enum possible_outcomes type_output);
bool get_users_answer (void);

#endif
