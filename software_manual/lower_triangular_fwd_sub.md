**Routine Name:** lower_triangular_back_sub

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the solution of a lower triangular system of 
linear equations.

**Input:** A diagonal matrix, a vector, and a memory location to write the solution. The matrix 
should be an instance of [this](../src/Matrix.cpp) Matrix class and the vector should be an array. 

**Output:** This routine returns the solution of the system by writing the result to the `out` parameter.

**Exceptions:** Throws `std::invalid_argument` if the matrix is not square. 

**Implementation/Code:** The following is the code for lower_triangular_back_sub. 
<!-- This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   
-->


```C++
void lower_triangular_fwd_sub(Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("Matrix must be square");

    const int n = A.get_num_rows();

    out[0] = b[0] / A[0][0];
    for (int i = 1; i < n; i++)
    {
	// some_sum really is a bad name but it's better than 
	// 'sum of the products of previously computed entries of x and coeffecients of A'
        double some_sum = 0;
        for (int j = i - 1; j >= 0; j--)
            some_sum += A[i][j] * out[j];
        out[i] = (b[i] - some_sum) / A[i][i];
    }
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

    0.0560912
    0.787365
    0.096554
    -0.28296
    -0.18577

**Last Modified:** 11/6/19

