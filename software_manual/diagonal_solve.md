**Routine Name:** diagonal_solve 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the solution of a square, diagonal, 
linear system of equations (Ax = b) where the coeffecient matrix is diagonal.  

**Input:** A diagonal matrix, a vector, and a memory location to write the solution. The matrix 
should be an instance of [this](../src/Matrix.cpp) matrix class
and the vector should be an array. 
 
**Output:** This routine returns the solution of the system by writing the result to the `out` parameter.

**Exceptions:** Throws `std::invalid_argument` if the matrix is not square. 

**Implementation/Code:** The following is the code for diagonal_solve. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   

```C++ 
inline void diagonal_solve(const Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("Matrix must be square"); 

    const int n = A.get_num_rows(); 
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        out[i] = b[i] / A[i][i];
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

