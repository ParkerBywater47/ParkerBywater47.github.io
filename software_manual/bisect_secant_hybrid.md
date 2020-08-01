**Routine Name:** bisectSecantHybrid

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine returns the approximate root of a function of a single real variable. Does this by using both the 
bisection and secant methods. Guarantees the convergence of bisection, and possibly the rate of convergence of the secant method. 

**Input:** A function, an interval for bisection, and a desired error tolerance.

**Output:** This routine returns the roots of the function with an error less than tolerance. 

**Implementation/Code:** The following is the code for bisectSecantHybrid. 
   
```java 
static double bisectSecantHybrid(Function<Double, Double> f, Function<Double, Double> fPrime, double a, double b, double tol) {
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
    boolean trySecant = true;
    int timesToBisect = 4;
    int timesBisected = 0;
    for (int i = 0; i < maxIter; i++) {
        if (trySecant) {
            double x_n;
            double x_nMinus1 = a;
            double x_nMinus2 = c;

            // compute the denominator separately to prevent division by zero
            double denominator = (f.apply(x_nMinus1) - f.apply(x_nMinus2));
            double err;
            int secIter = 0;
            // use newton's method as long as iterates stay in [a,b] and we don't exceed 1/4 of maxIter
            while (secIter < maxIter && denominator != 0) {
                x_n = (x_nMinus2 * f.apply(x_nMinus1) - x_nMinus1 * f.apply(x_nMinus2))
                        / denominator;
                err = Math.abs(x_n - x_nMinus1);
                x_nMinus2 = x_nMinus1;
                x_nMinus1 = x_n;
                denominator = (f.apply(x_nMinus1) - f.apply(x_nMinus2));

                // modify the interval if possible
                if (a <= x_n && x_n <= b) {
                    if (f.apply(a) < 0) {
                        if (f.apply(x_n) < 0)
                            a = x_n;
                        else if (f.apply(x_n) > 0)
                            b = x_n;
                    } else {
                        if (f.apply(x_n) > 0)
                            a = x_n;
                        else if (f.apply(x_n) < 0)
                            b = x_n;
                    }
                } else
                    break;
                if (err < tol) {
                    return x_n;
                }
                secIter++;
                trySecant = false;
                timesBisected = 0;


            }
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
        trySecant = timesBisected == timesToBisect;
    }
    return c;
}
```

**Usage/Example:** Sample output for the function f(x) = xcosh(x) + x^3 - pi with a = -10, b = 10, and tol = 1.0E-6. The function can either be wrapped in a class implementing java.util.function.Function<Double, Double> like the following. 
    
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
double bisectSecantRoot = bisectSecantHybrid(new CoshFunction(), -10, 10, 1.0E-06);
System.out.println("The root of x*cosh(x) + x^3 - pi is approximately " + bisectSecantRoot);
```

This outputs the following to the console. 
    
    The root of x*cosh(x) + x^3 - pi is approximately 1.0963277882922389

**Last Modified:** 10/25/19
