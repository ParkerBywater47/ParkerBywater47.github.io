**Routine Name:** infNorm 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the length of a vector using the Infinity-norm.  

**Input:** A vector represented as an array of the double type.  
 
**Output:** This routine returns the length of the vector given as input. If said vector is an empty array, 
`IllegalArgumentException` is thrown.  

**Implementation/Code:** The following is the code for infNorm. 
   
```java 
static double infNorm(double[] vec) {
        if (vec.length == 0)
            throw new IllegalArgumentException("Vector must have length > 0");
        double max = Math.abs(vec[0]);
        for (int i = 1; i < vec.length; i++) {
            double next = Math.abs(vec[i]);
            if (next > max)
                max = next;
        }
        return max;
    }
```

**Usage/Example:** Sample output for the vector (1,2,3,4,5) 

    5

**Last Modified:** 10/30/19 
