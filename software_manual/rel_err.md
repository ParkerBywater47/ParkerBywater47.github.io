**Routine Name:** relErr

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the relative error between an approximation, p, of a number, x, defined by 
|p - x|/|x| where |y| denotes the absolute value of y. 

**Input:** Two doubles: the approximate value of a number and the exact value of said number. 

**Output:** This routine returns (as a double) the relative error of the inputs. 

**Usage/Example:** Sample output when `relErr` is wrapped in a public class named AbsoluteError and called from a main method 
defined within a public class named TestAbsoluteError. Compiled and run within the Cygwin command line environment. 
    
    $ javac RelativeError.java
    $ javac TestRelativeError.java
    $ TestRelativeError
    
    relError(98, 100) = 0.02


**Implementation/Code:** The following is the code for the routine.
    
```java 
public static double relErr(double approxVal, double exactVal) {
    return Math.abs(approxVal - exactVal) / Math.abs(exactVal);
}
```

**Last Modified:** 9/15/19
