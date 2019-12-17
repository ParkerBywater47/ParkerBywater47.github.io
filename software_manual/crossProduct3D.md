**Routine Name:** crossProduct3D	 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the cross product of two 3-dimensional vectors.  

**Input:** Two 3-dimensional vectors represented as arrays of doubles.  
 
**Output:** This routine returns the cross product of the two vectors.  

**Implementation/Code:** The following is the code for crossProduct3D. 
   
```java 
static double[] crossProduct3D(double[] vec1, double[] vec2) {
    if (!(vec1.length == vec2.length && vec1.length == 3))
        throw new IllegalArgumentException("Vectors must be 3-dimensional");

    double[] out = new double[3];
    out[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    out[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    out[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
    return out;
}
```

**Usage/Example:** Sample output for (1, 0, 0) and (0, 1, 0).   

    [0.0, 0.0, 1.0]

**Last Modified:** 11/1/19
