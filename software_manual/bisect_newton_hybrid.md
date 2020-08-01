**Routine Name:** bisect_newton_hybrid

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine returns the approximate root of a function of a single real variable. Does this by using both the 
bisection and Newton methods. Guarantees the convergence of bisection, and possibly the fast convergence of Newton's method. 

**Input:** A function and its derivative, an interval for the bisection method, and a desired error tolerance. 

**Output:** This routine returns the root of the function with an error less than tolerance. 

**Implementation/Code:** The following is the code for bisect_newton_hybrid. 
   
```C++
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
```

**Usage/Example:** Below is some sample code to show the method working for the function f(x) = xcosh(x) + x^3 - pi with a bisection interval bounded by 0 and 3, and a tolerance of 1.0E-6. 
    
```C++ 
#define _USE_MATH_DEFINES

const double cosh_function(double x)  
{
    return x * cosh(x) + pow(x, 3) - M_PI; 
}

const double cosh_function_prime(double x)
{
    return 3 * pow(x, 2) + x * sinh(x) + cosh(x);
}

int main()
{ 
    printf("%s %.16f\n", "The root of x*cosh(x) + x^3 - pi is approximately", 
                        bisect_newton_hybrid(cosh_function, cosh_function_prime, 0, 3, 1.0E-6));
}
```
The output should be similar to mine shown below
    
    The root of x*cosh(x) + x^3 - pi is approximately 1.0963277882922402

**Last Modified:** 10/25/19
