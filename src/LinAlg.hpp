#ifndef LINALG_H
#define LINALG_H 

#include "Matrix.hpp"
#include "omp.h"
#include <stdexcept>
#include <utility>
#include <math.h>

#include <iostream>

double inverse_power_iteration(const Matrix& A, const double initial_guess[], const double tol, const int max_iter); 

inline void print_vector(const double v[], const int n) 
{ 
    for (int i = 0; i < n; i++ )
    { 
        std::cout << v[i] << std::endl;
    }
    std::cout << std::endl; 
}

Matrix hilbert_matrix(const int n) ; 

double power_iteration(const Matrix& A, const double initial_guess[], const double tol, const int max_iter); 

void pentadiag_mult(const double lolo[], const double lo[], const double mid[], const double up[], const double upup[], const double x[], double out[], const int n); 

void tridiag_mult(const double lo[], const double mid[], const double up[], const double x[], double out[], const int n); 

int conjugate_gradient(const Matrix& A, const double b[], const double init_guess[], const double tol, const int max_iter, double out[]) ;

int gradient_descent(const Matrix& A, const double b[], const double init_guess[], const double tol, const int max_iter, double out[]) ; 

inline double L2_norm(const double vec[], const int n) 
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
}

int gauss_seidel_iteration(const Matrix& A, const double b[], const double initial_guess[], const double tol, const int max_iter, double out[]) ;

int jacobi_iteration(const Matrix& A, const double b[], const double initial_guess[], const double tol, const int max_iter, double out[]) ;

std::pair<Matrix, Matrix> cholesky(const Matrix& A); 

void lower_triangular_fwd_sub(const Matrix& A, const double b[], double out[]); 

void up_triangular_back_sub(const Matrix& A, const double b[], double out[]);

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

inline void LU_solve(const Matrix& L, const Matrix& U, const double b[], double out[]) 
{
    // solve Lc = b 
    double * c = new double[L.get_num_rows()]; 
    lower_triangular_fwd_sub(L, b, c); 

    // solve Ux = c
    up_triangular_back_sub(U, c, out);  
    delete[] c; 
}

void square_solve_in_place(Matrix& A, double b[], double out[]);

inline void square_solve(const Matrix& A, const double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols())
	throw std::invalid_argument("A must be a square matrix");

    // copy the matrix and rhs vector
    Matrix A_copy = A; 

    double * b_copy = new double[A.get_num_rows()];
    # pragma omp parallel for
    for (int i = 0; i < A.get_num_rows(); i++)
        b_copy[i] = b[i];

    // call the in place version with the copies
    square_solve_in_place(A_copy, b_copy, out);
    
    // clean up memory 
    delete[] b_copy; 
}

void left_matrix_vector_mult(const Matrix& A, const double x[], double out[]); 

void gauss_elim_square_in_place(Matrix&);

Matrix gauss_elim_square(const Matrix&);

std::pair<Matrix, Matrix> LU(const Matrix& A);

void LU_compressed_in_place(Matrix& A);

inline Matrix LU_compressed(const Matrix& A) 
{
    Matrix out(A);
    LU_compressed_in_place(out);
    return out; 
}

inline double dot_product(const double vec1[], const double vec2[], const int n) 
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec1[i] * vec2[i]; 
    return sum;
}

inline void diagonal_solve(const Matrix& A, const double b[], double out[])  
{ 
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("Matrix must be square"); 

    const int n = A.get_num_rows(); 
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        out[i] = b[i] / A[i][i];
} 

inline void subtract_vectors(const double v[], const double u[], double out[], const int n) 
{ 
    # pragma omp parallel for
    for (int i = 0; i < n; i++) 
    {
        out[i] = v[i] - u[i];
    }
}

inline void add_vectors(const double v[], const double u[], double out[], const int n) 
{ 
    # pragma omp parallel for
    for (int i = 0; i < n; i++) 
    {
        out[i] = u[i] + v[i];
    }
}

inline void scale_vector(const double v[], const double a, double out[], const int n) 
{ 
    # pragma omp parallel for 
    for (int i = 0; i < n; i++)
    {
        out[i] = v[i] * a;
    }
}

Matrix random_diag_dom_symmetric_matrix(const int n, const int seed);

inline void ones_vector(int n, double out[])
{
    # pragma omp parallel for
    for (int i = 0; i < n; i++)
        out[i] = 1;
}

inline double inf_norm(const double v[], const int n)
{ 
    double max = fabs(v[0]);
    for (int i = 1; i < n; i++) 
    {
        max = fmax(fabs(v[i]), max);   
    }
    return max;
}

#endif
