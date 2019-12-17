**Routine Name:** L2RelErr 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the relative error of a vector and an approximation of said vector
using the L2-norm.  

**Input:** Two vectors represented as arrays of the double type.
 
**Output:** This routine returns the relative error of the vectors as "measured" by the L2-norm. 

**Implementation/Code:** The following is the code for L2RelErr. 
   
```java 
static double L2RelErr(double[] approximation, double[] exact) {
        double L2Exact = L2Norm(exact);
        if (L2Exact == 0)
            throw new ArithmeticException("exact vector cannot be zero vector");
        return Math.abs(L2Norm(approximation) - L2Exact) / L2Exact;
}    
```
The code for the L2Norm method is [here](./L2Norm.md).

**Usage/Example:** Sample output for the two vectors (0.1, 0.2, 0.3, 0.4, 0.5) and (6,7,8,9,10).  
    
    0.9591751709536138

**Last Modified:** 10/30/19
