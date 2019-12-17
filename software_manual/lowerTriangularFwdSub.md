**Routine Name:** lowerTriangularBackSub

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler.

**Description/Purpose:** This routine computes the solution of a lower triangular system of equations.

**Input:** A lower triangular matrix and a right-hand side vector.

**Output:** This routine returns the solution of the system as an array of doubles.

**Implementation/Code:** The following is the code for upTriangularBackSub
```java
static double[] lowerTriangularFwdSub(double[][] A, double[] b) {
    // some error checking
    if (A.length != b.length)
        throw new IllegalArgumentException("Incompatible dimensions");
    if (A.length == 0)
        throw new IllegalArgumentException("A and b must be nonempty");

    double[] x = new double[A.length];
    x[0] = b[0] / A[0][0];
    for (int i = 1; i < A.length; i++) {
        double thatSum = 0;
        for (int j = i - 1; j >= 0; j--)
            thatSum += A[i][j] * x[j];
        x[i] = (b[i] - thatSum) / A[i][i];

    }
    return x;
}
```

**Usage/Example:** Sample output using for A =

    17.8281	    0.0000	    0.0000	    0.0000	    0.0000	
    6.0840	    2.1067	    0.0000	    0.0000	    0.0000	
    13.0353	   10.3616	  -60.9972	    0.0000	    0.0000	
    16.9078	    0.6883	  -10.9901	  -12.6195	    0.0000	
    12.1246	   -1.9126	   24.2340	    0.3836	  -19.3491	

and b =

    1.0000
    2.0000
    3.0000
    4.0000
    5.0000

The solution returned is x =

     0.0561
     0.9494
    -0.0492
    -0.3170
    -0.2584

**Last Modified:** 11/6/19

