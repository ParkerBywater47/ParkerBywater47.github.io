**Routine Name:** square_solve_spp_in_place

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine solves a square linear system of equations using Gaussian elimination and 
back substitution. This routine performs the Gaussian elimination using scaled partial pivoting (spp) for the sake of greater numerical stability.

**Input:** A square matrix, a right-hand side vector, and a memory location to store the result. The
matrix should be an instance of [this](../src/Matrix.cpp) matrix class and the vector should be an array.
 
**Output:** This routine writes the solution of the system to the provided memory location. 

**Exceptions:** Throws `std::invalid_argument` if A is not square. 

**Implementation/Code:** The following is the code for square_solver. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   

```C++  
void square_solve_spp_in_place(Matrix& A, double b[], double out[])
{
    const int n = A.get_num_rows(); 
    if (n != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

    // compute the scale vector
    double * scale_vec = new double[n];
    # pragma omp parallel for
    for (int i = 0; i < n; i++) 
    {
        double max = abs(A[i][0]);
        for (int j = 1; j < n; j++) 
        {
            max = fmax(abs(A[i][j]), max);
            scale_vec[i] = max;
        }
    }

    // elimination and row swapping code  
    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        // compute the ratios for the column to determine the "largest" row
        int largest_ratio_idx = r;
        double largest_ratio = abs(A[largest_ratio_idx][k]) / scale_vec[r];
        double curr_ratio;
        for (int row_scan_idx = r + 1; row_scan_idx < n; row_scan_idx++) 
        {
            curr_ratio = abs(A[row_scan_idx][k]) / scale_vec[row_scan_idx];
            if (curr_ratio > largest_ratio) 
            {
                largest_ratio = curr_ratio;
                largest_ratio_idx = row_scan_idx;
            }
        }

        // swap the current row with row at largest_ratio_idx
        A.swap_rows(r, largest_ratio_idx); 
       
        // swap the entries in c as well
        double temp = b[r];
        b[r] = b[largest_ratio_idx];
        b[largest_ratio_idx] = temp;

        double pivot = A[r][k];
        if (pivot != 0) {
            # pragma omp parallel for 
            for (int i = r + 1; i < n; i++) 
            {
                double multiplier = A[i][k] / pivot;
                // do A[r] = U[r] - multiplier * A[r-1] for all entries of A[r]
                for (int j = 0; j < n; j++) 
                {
                    A[i][j] = A[i][j] - multiplier * A[r][j];
                }
                b[i] = b[i] - multiplier * b[r];
            }
        }
    }
    up_triangular_back_sub(A, b, out);

    // clean up memory
    delete[] scale_vec; 
}
```

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
