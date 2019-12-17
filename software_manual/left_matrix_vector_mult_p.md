**Routine Name:** left\_matrix\_vector\_mult\_p

**Author:** Parker Bywater

**Language:** C++. Pick your favorite compiler.  

**Description/Purpose:** This routine multiplies a matrix into a vector from the left. That is, it computes Ax
where A is the matrix and x is the vector. This routine includes OpenMP compiler directives to run the code 
using multiple cores.  

**Input:** The matrix and vector to be multiplied. A place to store the result, the number of rows in 
the matrix, and the number of columns of the matrix.  
 
**Output:** This routine writes the result of Ax to the parameter 'out[]'.  

**Implementation/Code:** The following is the code for left\_matrix\_vector\_mult\_p.
   
```C++
#include <omp.h>
 
void left_matrix_vector_mult_p(double *A[], double x[], double out[], const int m, const int n)
{ 
    # pragma omp parallel 
    # pragma omp for
    for (int i = 0; i < m; i++)
    {
        double dot_product = 0; 
        for (int j = 0; j < n; j++)
        {
            dot_product += A[i][j] * x[j];
        }
        out[i] = dot_product; 
    }    
}
```

**Usage/Example:** Sample output with A =   

    1   4   9
    6   21  13
    14  80  12

and x = 
    
    2
    3 
    4

The value stored in out is  
    
    50
    127
    316

**Last Modified:** 12/6/19 
