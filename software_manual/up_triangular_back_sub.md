**Routine Name:** up_triangular_back_sub

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine computes the solution of an upper triangular system of
 equations.  

**Input:** A (square) upper triangular matrix, a vector, and a memory location to write the solution.
The matrix should be an instance of [this](../src/Matrix.cpp) Matrix class and the vector should be an 
array.  

**Output:** This routine writes the solution of the system to the `out` parameter. 

**Exceptions:** Throws `std::invalid_argument` if A is not square.

**Implementation/Code:** The following is the code for up_triangular_back_sub.
```C++ 
void up_triangular_back_sub(const Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");
    
    const int n = A.get_num_rows(); 

    out[n - 1] = b[n - 1] / A[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) 
    {
        double some_sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            some_sum += A[i][j] * out[j];
        }
        out[i] = (b[i] - some_sum) / A[i][i];
    }
}
```

**Usage/Example:** Sample output using for A = 
    
    17.8281	    6.0840	   13.0353	   16.9078	   12.1246	
    0.0000	    2.1067	   10.3616	    0.6883	   -1.9126	
    0.0000	    0.0000	  -60.9972	  -10.9901	   24.2340	
    0.0000	    0.0000	    0.0000	  -12.6195	    0.3836	
    0.0000	    0.0000	    0.0000	    0.0000	  -19.3491 

and b = 
    
    1.0000
    2.0000
    3.0000
    4.0000
    5.0000

The solution returned is x = 
    
     0.1714
     1.2799
    -0.0933
    -0.3248
    -0.2584

**Last Modified:** 11/6/19 
