**Routine Name:** infAbsErr

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the absolute error of a vector and an approximation of said vector
using the Infinity-norm.  

**Input:** Two vectors represented as arrays of the double type.
 
**Output:** This routine returns the absolute error of the vectors as "measured" by the Infinity-norm. 

**Implementation/Code:** The following is the code for infAbsErr. 
   
```java 
static double infAbsErr(double[] approximation, double[] exact) {
        return Math.abs(infNorm(approximation) - infNorm(exact));
}
```
The code for the infNorm method is [here](./infNorm.md).

**Usage/Example:** Sample output for the two vectors (0.1, 0.2, 0.3, 0.4, 0.5) and (6,7,8,9,10).  
    
    9.5 

**Last Modified:** 10/30/19
