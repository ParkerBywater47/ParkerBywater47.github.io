**Routine Name:** left\_matrix\_vector\_mult

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine multiplies a matrix and a vector with the matrix on the left.
In math language, it computes Ax where A is the matrix and x is the vector. 

**Input:** The matrix and vector to be multiplied and a place to store the result. The Matrix object is an instance of this [Matrix class](../src/Matrix.cpp).
 
**Output:** This routine writes the result of Ax to the parameter 'out'.  

**Implementation/Code:** The following is the code for left\_matrix\_vector\_mult\_. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   

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
        out[i] = dot_product(A[i], x, num_cols);
    }    
}
```
**Dependencies:**
* `dot_product` code [here](./dot_product.md)


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
