#include "Matrix.hpp"
#include "LinAlg.hpp"
#include <stdexcept>
#include <omp.h>


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

            # pragma omp parallel
            # pragma omp for 
            // eliminate entries below the pivot
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