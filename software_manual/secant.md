**Routine Name:** secant

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine implements the secant method for finding the roots of a function of a single real-valued variable. 

**Input:** A function for root finding, two initial guesses of the root, a desired error tolerance, and a maximum number of iterations as
the secant method doesn't always converge. 

**Output:** This routine returns the root of the function with an error less than tolerance.

**Implementation/Code:** The following is the code for secant.
   
```java 
static double secant(Function<Double, Double> f, double x0, double x1, double tol, int maxIter) {
    double x_n; 
    double x_nMinus1 = x1;
    double x_nMinus2 = x0;
    double error;
    int iter = 0;
    do {
        x_n = (x_nMinus2 * f.apply(x_nMinus1) - x_nMinus1 * f.apply(x_nMinus2))
                / (f.apply(x_nMinus1) - f.apply(x_nMinus2));
        error = Math.abs(x_n - x_nMinus1);
        x_nMinus2 = x_nMinus1;
        x_nMinus1 = x_n;
        iter++;
    } while (error > tol && iter < maxIter);
    return x_n;
}
```

**Usage/Example:** Sample output for the function f(x) = x^3 + xchosh(x) - pi = 0 with initial guesses -1 and 2, a tolerance of 1.0E-06 and maxIter = 20. The function can be wrapped in a class implementing java.util.function.Function<Double, Double> like the following. 
    
```java 
class CoshFunction implements Function<Double, Double> { 
    @Override 
    public Double apply(Double x) { 
        return x * Math.cosh(x) + Math.pow(x, 3) - Math.PI; 
    }
}
```

Running the code and printing to the console from a main method can be accomplished with the following two lines of code. 

```java 
double newtonRoot = newton(new CoshFunction(), new CoshFunctionPrime(), 2, 1.0E-06, 20);
System.out.println("The root of x*cosh(x) + x^3 - pi is approximately " + newtonRoot);
```

This outputs the following to the console. 

    The root of x*cosh(x) + x^3 - pi is approximately 1.096327788304103

**Last Modified:** 10/23/19
