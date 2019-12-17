**Routine Name:** tridiag\_mult 

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine computes the product of a square tridiagonal matrix and a vector.  

**Input:** A tridiagonal matrix, a vector, a memory location, to which, the output can be written, 
and the dimension of the matrix. The matrix is represented by three vectors for the subdiagonal, diagonal, 
and superdiagonal bands of the matrix.  
 
**Output:** This routine writes the result to the parameter 'out[]'  

**Implementation/Code:** The following is the code for tridiag\_mult.
   
```C++ 
void tridiag_mult(double lower[], double mid[], double upper[], double x[], double out[], int n)
{
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && i + 1 < n)
        {
            out[i] = lower[i - 1] * x[i - 1] + mid[i] * x[i] + upper[i] * x[i + 1]; 
        }
        else if (i + 1 < n) 
        {
            out[i] = mid[i] * x[i] + upper[i] * x[i + 1]; 
        }       
        else 
        {
            out[i] = lower[i -1] * x[i-1] + mid[i] * x[i]; 
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
    
    33 
    41 
    41
    36  


**Last Modified:** 12/8/19
