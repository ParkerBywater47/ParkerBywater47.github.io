**Routine Name:** bisection 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine finds approximate roots of a function of a single real variable using the bisection method. This requires a continuous function and an interval [a,b] such that f(a) \* f(b) <= 0.  

**Input:** A continuous function, appropriate values of a and b as described above, and an error tolerance. 

**Output:** This routine returns the root of the function with an error less than or equal to the specified tolerance. 

**Implementation/Code:** The following is the code for bisection. 
   
```java 
static double bisection(Function<Double, Double> f, double a, double b, double tol) {
    if (f.apply(a) * f.apply(b) > 0)
        throw new IllegalArgumentException("f(a) * f(b) must be < 0");
    else if (f.apply(a) == 0)
        return a;
    else if (f.apply(b) == 0)
        return b;

    double c = (a + b) / 2;
    int maxIter = (int) (-Math.log10(tol / (b - a)) / Math.log10(2)) + 1;
    for (int i = 0; i < maxIter; i++) {
        if (f.apply(c) == 0)
            return c;
        else if (f.apply(a) * f.apply(c) < 0)
            b = c;
        else
            a = c;
        c = (a + b) / 2;
    }
    return c;
}
```

**Usage/Example:** Sample output for the function f(x) = xcosh(x) + x^3 - pi with a = -100, b = 100, and tol = 1.0E-6. The function can either be wrapped in a class implementing java.util.function.Function<Double, Double> like the following. 
    
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
 double bisectRoot = bisection(new CoshFunction(), -100, 100, 1.0E-6);
 System.out.println("The root of x*cosh(x) + x^3 - pi is approximately " + bisectRoot);
```
This outputs the following to the console. 
    
    The root of x*cosh(x) + x^3 - pi is approximately 1.0963277882922142

**Last Modified:** 10/6/19
