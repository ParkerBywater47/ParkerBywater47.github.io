**Routine Name:** diagonalSolver 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the solution of a square linear system of equations (Ax = b) where 
the coeffecient matrix is diagonal.  

**Input:** A diagonal matrix and a vector. 
 
**Output:** This routine returns the solution of the system.

**Implementation/Code:** The following is the code for diagonalSolver
```java 
static double[] diagonalSolver(double[][] A, double[] b) {
    if (A.length != b.length)
        throw new IllegalArgumentException("Incompatible dimensions");
    if (A.length == 0)
        throw new IllegalArgumentException("A must be a nonempty matrix");

    double[] out = new double[A.length];
    for (int i = 0; i < out.length; i++)
        out[i] = b[i] / A[i][i];
    return out;
}
```

**Usage/Example:** Sample output for the following for A = 
    
    17.8281	    0.0000	    0.0000	    0.0000	    0.0000	
    0.0000	    2.1067	    0.0000	    0.0000	    0.0000	
    0.0000	    0.0000	  -60.9972	    0.0000	    0.0000	
    0.0000	    0.0000	    0.0000	  -12.6195	    0.0000	
    0.0000	    0.0000	    0.0000	    0.0000	  -19.3491	  

and b = 
    
    1.0000
    2.0000
    3.0000
    4.0000
    5.0000

This returns x = 

     0.0561
     0.9494
    -0.0492
    -0.3170
    -0.2584 

**Last Modified:** 11/6/19
