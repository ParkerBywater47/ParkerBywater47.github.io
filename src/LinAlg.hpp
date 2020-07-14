#ifndef LINALG_H
#define LINALG_H 

#include "Matrix.hpp"
#include <utility>

inline double dot_product(double vec1[], double vec2[], const int n) ;

void left_matrix_vector_mult(Matrix& A, double x[], double out[]); 

void gauss_elim_square_in_place(Matrix&);

Matrix gauss_elim_square(Matrix&);

std::pair<Matrix, Matrix> LU(Matrix& A);

Matrix LU_compressed(const Matrix& A);

void LU_compressed_in_place(Matrix& A);

#endif
