**Routine Name:** L1AbsErr 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the absolute error of a vector and an approximation of said vector
using the L1-norm.  

**Input:** Two vectors represented as arrays of the double type.
 
**Output:** This routine returns the absolute error of the vectors as "measured" by the L1-norm. 

**Implementation/Code:** The following is the code for L1AbsErr. 
   
```java 
static double L1AbsErr(double[] approximation, double[] exact) {
        return Math.abs(L1Norm(approximation) - L1Norm(exact));
}
```
The code for the L1Norm method is [here](./L1Norm.md).

**Usage/Example:** Sample output for the two vectors (0.1, 0.2, 0.3, 0.4, 0.5) and (6,7,8,9,10).  
    
    38.5

**Last Modified:** 10/30/19
