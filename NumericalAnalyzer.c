#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infi.h"

/**
 * Defines the expected arguments amount.
 */
const int ARGS_AMOUNT = 7;
/**
 * Defines the functions amount.
 */
const int FUNC_AMOUNT = 6;
/**
 * Defines the function number argument.
 */
const int FUNC_ARG = 1;
/**
 * Defines the a (lower bound of the integral) argument.
 */
const int A_ARG = 2;
/**
 * Defines the b (upper bound of the integral) argument.
 */
const int B_ARG = 3;
/**
 * Defines the n (division factor of the integral calculation) argument.
 */
const int N_ARG = 4;
/**
 * Defines the x0 (point to calculate the derivative) argument.
 */
const int X0_ARG = 5;
/**
 * Defines the h (the derivative step size) argument.
 */
const int H_ARG = 6;
/**
 * Defines an invalid value.
 */
const int INVALID = -1;
/**
 * Defines a usage massage.
 */
const char *USAGE_MSG = "Usage: NumericalAnalyzer <function number> <a> <b> <N> <x0> <h>\n";
/**
 * Defines an invalid input massage.
 */
const char *INPUT_MSG = "Invalid input\n";

/**
 * Convert a string to an integer.
 * @param str String to convert.
 * @return The converted integer if the string was legal, -1 otherwise.
 */
int stringToInt(char *str)
{
    char *end = NULL;
    int n = (int) strtol(str, &end, 0);
    if (n < 0 || strlen(end) != 0)
    {
        return INVALID;
    }
    return n;
}

/**
 * Convert a string to a double, and put the result in the given double pointer.
 * @param str String to convert.
 * @param res Pointer to put the result in.
 * @return EXIT_FAILURE if the string was illegal, EXIT_SUCCESS otherwise.
 */
int stringToDouble(char *str, double *res)
{
    char *end = NULL;
    *res = strtod(str, &end);
    if (strlen(end) != 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @param x Parameter to the function.
 * @return the result of f1 on given x.
 */
double f1(double x)
{
    return pow(x, 2) / 4;
}

/**
 * @param x Parameter to the function.
 * @return the result of f2 on given x.
 */
double f2(double x)
{
    return (-pow(x, 3) + 3 * pow(x, 2) + x - 4 * sqrt(x)) / (2 * x * sqrt(x));
}

/**
 * @param x Parameter to the function.
 * @return the result of f3 on given x.
 */
double f3(double x)
{
    return pow(sin(x), 2) - pow(cos(x), 2);
}

/**
 * @param x Parameter to the function.
 * @return the result of f4 on given x.
 */
double f4(double x)
{
    return sin(x) / (1 + cos(2 * x));
}

/**
 * @param x Parameter to the function.
 * @return the result of f5 on given x.
 */
double f5(double x)
{
    return pow(M_E, x);
}

/**
 * @param x Parameter to the function.
 * @return the result of f6 on given x.
 */
double f6(double x)
{
    return sinh(2 * x) / (M_E * pow(x, 2));
}

/**
 * check if the arguments are valid, if they were valid, it will calculate the integral and the
 * derivative on the given function with the given parameters.
 * @param argc Number of arguments the program got.
 * @param argv An array of the arguments.
 * @return EXIT_SUCCESS if running the program was successful, EXIT_FAILURE otherwise.
 */
int main(int argc, char *argv[])
{
    if (argc != ARGS_AMOUNT)
    {
        fprintf(stderr, "%s", USAGE_MSG);
        return EXIT_FAILURE;
    }
    int funcNum = stringToInt(argv[FUNC_ARG]);
    int n = stringToInt(argv[N_ARG]);
    double a, b, x0, h = 0;
    int aCheck = stringToDouble(argv[A_ARG], &a);
    int bCheck = stringToDouble(argv[B_ARG], &b);
    int x0Check = stringToDouble(argv[X0_ARG], &x0);
    int hCheck = stringToDouble(argv[H_ARG], &h);
    if (funcNum == INVALID || n == INVALID || aCheck == EXIT_FAILURE || bCheck == EXIT_FAILURE ||
        x0Check == EXIT_FAILURE || hCheck == EXIT_FAILURE || funcNum > FUNC_AMOUNT ||
        funcNum == 0 || a >= b || n == 0)
    {
        fprintf(stderr,  "%s", INPUT_MSG);
        return EXIT_FAILURE;
    }
    RealFunction funcArr[] = {NULL, f1, f2, f3, f4, f5, f6};
    RealFunction f = funcArr[funcNum];
    double integralRes = integration(f, a, b, n);
    double derivativeRes = derivative(f, x0, h);
    if (isnan(integralRes) || isnan(derivativeRes))
    {
        fprintf(stderr,  "%s", INPUT_MSG);
        return EXIT_FAILURE;
    }
    printf("Integral: %0.5f\nDerivative: %0.5f\n", integralRes, derivativeRes);
    return EXIT_SUCCESS;
}
