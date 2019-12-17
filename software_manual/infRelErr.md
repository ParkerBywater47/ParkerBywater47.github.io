**Routine Name:** infRelErr 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the relative error of a vector and an approximation of said vector
using the Infinity-norm.  

**Input:** Two vectors represented as arrays of the double type.
 
**Output:** This routine returns the relative error of the vectors as "measured" by the Infinity-norm. 

**Implementation/Code:** The following is the code for infRelErr. 
   
```java 
static double infRelErr(double[] approximation, double[] exact) {
        double infExact = infNorm(exact);
        if (infExact == 0)
            throw new ArithmeticException("exact vector cannot be zero vector");
        return Math.abs(infNorm(approximation) - infExact) / infExact;
}    
```
The code for the infNorm method is [here](./infNorm.md).

**Usage/Example:** Sample output for the two vectors (0.1, 0.2, 0.3, 0.4, 0.5) and (6,7,8,9,10).  
    
    0.95

**Last Modified:** 10/30/19
