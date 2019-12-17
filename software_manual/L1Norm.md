**Routine Name:** L1Norm 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the L1-norm of a vector.   

**Input:** A vector represented as an array of type double.  
 
**Output:** This routine returns the L1Norm of the vector. Throws IllegalArgumentException if an empty vector is 
given as input.  

**Implementation/Code:** The following is the code for L1Norm. 
   
```java 
static double L1Norm(double[] vec) {
        if (vec.length == 0)
            throw new IllegalArgumentException("Vector must have length > 0");
        double out = 0;
        for (int i = 0; i < vec.length; i++) {
            out += vec[i];
        }
        return out;
    }
```

**Usage/Example:** Sample output for the vector (1,2,3,4,5) 

    10 

**Last Modified:** 10/30/2019
