#include "Matrix.hpp"
#include "LinAlg.hpp"
#include <stdexcept>
#include <omp.h>
#include <utility>
#include <math.h>

#include <iostream>

int gauss_seidel_iteration(const Matrix& A, const double b[], double initial_guess[], const double tol, const int max_iter, double out[]) 
{
    const int n = A.get_num_rows();

    int iter = 0;
    double err = 2 * tol;
    double * curr = new double[n];
    double * next = new double[n];

    // make curr = initial_guess
    # pragma omp parallel for 
    for (int k = 0; k < n; k++)
        curr[k] = initial_guess[k];

    // make next = curr
    # pragma omp parallel for 
    for (int k = 0; k < n; k++)
        next[k] = curr[k];

    while (iter++ < max_iter && err > tol)
    {
        // cout << "curr @ iter: " << iter << endl;
        // cout << "err = " << err << "\n" << endl;
        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                    sum += A[i][j] * next[j];
            }
            next[i] = (b[i] - sum) / A[i][i];
        }

        // update the error
        err = fabs(L2_norm(next, n) - L2_norm(curr, n));

        // make curr = next for next iteration
        # pragma omp parallel for
        for (int k = 0; k < n; k++)
            curr[k] = next[k];
    }
    // write the solution to out
    # pragma omp parallel for
    for (int i = 0; i < n; i++)
        out[i] = next[i];

    delete[] curr;
    delete[] next; 
    return iter - 1; 
}

int jacobi_iteration(const Matrix& A, const double b[], const double initial_guess[], const double tol, const int max_iter, double out[]) 
{
    const int n = A.get_num_rows();

    int iter = 0;
    double err = 2 * tol;
    double * curr = new double[n];
    double * next = new double[n];

    // make curr = initial_guess
    # pragma omp parallel for
    for (int k = 0; k < n; k++)
        curr[k] = initial_guess[k];

    while (iter++ < max_iter && err > tol) 
    {
        // cout << "curr @ iter: " << iter << endl;
        // cout << "err = " << err << endl;
        # pragma omp parallel for
        for (int i = 0; i < n; i++) 
        {
            double sum = 0.0;
            for (int j = 0; j < n; j++) 
            {
                if (i != j)
                    sum += A[i][j] * curr[j];
            }
            next[i] = (b[i] - sum) / A[i][i];
        }
        // update the error
        err = fabs(L2_norm(next, n) - L2_norm(curr, n));

        // make curr = next for next iteration
        # pragma omp parallel for
        for (int k = 0; k < n; k++)
            curr[k] = next[k];
    }
    // write the solution to out
    # pragma omp parallel for
    for (int k = 0; k < n; k++)
        out[k] = next[k];

    delete[] curr;
    delete[] next; 
    return iter - 1;
}

std::pair<Matrix, Matrix> cholesky(const Matrix& A) 
{ 
    const int n = A.get_num_rows();

    // check that the matrix is symmetric
    if (n != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square to be symmetric"); 

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (A[i][j] != A[j][i])
                throw std::invalid_argument("Matrix must be symmetric");
        }
    }

    std::pair<Matrix, Matrix> out(Matrix(n,n), Matrix(n,n));
    Matrix& L = out.first;
    Matrix& L_trans = out.second;

    // do special gaussian elimination
    L[0][0] = sqrt(A[0][0]);
    L_trans[0][0] = L[0][0];
    for (int i = 1; i < n; i++) 
    {
        int j;
        for (j = 0; j < i; j++) 
        {
            // compute the below diagonal entries
            double sum0 = 0.0;
            for (int k = 0; k < j; k++)
                sum0 += L[i][k] * L[j][k];
            L[i][j] = (A[i][j] - sum0) / L[j][j];
            L_trans[j][i] = L[i][j]; 
        }

        // compute the diagonal entries
        double sum1 = 0;
        for (int k = 0; k < j; k++)
            sum1 += L[j][k] * L[j][k];
        L[j][j] = sqrt(A[j][j] - sum1);
        L_trans[j][j] = L[j][j]; 
    }
    return out; 
}    

void square_solve_spp_in_place(Matrix& A, double b[], double out[])
{
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

    const int n = A.get_num_rows(); 

    // compute the scale vector
    double * scale_vec = new double[n];
    # pragma omp parallel for
    for (int i = 0; i < n; i++) 
    {
        double max = abs(A[i][0]);
        for (int j = 1; j < n; j++) 
        {
            max = fmax(abs(A[i][j]), max);
            scale_vec[i] = max;
        }
    }

    // elimination and row swapping code  
    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        // compute the ratios for the column to determine the "largest" row
        int largest_ratio_idx = r;
        double largest_ratio = abs(A[largest_ratio_idx][k]) / scale_vec[r];
        double curr_ratio;
        for (int row_scan_idx = r + 1; row_scan_idx < n; row_scan_idx++) 
        {
            curr_ratio = abs(A[row_scan_idx][k]) / scale_vec[row_scan_idx];
            if (curr_ratio > largest_ratio) 
            {
                largest_ratio = curr_ratio;
                largest_ratio_idx = row_scan_idx;
            }
        }

        // swap the current row with row at largest_ratio_idx
        A.swap_rows(r, largest_ratio_idx); 
//        double * rowTemp = U[r];
//        U[r] = U[largest_ratio_idx];
//        U[largest_ratio_idx] = rowTemp;
       
        // swap the entries in c as well
        double temp = b[r];
        b[r] = b[largest_ratio_idx];
        b[largest_ratio_idx] = temp;

        double pivot = A[r][k];
        if (pivot != 0) {
            # pragma omp parallel for 
            for (int i = r + 1; i < n; i++) 
            {
                double multiplier = A[i][k] / pivot;
                // U[r] = U[r] - multiplier * U[r-1]
                for (int j = 0; j < n; j++) 
                {
                    A[i][j] = A[i][j] - multiplier * A[r][j];
                }
                b[i] = b[i] - multiplier * b[r];
            }
        }
    }
    up_triangular_back_sub(A, b, out);

    // clean up memory
    delete[] scale_vec; 
}


void square_solve_in_place(Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("A must be a square matrix");
    
    const int n = A.get_num_rows(); 
    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        double pivot = A[r][k];
        #pragma omp parallel for
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

void lower_triangular_fwd_sub(Matrix& A, double b[], double out[]) 
{
    if (A.get_num_rows() != A.get_num_cols()) 
	throw std::invalid_argument("Matrix must be square");

    const int n = A.get_num_rows();

    out[0] = b[0] / A[0][0];
    for (int i = 1; i < n; i++)
    {
	// some_sum really is a bad name but it's better than 
	// 'sum of the products of previously computed entries of x and coeffecients of A'
        double some_sum = 0;
        for (int j = i - 1; j >= 0; j--)
            some_sum += A[i][j] * out[j];
        out[i] = (b[i] - some_sum) / A[i][i];
    }
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






