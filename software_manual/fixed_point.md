**Routine Name:** fixedPoint

**Author:** Parker Bywater

**Language:** Java. This can be compiled using your favorite Java compiler. 

**Description/Purpose:** This routine implements a fixed point iteration for functions of a single real variable. 

**Input:** The inputs for this routine are a class which implements the java.util.Function<Double, Double> interface, an initial guess of the root of the function, a maximum number of iterations, and a desired error tolerance. 

**Output:** This routine returns an approximation of the root or complete garbage as fixed point methods are finnicky. 

**Implementation/Code:** The following is the code for fixedPoint. 
   
```java 
static double fixedPoint(Function<Double, Double> g, double initialGuess, int maxIter, double tol) {
    double lastX = initialGuess;
    double currentX;
    int iter = 0;
    double err;
    do {
        currentX = lastX + g.apply(lastX);
        err = Math.abs(currentX - lastX);
        lastX = currentX;
        iter++;
    } while (iter < maxIter && err > tol);
    return currentX;
}
```

**Usage/Example:** Suppose we wanted to find the root of f(x) = xcosh(x) + x^3 - pi. We might find this root via a fixed point iteration of the function g(x) = x - (1/8)(xcosh(x) + x^3 - pi). We might also suspect that the root is at x = 1. To accomplish this I've wrapped g(x) in the following class definition.

```java 
class CoshFunction implements Function<Double, Double> { 
    @Override 
    public Double apply(Double x) { 
        return x - (1/8) * (x * Math.cosh(x) + Math.pow(x, 3) - Math.PI); 
    }
} 
```

We can then run this from some sort of main method and obtain an approximation of the root with the following lines of code, which run the method with an initial guess of 1, a maximum number of iterations equal to 100 and an error tolerance of 1.0E-6.

```java 
double fixedPtRoot = fixedPoint(new CoshFunction(), 1, 100, 1.0E-6);
System.out.println("The root of x*cosh(x) + x^3 - pi is approximately " + fixedPtRoot);
```

This yields the following output to the console. 
   
      The root of x*cosh(x) + x^3 - pi is approximately 1.096327726394997


**Last Modified:** 10/5/19

    
