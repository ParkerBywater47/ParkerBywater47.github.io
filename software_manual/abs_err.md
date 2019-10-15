**Routine Name:** absErr

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the absolute error between an approximation, p, of a number, x, defined by |p - x| where 
|y| denotes the absolute value of y. 

**Input:** Two doubles: the approximate value of a number and the exact value of said number. 

**Output:** This routine returns (as a double) the absolute error of the inputs. 

**Usage/Example:** Sample output when `absErr` is wrapped in a public class named AbsoluteError and called from a main method 
defined within another public class named TestAbsoluteError. Compiled and run within the Cygwin command line environment. 
    
    $ javac AbsoluteError.java
    $ javac TestAbsoluteError.java
    $ TestAbsoluteError
    
    absError(4.5, 5) = 0.5


**Implementation/Code:** The following is the code for the routine.
    
```java 
public static double absErr(double approxVal, double exactVal) {
    return Math.abs(approxVal - exactVal);
}
```

**Last Modified:** 9/15/19
