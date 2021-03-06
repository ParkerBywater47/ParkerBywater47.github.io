**Routine Name:** gauss_elim_square_in_place 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine performs gaussian elimination on a square matrix. Swaps rows when necessary. This routine acts "in place", that is, it will change
the data stored in the arguments given. 

**Input:** A square matrix as an instance of [this](../src/Matrix.cpp) Matrix class. The contents of this object are overwritten to contain the reduced form.  
 
**Output:** This routine returns the row reduced form of the matrix. 

**Exceptions:** Throws `std::invalid_argument` if the matrix given is not square.

**Implementation/Code:** The following is the code for gauss_elim_square_in_place. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   


```C++ 
void gauss_elim_square_in_place(Matrix& A)
{
    const int n = A.get_num_rows(); 
    if (n != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

    // elimination code
    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        // check that this entry is not zero as pivots cannot be zero
        if (A[r][k] != 0) 
        {
            double pivot = A[r][k];

            // eliminate entries below the pivot
            # pragma omp parallel for
            for (int i = r + 1; i < n; i++) 
            {
                double multiplier = A[i][k] / pivot;

                // if the multiplier is zero this for loop does no work
                if (multiplier != 0) 
                {
                    // do the row subtraction
                    for (int j = 0; j < n; j++) 
                    {
                        A[i][j] = A[i][j] - multiplier * A[r][j];
                    }
                }
            }
        }
        else 
        {
            // try to find a pivot in other rows of column k
            int i;
            for (i = r + 1; i < n; i++) 
            {
                if (A[i][k] != 0) 
                {
                    // swap rows of the matrix
                    A.swap_rows(r, i); 

                    // decrement the values of r and k because the outermost for loop will increment
		    // them and skip elimination using the row which was just swapped
                    r--;
                    k--;
                    break;
                }
            }
            // check for an unsuccessful pivot search and decrement r because the outer for loop will
            // increment r and skip a row
            if (i == n)
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
     
After calling the function the matrix object holds the values below.

    3.6578	    4.3459	    6.6881	   10.1399	    0.9815	
    0.0000	   13.8197	   -2.3453	   16.0833	   14.7515	
    0.0000	    0.0000	  -20.1955	  -26.3885	    6.8461	
    0.0000	    0.0000	    0.0000	  -13.2366	    1.2561	
    0.0000	    0.0000	   -0.0000	    0.0000	   -4.6013 

