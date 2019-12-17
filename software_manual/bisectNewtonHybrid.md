**Routine Name:** bisectNewtonHybrid

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine returns the approximate root of a function of a single real variable. Does this by using both the 
bisection and Newton methods. Guarantees the convergence of bisection, and possibly the fast convergence of Newton's method. 

**Input:** A function and its derivative, an interval for the bisection method, and a desired error tolerance. 

**Output:** This routine returns the root of the function with an error less than tolerance. 

**Implementation/Code:** The following is the code for bisectNewtonHybrid. 
   
```java 
static double bisectNewtonHybrid(Function<Double, Double> f, Function<Double, Double> fPrime, double a, double b, double tol) {
    // check that the input is valid and for the possibility that f(a) or f(b) are zero
    if (f.apply(a) * f.apply(b) > 0)
        throw new IllegalArgumentException("f(a) * f(b) must be < 0");
    else if (f.apply(a) == 0)
        return a;
    else if (f.apply(b) == 0)
        return b;

    // start bisection
    double c = (a + b) / 2;
    int maxIter = (int) (-Math.log10(tol / (b - a)) / Math.log10(2));

    // variables to implement logic of bisecting 4 times when newton method fails
    boolean tryNewton = true;
    int timesToBisect = 4;
    int timesBisected = 0;
    for (int i = 0; i < maxIter; i++) {
        if (tryNewton) {
            double x0 = c;
            double fPrimeVal = f.apply(x0);
            double x1;
            double err;
            int newtIter = 0;
            // use newton's method as long as iterates stay in [a,b] and we don't exceed 1/4 of maxIter
            while (newtIter <  maxIter / 4 && fPrimeVal != 0) {

                x1 = x0 - f.apply(x0) / fPrimeVal;
                err = Math.abs(x1 - x0);
                fPrimeVal = f.apply(x0);
                x0 = x1;

                // modify the interval if possible
                if (a <= x1 && x1 <= b) {
                    if (f.apply(a) < 0) {
                        if (f.apply(x1) < 0)
                            a = x1;
                        else if (f.apply(x1) > 0)
                            b = x1;
                    }
                    else {
                        if (f.apply(x1) > 0)
                            a = x1;
                        else if (f.apply(x1) < 0)
                            b = x1;
                    }
                }
                else
                    break;
                if (err < tol) {
                    return x1;
                }
                newtIter++;
            }
            tryNewton = false;
            timesBisected = 0;
        }

        // bisection code
        if (f.apply(c) == 0)
            return c;
        else if (f.apply(a) * f.apply(c) < 0)
            b = c;
        else
            a = c;
        c = (a + b) / 2;
        timesBisected++;
        tryNewton = timesBisected == timesToBisect;
    }
    return c;
}
```

**Usage/Example:** Sample output for the function f(x) = xcosh(x) + x^3 - pi with an initial guess of 2 and a tolerance of 1.0E-6. The function and its derivative can be wrapped in a class implementing `java.util.function.Function<Double, Double>` like the following. 
    
```java 
class CoshFunction implements Function<Double, Double> { 
    @Override 
    public Double apply(Double x) { 
        return x * Math.cosh(x) + Math.pow(x, 3) - Math.PI; 
    }
}

class CoshFunctionPrime implements Function<Double, Double> {
    @Override
    public Double apply(Double x) {
        return 3 * Math.pow(x, 2) + x * Math.sinh(x) + Math.cosh(x);
    }
}
```

Running the code and printing to the console from a main method can be accomplished with the following two lines of code. 

```java 
double bisectNewtonRoot = bisectNewtonHybrid(new CoshFunction(), new CoshFunctionPrime(), -1,2, 1.0E-06);
System.out.println("The root of x*cosh(x) + x^3 - pi is approximately " + bisectNewtonRoot);
```

This gives the following output. 

    The root of x*cosh(x) + x^3 - pi is approximately 1.0963280200958252

**Last Modified:** 10/25/19
