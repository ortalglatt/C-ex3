#include <assert.h>
#include "infi.h"

 /**
  * Computes the numerical integration for the given rationale function at the given numbers range,
  * based on Riemann sums
  * @param func A function that gets a double and return a double.
  * @param a The lower bound of the integral.
  * @param b The upper bound of the integral.
  * @param n The division factor.
  * @return The integration result.
  */
double integration(RealFunction func, double a, double b, unsigned int n)
{
    assert(a < b);
    assert(n > 0);
    double result = 0;
    double devFactor = (b - a) / n;
    double curValue = a;
    double mid = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        mid = (curValue + (curValue + devFactor)) / 2;
        result += func(mid) * devFactor;
        curValue += devFactor;
    }
    return result;
}

 /**
  * Computes a numerical derivative for the given rationale function at the point, for a given
  * epsilon.
  * @param func A function that gets a double and return a double.
  * @param x0 The point we want to calculate the derivative on.
  * @param h The derivative step size.
  * @return The differentiate.
  */
double derivative(RealFunction func, double x0, double h)
{
    assert(h > 0);
    double result = func(x0 + h) - func(x0 - h);
    return result / (2*h);
}
