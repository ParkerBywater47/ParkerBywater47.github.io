**Routine Name:** LUinPlace.md 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes the LU-factorization of a matrix.   

**Input:** A square matrix.  
 
**Output:** This routine returns the important bits of the LU-factorization of the matrix given. Specifically, 
the 2-dimensional array given is overwritten with a matrix where the lower-triangular entries of the matrix are 
identical to the lower-triangular entries of L while the diagonal and upper-triangular entries are identical to U.  

**Implementation/Code:** The following is the code for LUinPlace
```java 
static void LUinPlace(double[][] A) {
    for (int k = 0, r = 0; k < A.length; k++, r++) {
        // try to find a pivot in the first column
        if (A[r][k] != 0) {
            double pivot = A[r][k];
            for (int i = r + 1; i < A.length; i++) {
                double multiplier = A[i][k] / pivot;
                // A[r] = A[r] - multiplier * A[r-1]
                for (int j = k; j < A[r].length; j++) {
                    A[i][j] = A[i][j] - multiplier * A[r][j];
                }
                A[i][k] = multiplier;
            }
        }
    }
}
```

**Usage/Example:** Sample output with A = 

    10.0668	    5.8928	   18.7510	   15.2897	    7.7862	
    6.4984	   11.7314	   20.2723	    7.5155	   18.7879	
    5.1422	   11.7827	   17.0966	   10.7515	   18.8450	
    9.8980	   10.3043	    0.8913	    9.1373	    7.5222	
    19.0364	   17.0692	   12.7061	   13.7253	    9.2764	

The output is 

    10.0668	    5.8928	   18.7510	   15.2897	    7.7862	
    0.6455	    7.9274	    8.1680	   -2.3544	   13.7617	
    0.5108	    1.1066	   -1.5204	    5.5468	   -0.3611	
    0.9832	    0.5689	   14.5966	  -85.5213	   -2.6918	
    1.8910	    0.7475	   18.9806	    1.3881	   -5.1434	

To clarify what this output is, the LU-factorization of A is L = 

    1.0000	    0.0000	    0.0000	    0.0000	    0.0000	
    0.6455	    1.0000	    0.0000	    0.0000	    0.0000	
    0.5108	    1.1066	    1.0000	    0.0000	    0.0000	
    0.9832	    0.5689	   14.5966	    1.0000	    0.0000	
    1.8910	    0.7475	   18.9806	    1.3881	    1.000

and U = 

    10.0668	    5.8928	   18.7510	   15.2897	    7.7862	
    0.0000	    7.9274	    8.1680	   -2.3544	   13.7617	
    0.0000	    0.0000	   -1.5204	    5.5468	   -0.3611	
    0.0000	    0.0000	    0.0000	  -85.5213	   -2.6918	
    0.0000	    0.0000	    0.0000	    0.0000	   -5.1434

As you can see, the diagonal and above is identical to U while everything below the diagonal is identical to L. 
   
**Last Modified:** 11/9/19
