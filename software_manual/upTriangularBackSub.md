**Routine Name:** upTriangularBackSub 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the solution of an upper triangular system of equations.  

**Input:** An upper triangular matrix and a right-hand side vector.  
 
**Output:** This routine returns the solution of the system as an array of doubles. 

**Implementation/Code:** The following is the code for upTriangularBackSub
```java 
static double[] upTriangularBackSub(double[][] A, double[] b) {
    // some error checking
    if (A.length != b.length)
        throw new IllegalArgumentException("Incompatible dimensions");
    if (A.length == 0)
        throw new IllegalArgumentException("A and b must be nonempty");

    double[] x = new double[A.length];
    x[x.length - 1] = b[b.length - 1] / A[A.length - 1][A.length - 1];
    for (int i = x.length - 2; i >= 0; i--) {
        double thatSum = 0;
        for (int j = i + 1; j < A.length; j++)
            thatSum += A[i][j] * x[j];
        x[i] = (b[i] - thatSum) / A[i][i];

    }
    return x;
}
```

**Usage/Example:** Sample output using for A = 
    
    17.8281	    6.0840	   13.0353	   16.9078	   12.1246	
    0.0000	    2.1067	   10.3616	    0.6883	   -1.9126	
    0.0000	    0.0000	  -60.9972	  -10.9901	   24.2340	
    0.0000	    0.0000	    0.0000	  -12.6195	    0.3836	
    0.0000	    0.0000	    0.0000	    0.0000	  -19.3491 

and b = 
    
    1.0000
    2.0000
    3.0000
    4.0000
    5.0000

The solution returned is x = 
    
     0.1714
     1.2799
    -0.0933
    -0.3248
    -0.2584

**Last Modified:** 11/6/19 
