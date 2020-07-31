**Routine Name:** tridiag\_mult 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the product of a square tridiagonal matrix and a vector.  

**Input:** A tridiagonal matrix, a vector, a memory location, to which, the output can be written, 
and the dimension of the matrix. The matrix is represented by three vectors for the subdiagonal, diagonal, 
and superdiagonal bands of the matrix.  
 
**Output:** This routine writes the result to the parameter 'out[]'  

**Exceptions:** Throws `std::invalid_argument` if n < 2 as this doesn't make sense for matrix-vector multiplication at all. 

**Implementation/Code:** The following is the code for tridiag\_mult. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   
   
```C++ 
void tridiag_mult(const double lo[], const double mid[], const double up[], const double x[], double out[], const int n)
{
    if (n < 2)
        throw std::invalid_argument("matrix dimension must be at least 2"); 

    # pragma omp parallel for 
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && i + 1 < n)
        {
            out[i] = lo[i - 1] * x[i - 1] + mid[i] * x[i] + up[i] * x[i + 1]; 
        }
        else if (i + 1 < n) 
        {
            out[i] = mid[i] * x[i] + up[i] * x[i + 1]; 
        }       
        else 
        {
            out[i] = lo[i -1] * x[i-1] + mid[i] * x[i]; 
        }
    }
}
```

**Usage/Example:** Sample output with A = 
    
    1   1   0   0
    1   1   1   0
    0   1   1   1
    0   0   1   1

and x =
    
    5
    13 
    15 
    8

The values stored in out after execution are 
    
    18
    33 
    36 
    23 
