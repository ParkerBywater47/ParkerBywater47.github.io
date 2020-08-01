**Routine Name:** newton

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This can be used to find the root(s) of a real-valued function of a single variable. This function must be differentiable. 

**Input:** A function pointer which points to the target function, a function pointer to the derivative of the function, an initial guess of the root, desired error tolerance, and a maximum number of iterations as Newton's method doesn't always converge. 

**Output:** This routine returns the root of the function with error less than or equal to tolerance. 

**Implementation/Code:** The following is the code for newton. 
   
```C++ 
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
```

**Usage/Example:** Below is some sample code to show the method working for the function f(x) = xcosh(x) + x^3 - pi with an initial guess of 2, tolerance of 1.0E-6, and 20 iterations at most. 
    
```C++ 
#define _USE_MATH_DEFINES   // for pi constant

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
                        newton(cosh_function, cosh_function_prime, 2, 1.0E-6, 20));
}
```
The output should be similar to mine shown below
    
    The root of x*cosh(x) + x^3 - pi is approximately 1.0963277882922402

**Last Modified:** 10/25/19
