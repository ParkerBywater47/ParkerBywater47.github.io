**Routine Name:** L2Norm 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the length of a vector using the L2-norm for a given vector.  

**Input:** A vector represented as an array of type double.  
 
**Output:** This routine returns the length of the vector given.  

**Implementation/Code:** The following is the code for L2Norm
   
```java 
static double L2Norm(double[] vec) {
        if (vec.length == 0)
            throw new IllegalArgumentException("Vector must have length > 0");
        double sum = 0;
        for (int i = 0; i < vec.length; i++)
            sum += Math.pow(vec[i], 2);
        return Math.sqrt(sum);
    }
```

**Usage/Example:** Sample output for the vector (1.1, 1.4, 1.8). 
	
	2.5317977802344327


**Last Modified:** 10/30/19
