**Routine Name:** pentadiag\_mult 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the product of a square pentadiagonal matrix and a vector.  
This routine assumes that the matrix is at least a 4x4 matrix as pentadiagonal matrices don't make much 
sense for n < 4.  

**Input:** A pentadiagonal matrix, a vector, a memory location, to which, the output can be written, 
and the dimension of the matrix. The matrix is represented by five vectors for the lowest diagonal, 
lower diagonal, diagonal, higher diagonal, and highest diagonal bands of the matrix.  
 
**Output:** This routine writes the result to the parameter 'out[]'.  

**Implementation/Code:** The following is the code for pentadiag\_mult. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   
   
```C++ 
void pentadiag_mult(const double lolo[], const double lo[], const double mid[], const double up[], const double upup[], const double x[], double out[], const int n) 
{
    if (n < 4)
        throw std::invalid_argument("matrix dimension must be at least 4"); 

    # pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        if (i > 1 && i + 2 < n)
            out[i] = lolo[i-2] * x[i-2] + lo[i-1] * x[i-1] + mid[i] * x[i] + up[i] * x[i+1] + upup[i] * x[i+2]; 
        else if (i > 0 && i + 2 < n)
            out[i] = lolo[i-1] * x[i - 1] + mid[i] * x[i] + up[i] *x[i+ 1] + upup[i] * x[i + 2]; 
        else if (i == 0 && i + 2 < n)
            out[i] = mid[i] * x[i] + up[i]*x[i + 1] + upup[i] * x[i + 2]; 
        else if (i > 1 && i + 1 < n)
            out[i] = lolo[i - 2] * x[i-2] + lo[i - 1] * x[i - 1] + mid[i] * x[i] + up[i] * x[i + 1];
        else if (i > 1 && i + 2 < n)
            out[i] = lolo[i - 2] * x[i - 2] + lo[i - 1] * x[i - 1] + mid[i] * x[i]; 
        else if (i < n)
            out[i] = lolo[i -2] * x[i-2] + lo[i-1] * x[i-1] + mid[i] * x[i];
    } 
}
```

**Usage/Example:** Sample output with A = 

    1   1   1   0   0
    1   1   1   1   0
    1   1   1   1   1
    0   1   1   1   1
    0   0   0   1   1

and b = 
    
    5 
    13 
    15 
    8 
    24

The values stored in out after execution are 

    33
    41
    65
    60
    47
     
