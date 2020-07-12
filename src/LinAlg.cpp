#include "Matrix.hpp"
#include "LinAlg.hpp"


inline double dot_product(double vec1[], double vec2[], const int n) 
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec1[i] * vec2[i]; 
    return sum;
}


void left_matrix_vector_mult(Matrix& A, double x[], double out[])
{ 
    const int num_rows = A.get_num_rows(); 
    const int num_cols = A.get_num_cols(); 
    # pragma omp parallel 
    # pragma omp for
    for (int i = 0; i < num_rows; i++)
    {
//        double dot_product = 0; 
//        for (int j = 0; j < num_cols; j++)
//        {
//            dot_product += A[i][j] * x[j];
//        }
//        out[i] = dot_product; 
        out[i] = dot_product(A[i], x, num_cols);
    }    
}
