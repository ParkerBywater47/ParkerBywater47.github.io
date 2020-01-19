**Routine Name:** lower_triangular_back_sub

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler.

**Description/Purpose:** This routine computes the solution of a lower triangular system of 
linear equations.

**Input:** A (square) lower triangular matrix, a vector, and a memory location to write the solution.
The matrix should be an instance of [this](./Matrix.cpp) Matrix class and the vector should be an 
array.  

**Output:** This routine returns the solution of the system as an array of doubles.

**Implementation/Code:** The following is the code for lower_triangular_back_sub.
```C++
void lower_triangular_back_sub(Matrix& A, double b[], double out[]) {
    if (A.get_num_rows() == 0)
        throw "A must be a nonempty matrix";
    else if (A.get_num_rows() != A.get_num_cols()) 
	throw "A must be a square matrix"

    const int n = A.get_num_rows();

    out[0] = b[0] / A[0][0];
    for (int i = 1; i < A; i++)
    {
	// some_sum really is a bad name but it's better than 
	// 'sum of the products of previously computed entries of x and coeffecients of A'
        double some_sum = 0;
        for (int j = i - 1; j >= 0; j--)
            some_sum += A[i][j] * out[j];
        out[i] = (b[i] - some_sum) / A[i][i];
    }
    return out;
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

     0.0561
     0.9494
    -0.0492
    -0.3170
    -0.2584

**Last Modified:** 11/6/19

