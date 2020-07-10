**Routine Name:** bisection 

**Author:** Parker Bywater

**Language:** C++. 

**Description/Purpose:** This routine finds approximate roots of a function of a single real variable using the bisection method. This requires a continuous function (f) and an interval [a,b] such that f(a) \* f(b) <= 0.  

**Input:** A continuous function passed as a function pointer, appropriate values of a and b as described above, and an error tolerance. 

**Output:** This routine returns the root of the function with an error less than or equal to the specified tolerance. 

**Exceptions:** Throws `std::invalid_argument` if f(a) * f(b) > 0 as this invalidates the assumptions needed for the bisection method.  

**Implementation/Code:** The following is the code for bisection. 
   
```C++ 
#include <math.h>
#include <stdexcept>

#define _USE_MATH_DEFINES   // for pi constant


double cosh_function(double x); 

double bisection(double (*f)(double), double a, double b, double tol) 
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
```

**Usage/Example:** Below is sample code that can be added to the above to show the bisection method working on the function f(x) = xcosh(x) + x^3 - pi with a = -100, b = 100, and tol = 1.0E-6.  
    
```C++
double cosh_function(double x) 
{
    return x * cosh(x) + pow(x, 3) - M_PI; 
}


int main()
{ 
    printf("%s %.16f\n", "The root of x*cosh(x) + x^3 - pi is approximately", bisection(cosh_function, -100, 100, 1.0E-6));
}
```
The output should be similar to mine shown below
    
    The root of x*cosh(x) + x^3 - pi is approximately 1.0963277882922142

**Last Modified:** 10/6/19
