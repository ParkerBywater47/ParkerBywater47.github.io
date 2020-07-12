#include <iostream> 
#include <omp.h>

#include "Matrix.hpp"
#include "LinAlg.hpp"

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
