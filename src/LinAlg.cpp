#include "Matrix.hpp"
#include "LinAlg.hpp"
#include <stdexcept>
#include <omp.h>
#include <utility>
#include <math.h>

#include <iostream>


double inverse_power_iteration(const Matrix& A, const double initial_guess[], const double tol, const int max_iter)
{
    const int n = A.get_num_rows(); 
    std::pair<Matrix, Matrix> lu_fact = LU(A);     
    
    Matrix& L = lu_fact.first;
    Matrix& U = lu_fact.second; 

    // initialize current x and update with values from initial_guess
    double * curr_x = new double[n]; 
    #pragma omp parallel for
    for (int i = 0; i < n; i++)    
        curr_x[i] = initial_guess[i]; 

    // initialize next x and y    
    double * next_x = new double[n]; 
    double * y = new double[n]; 


    // diff stores the difference of next x and curr x to compute error at each iteration
    double * diff = new double[n];

    double err = 2 * tol; 
    int iter = 0; 
    while (err > tol && iter < max_iter) 
    {
        // solve for y
        LU_solve(L, U, curr_x, y); 

        // compute next x
        scale_vector(y, 1.0 / L2_norm(y, n), next_x, n);

        // update error
        subtract_vectors(next_x, curr_x, diff, n);
        err = L2_norm(diff, n);

        // set curr_x forward
        # pragma omp parallel for
        for (int i = 0; i < n; i++)
            curr_x[i] = next_x[i]; 
        ++iter; 
    } 

    // compute the dominant eigenvalue of A inverse using modified Rayleigh quotient 
    double eig = dot_product(y, curr_x, n) / dot_product(curr_x, curr_x, n); 

    // clean up memory
    delete[] curr_x;  
    delete[] next_x; 
    delete[] y;
    delete[] diff; 
    
    // return 1 / eig because we've really found the dominant eigenvalue of A inverse, but need to return smallest of A  
    return 1.0 / eig; 
}

double power_iteration(const Matrix& A, const double initial_guess[], const double tol, const int max_iter)
{
    const int n = A.get_num_rows();

    double * Acurr = new double[n];    // just a place to store A * curr 
    double * curr = new double[n]; 
    double * next = new double[n];
    double * next_minus_curr = new double[n];

    // compute normalized initial_guess and store it in curr    
    double scale = L2_norm(initial_guess, n); 
    # pragma omp parallel for
    for (int i = 0; i < n; i++) 
        curr[i] = initial_guess[i] / scale; 

    double err = 2 * tol; 
    int iter = 0; 
    while (err > tol && iter < max_iter) 
    {
        // compute A * curr
        left_matrix_vector_mult(A, curr, Acurr); 
   
        // compute A * curr / ||A * curr|| and store it in next
        scale_vector(Acurr, 1 / L2_norm(Acurr, n), next, n);

        // update necessary things 
        subtract_vectors(next, curr, next_minus_curr, n); 

        err = fabs(inf_norm(next_minus_curr, n)); 
        # pragma omp parallel for
        for (int i = 0; i < n; i++)
            curr[i] = next[i];
        iter++;        
    }

    // return the dominant eigenvalue as determined by Rayleigh coeffecient 
    left_matrix_vector_mult(A, curr, Acurr);
    
    double out = dot_product(Acurr, curr, n) / dot_product(curr, curr, n); 

    delete[] Acurr; 
    delete[] curr; 
    delete[] next; 
    delete[] next_minus_curr;
    
//    std::cout << iter << std::endl;

    return out;
}

void pentadiag_mult(const double lolo[], const double lo[], const double mid[], const double up[], const double upup[], const double x[], double out[], const int n) 
{
    if (n < 4)
        throw std::invalid_argument("matrix dimension must be at least 4"); 

    # pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        if (i > 1 && i + 2 < n)
            out[i] = lolo[i-2] * x[i-2] + lo[i-1] * x[i-1] + mid[i] * x[i] + up[i] * x[i+1] + upup[i] * x[i+2]; 
        else if (i > 0 && i + 2 < n)
            out[i] = lolo[i-1] * x[i - 1] + mid[i] * x[i] + up[i] *x[i+ 1] + upup[i] * x[i + 2]; 
        else if (i == 0 && i + 2 < n)
            out[i] = mid[i] * x[i] + up[i]*x[i + 1] + upup[i] * x[i + 2]; 
        else if (i > 1 && i + 1 < n)
            out[i] = lolo[i - 2] * x[i-2] + lo[i - 1] * x[i - 1] + mid[i] * x[i] + up[i] * x[i + 1];
        else if (i > 1 && i + 2 < n)
            out[i] = lolo[i - 2] * x[i - 2] + lo[i - 1] * x[i - 1] + mid[i] * x[i]; 
        else if (i < n)
            out[i] = lolo[i -2] * x[i-2] + lo[i-1] * x[i-1] + mid[i] * x[i];
    } 
}

