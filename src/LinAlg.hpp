#ifndef LINALG_H
#define LINALG_H 

#include "Matrix.hpp"
#include "omp.h"
#include <stdexcept>
#include <utility>


void left_matrix_vector_mult(Matrix& A, double x[], double out[]); 

void gauss_elim_square_in_place(Matrix&);

Matrix gauss_elim_square(Matrix&);

std::pair<Matrix, Matrix> LU(Matrix& A);

Matrix LU_compressed(const Matrix& A);

void LU_compressed_in_place(Matrix& A);

inline double dot_product(double vec1[], double vec2[], const int n) 
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec1[i] * vec2[i]; 
    return sum;
}

inline void diagonal_solver(const Matrix& A, double b[], double out[])  
{ 
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("Matrix must be square"); 

    const int n = A.get_num_rows(); 
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        out[i] = b[i] / A[i][i];
} 







#endif
