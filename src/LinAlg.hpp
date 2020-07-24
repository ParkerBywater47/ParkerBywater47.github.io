#ifndef LINALG_H
#define LINALG_H 

#include "Matrix.hpp"
#include "omp.h"
#include <stdexcept>
#include <utility>
#include <math.h>


inline double L2_norm(const double vec[], const int n) 
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
}

int gauss_seidel_iteration(const Matrix& A, const double b[], double initial_guess[], double tol, int max_iter, double out[]) ;

int jacobi_iteration(const Matrix& A, const double b[], double initial_guess[], double tol, int max_iter, double out[]) ;

std::pair<Matrix, Matrix> cholesky(const Matrix& A); 

void lower_triangular_fwd_sub(Matrix& A, double b[], double out[]); 

void up_triangular_back_sub(const Matrix& A, double b[], double out[]);

void square_solve_spp_in_place(Matrix& A, double b[], double out[]); 

inline void square_solve_spp(const Matrix& A, const double b[], double out[])
{
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

    // initialize U and copy the values of A into it
    Matrix U = A;  

    const int n = A.get_num_rows(); 

    // make a copy of b 
    double * c = new double[n];
    # pragma omp parallel for 
    for (int i = 0; i < n; i++)
        c[i] = b[i];

    square_solve_spp_in_place(U, c, out);

//    // compute the scale vector
//    double * scale_vec = new double[n];
//    # pragma omp parallel for
//    for (int i = 0; i < n; i++) 
//    {
//        double max = abs(U[i][0]);
//        for (int j = 1; j < n; j++) 
//        {
//            max = fmax(abs(U[i][j]), max);
//            scale_vec[i] = max;
//        }
//    }
//
//    // elimination and row swapping code  
//    for (int k = 0, r = 0; k < n; k++, r++) 
//    {
//        // compute the ratios for the column to determine the "largest" row
//        int largest_ratio_idx = r;
//        double largest_ratio = abs(U[largest_ratio_idx][k]) / scale_vec[r];
//        double curr_ratio;
//        for (int row_scan_idx = r + 1; row_scan_idx < n; row_scan_idx++) 
//        {
//            curr_ratio = abs(U[row_scan_idx][k]) / scale_vec[row_scan_idx];
//            if (curr_ratio > largest_ratio) 
//            {
//                largest_ratio = curr_ratio;
//                largest_ratio_idx = row_scan_idx;
//            }
//        }
//
//        // swap the current row with row at largest_ratio_idx
//        U.swap_rows(r, largest_ratio_idx); 
////        double * rowTemp = U[r];
////        U[r] = U[largest_ratio_idx];
////        U[largest_ratio_idx] = rowTemp;
//       
//        // swap the entries in c as well
//        double temp = c[r];
//        c[r] = c[largest_ratio_idx];
//        c[largest_ratio_idx] = temp;
//
//        double pivot = U[r][k];
//        if (pivot != 0) 
//        {
//            # pragma omp parallel for 
//            for (int i = r + 1; i < n; i++) 
//            {
//                double multiplier = U[i][k] / pivot;
//                // U[r] = U[r] - multiplier * U[r-1]
//                for (int j = 0; j < n; j++) 
//                {
//                    U[i][j] = U[i][j] - multiplier * U[r][j];
//                }
//                c[i] = c[i] - multiplier * c[r];
//            }
//        }
//    }
//    up_triangular_back_sub(U, c, out);

    // clean up memory
    delete[] c; 
//    delete[] scale_vec; 
}

void square_solve_spp_in_place(Matrix& A, double b[], double out[]); 

inline void LU_solve(Matrix& L, Matrix& U, double b[], double out[]) 
{
    // solve Lc = b 
    double * c = new double[L.get_num_rows()]; 
    lower_triangular_fwd_sub(L, b, c); 

    // solve Ux = c
    up_triangular_back_sub(U, c, out);  
    delete[] c; 
}

void square_solve_in_place(Matrix& A, double b[], double out[]);

inline void square_solve(const Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols())
	throw std::invalid_argument("A must be a square matrix");

    // copy the matrix and rhs vector
    Matrix A_copy = A; 
    double * b_copy = new double[A.get_num_rows()];
    for (int i = 0; i < A.get_num_rows(); i++)
        b_copy[i] = b[i];

    // call the in place version with the copies
    square_solve_in_place(A_copy, b_copy, out);
    
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
