**Routine Name:** square_solve_in_place   

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine solves a square linear system of equations using Gaussian elimination and 
back substitution without using extra storage space. As a consequence the value of the arguments passed can not be guaranteed to remain unchanged. Also, this routine performs the gaussian elimination 
naively, that is, it assumes the matrix is not singular and doesn't attempt row swaps.  

**Input:** A matrix, a vector, and a memory location to write the solution. The matrix 
should be an instance of [this](../src/Matrix.cpp) Matrix class
and the vector should be an array.  

**Output:** This routine returns the solution of the system by writing the result to the `out` 
parameter.

**Exceptions:** Throws `std::invalid_argument` if A is not square. 

**Implementation/Code:** The following is the code for square_solve_in_place. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   

```C++ 
void square_solve_in_place(Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("A must be a square matrix");
    
    const int n = A.get_num_rows(); 
    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        double pivot = A[r][k];
        # pragma omp parallel for
        for (int i = r + 1; i < n; i++) 
        {
            double multiplier = A[i][k] / pivot;
            for (int j = 0; j < n; j++) 
            {
                A[i][j] = A[i][j] - multiplier * A[r][j];
            }
            b[i] = b[i] - multiplier * b[r];
        }
    }
    // determines the solution and writes it to out
    up_triangular_back_sub(A, b, out); 
}
}
```
**Dependencies:**
* `up_triangular_back_sub` code [here](./up_triangular_back_sub.md). 

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