void tridiag_mult(const double lo[], const double mid[], const double up[], const double x[], double out[], const int n)
{
    if (n < 2)
        throw std::invalid_argument("matrix dimension must be at least 2"); 

    # pragma omp parallel for 
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && i + 1 < n)
        {
            out[i] = lo[i - 1] * x[i - 1] + mid[i] * x[i] + up[i] * x[i + 1]; 
        }
        else if (i + 1 < n) 
        {
            out[i] = mid[i] * x[i] + up[i] * x[i + 1]; 
        }       
        else 
        {
            out[i] = lo[i -1] * x[i-1] + mid[i] * x[i]; 
        }
    }
}

int conjugate_gradient(const Matrix& A, const double b[], const double init_guess[], const double tol, const int max_iter, double out[]) 
{
    const int n = A.get_num_rows();

    // copy init_guess into x
    double * curr_x = new double[n]; 
    # pragma omp parallel for
    for (int i = 0; i < n; i++)
        curr_x[i] = init_guess[i]; 
    
    // compute d_0 and r_0
    double * curr_d = new double[n]; // current direction vector?  
    double * Ax = new double[n];    // stores A * x
    left_matrix_vector_mult(A, curr_x, Ax); 
    subtract_vectors(b, Ax, curr_d, n); 
    delete[] Ax; 
    
    double * curr_r = new double[n]; // current residual vector
    # pragma omp parallel for
    for (int i = 0; i < n; i++) 
        curr_r[i] = curr_d[i]; 


    double alpha;                       // a scale factor 
    double beta;                        // the other scale factor
    double * next_d = new double[n];    // next direction vector? 
    double * next_x = new double[n];    // next iterate of the solution 
    double * next_r = new double[n];    // next iterate of the residual vector 
    double * Ad = new double[n];        // to store A * curr_d
    double * alpha_d = new double[n];   // to store alpha * curr_d 
    double * alpha_A_d = new double[n]; // to store alpha * A * curr_d
    double * beta_d = new double[n]; 

    double err = 2 * tol;
    int iter = 0;
    while (err > tol && iter < max_iter) 
    {
        // compute alpha_i
        left_matrix_vector_mult(A, curr_d, Ad); // compute Ad first as it's used to compute the demoninator below
        alpha = dot_product(curr_r, curr_r, n) / dot_product(curr_d, Ad, n); 
        
        // compute x_i+1 = x_i + alpha_i * d_i
        scale_vector(curr_d, alpha, alpha_d, n) ;
        add_vectors(curr_x, alpha_d, next_x, n); 

        // compute alpha*A*curr_d
        scale_vector(Ad, alpha, alpha_A_d, n) ;
        // compute next_r
        subtract_vectors(curr_r, alpha_A_d, next_r, n);
        
        // compute beta_i+1
        beta = dot_product(next_r, next_r, n) / dot_product(curr_r, curr_r, n); 

        // compute d_i+1
        scale_vector(curr_d, beta, beta_d, n); 
        add_vectors(next_r, beta_d, next_d, n); 

        // set curr_x, curr_r, curr_d forward 
        # pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            curr_x[i] = next_x[i]; 
            curr_r[i] = next_r[i];
            curr_d[i] = next_d[i]; 
        }

        // update the error
        err = L2_norm(curr_r, n); 
        iter++; 
    }

    // copy the solution into out
    # pragma omp parallel for
    for (int i = 0; i < n; i++) 
        out[i] = curr_x[i]; 

    delete[] curr_x; 
    delete[] next_x; 
    delete[] curr_r; 
    delete[] next_r; 
    delete[] curr_d; 
    delete[] next_d; 
    delete[] Ad; 
    delete[] alpha_d; 
    delete[] alpha_A_d; 
    delete[] beta_d; 
    return iter; 
}

