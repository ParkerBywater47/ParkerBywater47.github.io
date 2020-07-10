#include <iostream> 
#include <omp.h>

#include "Matrix.hpp"

 
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

int main() { 

    // matrix dimension
    const int n = 3; 

    // data initialization
    double data[n][n] = {
                    {1,  4,  9},
                    {6,  21, 13},
                    {14, 80, 12},
                    };
    Matrix A(n, n, &data[0][0]);
    double x[] = {2,3,4};
    double out[n];

    // function call
    left_matrix_vector_mult(A, x, out);  
        
    for (int i = 0; i < n; i++) 
    { 
        std::cout << out[i] << std::endl; 
    }

    return 0;
}
