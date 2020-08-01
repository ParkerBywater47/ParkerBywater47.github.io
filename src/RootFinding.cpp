#include "RootFinding.hpp"

#include <stdexcept>
#include <omp.h>
#include <utility>
#include <math.h>

#include <iostream>

#define _USE_MATH_DEFINES

const double cosh_function(double x)  
{
    return x * cosh(x) + pow(x, 3) - M_PI; 
}

const double cosh_function_prime(double x)
{
    return 3 * pow(x, 2) + x * sinh(x) + cosh(x);
}

double bisect_newton_hybrid(const double (*f)(double), const double (*df)(double), double a, double b, const double tol) 
{
    // check that the input is valid and for the possibility that f(a) or f(b) are zero
    if (f(a) * f(b) > 0)
        throw std::invalid_argument("f(a) * f(b) must be < 0");
    else if (f(a) == 0)
        return a;
    else if (f(b) == 0)
        return b;

    // start bisection
    double c = (a + b) / 2.0;
    const int max_iter = (int) (-log10(tol / (b - a)) / log10(2));

    // variables to implement logic of bisecting 4 times when newton method fails
    bool try_newton = true;
    const int times_to_bisect = 4;
    int times_bisected = 0;
    for (int i = 0; i < max_iter; i++) 
    {
        if (try_newton) 
        {
            double x0 = c;
            double f_prime_val; 
            double x1;
            double err;
            int newt_iter = 0;
            // use newton's method as long as iterates stay in [a,b] and we don't exceed 1/4 of max_iter
            while (newt_iter <  max_iter / 4 && f_prime_val != 0) 
            {
                f_prime_val = df(x0);
                x1 = x0 - f(x0) / f_prime_val;
                err = fabs(x1 - x0);
                x0 = x1;

                // modify the interval if possible
                if (a <= x1 && x1 <= b) 
                {
                    if (f(a) < 0) 
                    {
                        if (f(x1) < 0)
                            a = x1;
                        else if (f(x1) > 0)
                            b = x1;
                    }
                    else 
                    {
                        if (f(x1) > 0)
                            a = x1;
                        else if (f(x1) < 0)
                            b = x1;
                    }
                }
                else
                    break;
                if (err < tol) 
                {
                    return x1;
                }
                newt_iter++;
            }
            try_newton = false;
            times_bisected = 0;
        }

        // bisection code
        if (f(c) == 0)
            return c;
        else if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
        c = (a + b) / 2;
        times_bisected++;
        try_newton = times_bisected == times_to_bisect;
    }
    return c;
}

double secant(const double (*f)(double), const double x0, const double x1, const double tol, const int max_iter) 
{
    double x_n; 
    double x_nMinus1 = x1;
    double x_nMinus2 = x0;
    double error;
    int iter = 0;
    do {
        x_n = (x_nMinus2 * f(x_nMinus1) - x_nMinus1 * f(x_nMinus2))
                / (f(x_nMinus1) - f(x_nMinus2));
        error = fabs(x_n - x_nMinus1);
        x_nMinus2 = x_nMinus1;
        x_nMinus1 = x_n;
        iter++;
    } while (error > tol && iter < max_iter);
    return x_n;
}

double bisection(const double (*f)(double), double a, double b, const double tol) 
{
    if (f(a) * f(b) > 0) 
    { 
        throw std::invalid_argument("f(a) * f(b) must be <= 0");
    }
    else if (f(a) == 0) 
        return a; 
    else if (f(b) == 0)
        return b;

    double c = (a + b) / 2;
    int max_iter = (int) (-log10(tol / (b - a)) / log10(2)) + 1; 
    for (int i = 0; i < max_iter; i++) { 
        if (f(a) * f(c) < 0)
            b = c;
        else if (f(b) * f(c) < 0)
            a = c; 
        else    // f(c) == 0 -- very unlikely to happen
            return c;
        c = (a + b) / 2; 
    }
    return c; 
}


double newton(const double (*f)(double), const double (*df)(double), const double initial, const double tol, const int max_iter)
{
    double last_x = initial;
    double f_val = f(last_x);
    double df_val = df(last_x);
    double curr_x = last_x;
    double error = 2 * tol;
    int iter = 0;
    while (error > tol && iter < max_iter && fabs(df_val) != 0) 
    {
        curr_x = last_x - f_val / df_val;
        error = fabs(curr_x - last_x);
        last_x = curr_x;
        f_val = f(curr_x);
        df_val = df(curr_x);
        iter++;
    }
    return curr_x;
 }
