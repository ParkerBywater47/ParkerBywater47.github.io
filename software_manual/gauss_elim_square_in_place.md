**Routine Name:** gaussElimSquareInPlace 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine performs gaussian elimination on a square matrix by performing in place row operations. 
Specifically, it overwrites the array given. 

**Input:** A square matrix represented as a 2-dimensional array. This array is overwritten to contain the reduced form.  
 
**Output:** This routine returns the row echelon form of the matrix. 

**Implementation/Code:** The following is the code for gaussElimSquare.
```java 
static void gaussElimSquareInPlace(double[][] A) {
    if (A.length == 0)
        throw new IllegalArgumentException("Matrix cannot be empty");

    for (int k = 0, r = 0; k < A.length; k++, r++) {
        if (A[r][k] != 0) {
            double pivot = A[r][k];
            for (int i = r + 1; i < A.length; i++) {
                double multiplier = A[i][k] / pivot;
                // A[r] = A[r] - multiplier * A[r-1]
                for (int j = 0; j < A[r].length; j++) {
                    A[i][j] = A[i][j] - multiplier * A[r][j];
                }
            }
        }
        else {
            // try to find a pivot in other rows of column k
            int i ;
            for (i = 0; i < A.length; i++) {
                if (A[i][k] != 0) {
                    double[] temp = A[r];
                    A[r] = A[i];
                    A[i] = temp;
                    // decrement the values of r and k because the for loop will increment them and skip the 
                    // row which was just swapped
                    r--;
                    k--;
                    break;
                }
            }
            // check for an unsuccessful pivot search and decrement r because the outer for loop will
            // increment r and skip a row
            if (i == A.length)
                r--;
        }
    }
}
```

**Usage/Example:** Sample output when the matrix below is passed as input.  
    
    3.6578	    4.3459	    6.6881	   10.1399	    0.9815	
    1.7441	   15.8919	    0.8436	   20.9181	   15.2195	
    19.2112	   12.3691	   16.7053	   14.6983	    0.8400	
    18.3011	   18.6141	   13.1689	    6.6432	    9.8854	
    0.7692	   18.4410	   18.2696	   15.0529	   10.7585
     
The values of the array are now

    3.6578	    4.3459	    6.6881	   10.1399	    0.9815	
    0.0000	   13.8197	   -2.3453	   16.0833	   14.7515	
    0.0000	    0.0000	  -20.1955	  -26.3885	    6.8461	
    0.0000	    0.0000	    0.0000	  -13.2366	    1.2561	
    0.0000	    0.0000	   -0.0000	    0.0000	   -4.6013 

**Last Modified:** 11/6/19 
