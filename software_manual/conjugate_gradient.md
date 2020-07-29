**Routine Name:** conjugate_gradient

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine implements the conjugate gradient method for approximating the solution of systems of linear equations.  

**Input:** A symmetric, positive definite matrix, a right hand side vector, an initial guess of the solution, an error tolerance, and a maximum number of iterations.
 
**Output:** This routine writes the approximate solution to the parameter 'out'.

**Implementation/Code:** The following is the code for conjugate\_gradient. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   
   
```C++ 
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
```

**Usage/Example:** Sample output with A = 

    4.0000         0.5000         0.3333         0.2500
    0.5000         3.0000         0.2500         0.2000
    0.3333         0.2500         2.0000         0.1667
    0.2500         0.2000         0.1667         1.0000

and b =

    5.0833
    3.9500 
    2.7500 
    1.6167

with a desired tolerance of 1.0E-06.    
After running the algorithm the values stored in out are 

    1.0000
    1.0000
    1.0000
    1.0000

