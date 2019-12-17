**Routine Name:** squareSolverInPlace   

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine solves a square linear system of equations using Gaussian elimination and 
back substitution without using extra storage space. As a consequence the value of the parameters can not be guaranteed to remain unchanged. Also, this routine performs the gaussian elimination naiively, that is, it assumes the matrix is not singular.  

**Input:** A matrix and a vector.  
 
**Output:** This routine returns the solution of the system

**Implementation/Code:** The following is the code for squareSolverInPlace.
```java 
static double[] squareSolverInPlace(double[][] A, double[] b) {
    if (A.length != b.length)
        throw new IllegalArgumentException("Incompatible dimensions");
    if (A.length == 0)
        throw new IllegalArgumentException("Matrix cannot be empty");

    for (int k = 0, r = 0; k < A.length; k++, r++) {
        if (A[r][k] != 0) {
            double pivot = A[r][k];
            for (int i = r + 1; i < A.length; i++) {
                double multiplier = A[i][k] / pivot;
                // out[r] = out[r] - multiplier * out[r-1]
                for (int j = 0; j < A[r].length; j++) {
                    A[i][j] = A[i][j] - multiplier * A[r][j];
                }
                b[i] = b[i] - multiplier * b[r];
            }
        }
    }
    return upTriangularBackSub(A, b);
}
```
The code for `upTriangularBackSub` is located [here](./upTriangularBackSub.md). 

**Usage/Example:** Sample output for the matrix A = 

      1.0000	    0.0000	    1.0000	    0.0000	
      0.0000	    5.0000	    0.0000	    1.0000	
    -25.0000	    0.0000	   -1.0000	    0.0000	
      0.0000	 -125.0000	    0.0000	   -1.0000	

and b = 

       6.0000
     -28.0000
    -102.0000
     622.0000

The output solution is 

     4.0000
    -4.9500
     2.0000
    -3.2500


**Last Modified:** 11/8/19
