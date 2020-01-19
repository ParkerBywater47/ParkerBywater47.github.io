**Routine Name:** left\_matrix\_vector\_mult

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine multiplies a matrix into a vector from the left.
That is, it computes Ax where A is the matrix and x is the vector. This routine includes OpenMP
compiler directives to take advantage of multiple threads. To take advantage this the `omp.h` header
must be included and must be enabled at compile time as follows.

    g++ -fopenmp your_src_file.cpp 

**Input:** The matrix and vector to be multiplied. A place to store the result, the number of rows
in the matrix, and the number of columns of the matrix. The Matrix object is an instance of my 
[Matrix class](./Matrix.cpp).
 
**Output:** This routine writes the result of Ax to the parameter 'out'.  

**Implementation/Code:** The following is the code for left\_matrix\_vector\_mult\_.
   
```C++
#include <omp.h>
 
void left_matrix_vector_mult(Matrix& A, double x[], double out[])
{ 
    const int num_rows = A.get_num_rows(); 
    const int num_cols = A.get_num_cols(); 
    # pragma omp parallel 
    # pragma omp for
    for (int i = 0; i < num_rows; i++)
    {
        double dot_product = 0; 
        for (int j = 0; j < num_cols; j++)
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

After calling the function the value stored in out is  
    
    50
    127
    316

**Last Modified:** 12/6/19 
