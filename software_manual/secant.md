**Routine Name:** secant

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine implements the secant method for finding the roots of a function of a single real-valued variable. 

**Input:** A function for root finding, two initial guesses of the root, a desired error tolerance, and a maximum number of iterations as the secant method doesn't always converge. 

**Output:** This routine returns the root of the function with an error less than tolerance or the most recent approximation if the method fails to converge.

**Implementation/Code:** The following is the code for secant.
   
```C++ 
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
```

**Usage/Example:** Below is some sample code to show the method working for the function f(x) = xcosh(x) + x^3 - pi with initial guesses of 2 and 3, tolerance of 1.0E-6, and 20 iterations at most. 
    
```C++ 
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
                        secant(cosh_function, 2, 3, 1.0E-6, max_iter));
}
```
The output should be similar to mine shown below
    
    The root of x*cosh(x) + x^3 - pi is approximately 1.0963277882922402

