#ifndef LINALG_H
#define LINALG_H 

#include "Matrix.hpp"
#include "omp.h"
#include <stdexcept>
#include <utility>


//inline void LU_solve(Matrix& L, Matrix& U, double b[], double out[]) 
//{
//    // solve Lc = b 
//    double * c = new double[n]; 
//    lower_triangular_fwd_sub(L, b, c); 
//
//    // solve Ux = c
//    up_triangular_back_sub(U, c, x);  
//    delete[] c; 
//}

void lower_triangular_fwd_sub(Matrix& A, double b[], double out[]); 

void up_triangular_back_sub(const Matrix& A, double b[], double out[]);

void square_solver_in_place(Matrix& A, double b[], double out[]);

inline void square_solver(const Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols())
	throw std::invalid_argument("A must be a square matrix");

    // copy the matrix and rhs vector
    Matrix A_copy = A; 
    double * b_copy = new double[A.get_num_rows()];
    for (int i = 0; i < A.get_num_rows(); i++)
        b_copy[i] = b[i];

    // call the in place version with the copies
    square_solver_in_place(A_copy, b_copy, out);
    
    // clean up memory 
    delete[] b_copy; 
}

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

inline void diagonal_solve(const Matrix& A, double b[], double out[])  
{ 
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("Matrix must be square"); 

    const int n = A.get_num_rows(); 
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        out[i] = b[i] / A[i][i];
} 


void square_solver(const Matrix& A, double b[], double out[]) ;
//{
//    // copy the Matrix  
//    Matrix copy = A;
//
//    // do elimination on the copied matrix
//    gauss_elim_square_in_place(copy); 
//
//    // call function which back-substitutes to get the solution
//    up_triangular_back_sub(copy, b, out);
//}





#endif
