#include "Matrix.hpp"
#include "LinAlg.hpp"
#include <stdexcept>
#include <omp.h>
#include <utility>

#include <iostream>


void square_solver_in_place(Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("A must be a square matrix");
    
    const int n = A.get_num_rows(); 
    # pragma omp parallel for
    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        double pivot = A[r][k];
        for (int i = r + 1; i < n; i++) 
        {
            double multiplier = A[i][k] / pivot;
            for (int j = 0; j < n; j++) 
            {
                A[i][j] = A[i][j] - multiplier * A[r][j];
            }
            b[i] = b[i] - multiplier * b[r];
        }
    }
    // determines the solution and writes it to out
    up_triangular_back_sub(A, b, out); 
}

void up_triangular_back_sub(const Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");
    
    const int n = A.get_num_rows(); 

    out[n - 1] = b[n - 1] / A[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) 
    {
	// some_sum really is a bad name but it's better than 
	// 'sum of the products of previously computed entries of x and coeffecients of A'
        double some_sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            some_sum += A[i][j] * out[j];
        }
        out[i] = (b[i] - some_sum) / A[i][i];
    }
}

void LU_compressed_in_place(Matrix& A) 
{
    const int n = A.get_num_rows();

    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        double pivot = A[r][k];
        #pragma omp parallel for
        for (int i = r + 1; i < n; i++) 
        {
            double multiplier = A[i][k] / pivot;                                               

            // A[r] = A[r] - multiplier * A[r-1]
            for (int j = k; j < n; j++) 
            {
                A[i][j] = A[i][j] - multiplier * A[r][j];                                        
            }
            A[i][k] = multiplier;
        }
    } 
}

Matrix LU_compressed(const Matrix& A) 
{
    Matrix out(A);
    LU_compressed_in_place(out);

//    for (int k = 0, r = 0; k < n; k++, r++) 
//    {
//        double pivot = out[r][k];
//        #pragma omp parallel for
//        for (int i = r + 1; i < n; i++) 
//        {
//            double multiplier = out[i][k] / pivot;                                               
//
//            // A[r] = A[r] - multiplier * A[r-1]
//            for (int j = k; j < n; j++) 
//            {
//                out[i][j] = out[i][j] - multiplier * out[r][j];                                        
//            }
//            out[i][k] = multiplier;
//        }
//    } 
    return out; 
}

std::pair<Matrix, Matrix> LU(Matrix& A)
{ 
    const int n = A.get_num_rows();  
    Matrix L(n,n);
    Matrix U(A); 

    for (int i = 0, j = 0; i < n; i++, j++) { L[i][j] = 1.0; }

    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        double pivot = U[r][k];
        #pragma omp parallel 
        #pragma omp for
        for (int i = r + 1; i < n; i++) 
        {
            double multiplier = U[i][k] / pivot;
            for (int j = 0; j < n; j++)
            {
                U[i][j] = U[i][j] - multiplier * U[r][j];
            }
            L[i][k] = multiplier;
        }
    }
    return std::pair<Matrix, Matrix>{L, U};
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


void gauss_elim_square_in_place(Matrix& A)
{
    const int n = A.get_num_rows(); 
    if (n != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

    // elimination code
    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        // check that this entry is not zero as pivots cannot be zero
        if (A[r][k] != 0) 
        {
            double pivot = A[r][k];

            // eliminate entries below the pivot
            # pragma omp parallel
            # pragma omp for 
            for (int i = r + 1; i < n; i++) 
            {
                double multiplier = A[i][k] / pivot;

                // if the multiplier is zero this for loop does no work
                if (multiplier != 0) 
                {
                    // do the row subtraction
                    for (int j = 0; j < n; j++) {
                        A[i][j] = A[i][j] - multiplier * A[r][j];
                    }
                }
            }
        }
        else 
        {
            // try to find a pivot in other rows of column k
            int i;
            for (i = r + 1; i < n; i++) 
            {
                if (A[i][k] != 0) 
                {
                    // swap rows of the matrix
                    A.swap_rows(r, i); 

                    // decrement the values of r and k because the outermost for loop will increment
		    // them and skip elimination using the row which was just swapped
                    r--;
                    k--;
                    break;
                }
            }
            // check for an unsuccessful pivot search and decrement r because the outer for loop will
            // increment r and skip a row
            if (i == n)
                r--;
        }
    }
}


Matrix gauss_elim_square(Matrix& A) {
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");
   
    // Make a copy of the matrix and pass it to the in place Gaussian elimination function  
    Matrix out = A; 
    gauss_elim_square_in_place(out); 
    return out; 
}