int gradient_descent(const Matrix& A, const double b[], const double init_guess[], const double tol, const int max_iter, double out[]) 
{
    const int n = A.get_num_rows();


//    // the next and current iterates of the residual
//    double * curr_r = new double[n]; 
//    double * next_r = new double[n]; 
//
//    // the next and current iterates of the step size
//    double curr_step;
//    double next_step; 
//
//    // var to store A * curr_r
//    double * step_times_r = new double[n];
//    double * delta_r = new double[n]; // stores curr_step * A *curr_r
//
    // copy init_guess into curr_x
    double * curr_x = new double[n]; 
    # pragma omp parallel for
    for (int i = 0; i < n; i++)
        curr_x[i] = init_guess[i];
//
    //// compute the first residual
    //double * delete_me = new double[n]; 
    //left_matrix_vector_mult(A, curr_x, delete_me); 
    //subtract_vectors(b, delete_me, curr_r, n);  
    //delete[] delete_me;
//
    //// compute A*r_i
    //left_matrix_vector_mult(A, curr_r, A_times_r); 
// 
    //// compute the current step 
//    curr_step = dot_product(curr_r, curr_r, n) / dot_product(curr_r, A_times_r, n);


    // r is short for residual
    double * r = new double[n];
    double * A_times_r = new double[n]; 
    double * step_times_r = new double[n]; 
    double * A_times_x = new double[n];

    double step;
        
    double err = 2 * tol;     
    int iter = 0; 
    while (err > tol && iter < max_iter)
    {
        // compute r         
        left_matrix_vector_mult(A, curr_x, A_times_x);  subtract_vectors(b, A_times_x, r, n);
        
        // compute A*r for determining step size
        left_matrix_vector_mult(A, r, A_times_r);

        // compute step size
        step = dot_product(r, r, n) / dot_product(r, A_times_r, n); 

        // compute step_times_r to be added to curr_x 
        scale_vector(r, step, step_times_r, n); 

        // add step_times_r to curr_x to get next_x
        add_vectors(curr_x, step_times_r, curr_x, n); 

        // update error and iter 
        err = L2_norm(r, n); 
        iter++; 
    }

    // write the solution to out
    # pragma omp parallel for 
    for (int i = 0; i < n; i++)
        out[i] = curr_x[i]; 

    // delete what's necessary
    delete[] curr_x; 
    delete[] A_times_x;
    delete[] A_times_r; 
    delete[] step_times_r; 
    delete[] r; 
    return iter; 
}

int gauss_seidel_iteration(const Matrix& A, const double b[], const double initial_guess[], const double tol, const int max_iter, double out[]) 
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
    const int n = A.get_num_rows(); 
    if (n != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

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
    const int n = A.get_num_rows(); 
    if (n != A.get_num_cols()) 
	throw std::invalid_argument("A must be a square matrix");
    
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

void lower_triangular_fwd_sub(const Matrix& A, const double b[], double out[]) 
{
    const int n = A.get_num_rows();
    if (n != A.get_num_cols()) 
	throw std::invalid_argument("Matrix must be square");

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

void up_triangular_back_sub(const Matrix& A, const double b[], double out[]) 
{
    const int n = A.get_num_rows(); 
    if (n != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

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

std::pair<Matrix, Matrix> LU(const Matrix& A)
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



void left_matrix_vector_mult(const Matrix& A, const double x[], double out[])
{ 
    const int num_rows = A.get_num_rows(); 
    const int num_cols = A.get_num_cols(); 

    # pragma omp parallel for 
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
            # pragma omp parallel for
            for (int i = r + 1; i < n; i++) 
            {
                double multiplier = A[i][k] / pivot;

                // if the multiplier is zero this for loop does no work
                if (multiplier != 0) 
                {
                    // do the row subtraction
                    for (int j = 0; j < n; j++) 
                    {
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


Matrix gauss_elim_square(const Matrix& A) 
{
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");
   
    // Make a copy of the matrix and pass it to the in place Gaussian elimination function  
    Matrix out = A; 
    gauss_elim_square_in_place(out); 
    return out; 
}



Matrix random_diag_dom_symmetric_matrix(const int n, const int seed)
{
    Matrix out(n,n);
    srand(seed);
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        const int max_non_diag_val = RAND_MAX / n - 1;
        for (int j = i + 1; j < n; j++)
        {
            int num = (double)(rand() % max_non_diag_val);
            out[i][j] = num;
            out[j][i] = num;
            sum += fabs(num);
        }

        // sum the entries on the left half of row i
        for (int j = 0; j < i; j++)
            sum += out[i][j];

        // fill in the diagonal entries
        double num = (double)rand();
        while (fabs(num) <= sum)
            num = (double)rand();
        out[i][i] = num;
    }
    return out; 
}


Matrix hilbert_matrix(const int n) 
{
    Matrix out(n,n); 
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            out[i][j] = 1.0 / (i + j + 1); 
        }
    }
    return out; 
}
