**Routine Name:** gaussElimSquare 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine performs gaussian elimination on a square matrix.  

**Input:** A square matrix represented as a 2-dimensional array.  
 
**Output:** This routine returns the row echelon form of the matrix as a new 2-dimensional array.   

**Implementation/Code:** The following is the code for gaussElimSquare.
```java 
static double[][] gaussElimSquare(double[][] A) {
    if (A.length == 0)
        throw new IllegalArgumentException("Matrix cannot be empty");
    
    double[][] out = new double[A.length][A.length] ; 
    for (int i = 0; i < A.length; i++)
        System.arraycopy(A[i], 0, out[i], 0, A.length); 
    
    for (int k = 0, r = 0; k < out.length; k++, r++) {
        if (out[r][k] != 0) {
            double pivot = out[r][k];
            for (int i = r + 1; i < out.length; i++) {
                double multiplier = out[i][k] / pivot;
                // out[r] = out[r] - multiplier * out[r-1]
                for (int j = 0; j < out[r].length; j++) {
                    out[i][j] = out[i][j] - multiplier * out[r][j];
                }
            }
        }
        else {
            // try to find a pivot in other rows of column k
            int i ;
            for (i = 0; i < out.length; i++) {
                if (out[i][k] != 0) {
                    double[] temp = out[r];
                    out[r] = out[i];
                    out[i] = temp;
                    // decrement the values of r and k because the for loop will increment them and skip the 
                    // row which was just swapped
                    r--;
                    k--;
                    break;
                }
            }
            // check for an unsuccessful pivot search and decrement r because the outer for loop will
            // increment r and skip a row
            if (i == out.length)
                r--;
        }
    }
    return out; 
}
```

**Usage/Example:** Sample output when the matrix below is passed as input.  
    
    3.6578	    4.3459	    6.6881	   10.1399	    0.9815	
    1.7441	   15.8919	    0.8436	   20.9181	   15.2195	
    19.2112	   12.3691	   16.7053	   14.6983	    0.8400	
    18.3011	   18.6141	   13.1689	    6.6432	    9.8854	
    0.7692	   18.4410	   18.2696	   15.0529	   10.7585
     
The folowing is returned 

    3.6578	    4.3459	    6.6881	   10.1399	    0.9815	
    0.0000	   13.8197	   -2.3453	   16.0833	   14.7515	
    0.0000	    0.0000	  -20.1955	  -26.3885	    6.8461	
    0.0000	    0.0000	    0.0000	  -13.2366	    1.2561	
    0.0000	    0.0000	   -0.0000	    0.0000	   -4.6013 

**Last Modified:** 11/6/19 
