**Routine Name:** dotProduct 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the dotProduct of two vectors.  

**Input:** Two vectors represented as arrays of doubles. 
 
**Output:** This routine returns the dot product of two vectors. 

**Implementation/Code:** The following is the code for dotProduct. 
   
```java 
static double dotProduct(double[] vec1, double[] vec2) {
    if (vec1.length != vec2.length)
	throw new IllegalArgumentException("Vectors must be of the same dimension");

    double sum = 0;
    for (int i = 0; i < vec1.length; i++)
        sum += vec1[i] * vec2[i]; 
    return sum;
}
```

**Usage/Example:** Sample output for the vectors (0.1, 0.2, 0.3, 0.4, 0.5) and (6, 7, 8, 9, 10). 

    13.0

**Last Modified:** 11/1/19 
