**Routine Name:** square_solve   

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine solves a square linear system of equations using Gaussian elimination and 
back substitution. This routine performs the gaussian elimination naively, that is, it assumes the matrix is not singular 
and does not make an attempt to swap rows.  

**Input:** A square matrix, a right-hand side vector, and a memory location to store the result. The
matrix should be an instance of [this](../src/Matrix.cpp) matrix class and the vector should be an array.
 
**Output:** This routine writes the solution of the system to the provided memory location. 

**Exceptions:** Throws `std::invalid_argument` if A is not square. 

**Implementation/Code:** The following is the code for square_solve. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   

```C++  
inline void square_solve(const Matrix& A, const double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols())
	throw std::invalid_argument("A must be a square matrix");

    // copy the matrix and rhs vector
    Matrix A_copy = A; 

    double * b_copy = new double[A.get_num_rows()];
    # pragma omp parallel for
    for (int i = 0; i < A.get_num_rows(); i++)
        b_copy[i] = b[i];

    // call the in place version with the copies
    square_solve_in_place(A_copy, b_copy, out);
    
    // clean up memory 
    delete[] b_copy; 
}
```

**Dependencies:** 
* `square_solve_in_place` code [here](./square_solve_in_place.md)

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

