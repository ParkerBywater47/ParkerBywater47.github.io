**Routine Name:** newton

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine implements Newton's method for functions of a single real-valued variable. 

**Input:** A function for root-finding, the derivative of the function, an initial guess of the root, desired error tolerance, and a maximum number of iterations as Newton's method doesn't always converge. 

**Output:** This routine returns the root of the function with error less than or equal to tolerance. 

**Implementation/Code:** The following is the code for newton. 
   
```java 
static double newton(Function<Double, Double> f, Function<Double, Double> fPrime, double initial, double tol, int maxIter)
    int iter = 0;
    double lastX = initialGuess;
    double fVal = f.apply(lastX);
    double fPrimeVal = fPrime.apply(lastX);
    double error = 2 * tol;
    double currX = lastX;
    while (error > tol && iter < maxIter && Math.abs(fPrimeVal) != 0) {
        currX = lastX - fVal / fPrimeVal;
        error = Math.abs(currX - lastX);
        lastX = currX;
        fVal = f.apply(currX);
        fPrimeVal = fPrime.apply(currX);
        iter++;
    }
    return currX;
 }
```

**Usage/Example:** Sample output for the function f(x) = xcosh(x) + x^3 - pi with an initial guess of 2, tol = 1.0E-6, and maxIter = 20. The function and its derivative can be wrapped in a class implementing `java.util.function.Function<Double, Double>` like the following. 
    
```java 
class CoshFunction implements Function<Double, Double> { 
    @Override 
    public Double apply(Double x) { 
        return x * Math.cosh(x) + Math.pow(x, 3) - Math.PI; 
    }
}

class CoshFunction implements Function<Double, Double> {
    @Override
    public Double apply(Double x) {
        return 3 * Math.pow(x, 2) + x * Math.sinh(x) + Math.cosh(x);
    }
}
```

Running the code and printing to the console from a main method can be accomplished with the following two lines of code. 

```java 
double newtonRoot = newton(new CoshFunction(), new CoshFunctionPrime(), 2, 1.0E-06, 20);
System.out.println("The root of x*cosh(x) + x^3 - pi is approximately " + newtonRoot);
```

This outputs the following to the console. 
    
    The root of x*cosh(x) + x^3 - pi is approximately 1.0963277882922402

**Last Modified:** 10/25/19
