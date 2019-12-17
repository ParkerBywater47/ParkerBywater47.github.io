**Routine Name:** L1RelErr 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the relative error of a vector and an approximation of said vector
using the L1-norm.  

**Input:** Two vectors represented as arrays of the double type.
 
**Output:** This routine returns the relative error of the vectors as "measured" by the L1-norm. 

**Implementation/Code:** The following is the code for L1RelErr. 

```java 
static double L1RelErr(double[] approximation, double[] exact) {
        double L1Exact = L1Norm(exact);
        if (L1Exact == 0)
            throw new ArithmeticException("exact vector cannot be zero vector");
        return Math.abs(L1Norm(approximation) - L1Exact) / L1Exact;
}
```
The code for the L1Norm method is [here](./L1Norm.md).

**Usage/Example:** Sample output for the two vectors (0.1, 0.2, 0.3, 0.4, 0.5) and (6,7,8,9,10).
    
    0.9625

**Last Modified:** 10/30/19
