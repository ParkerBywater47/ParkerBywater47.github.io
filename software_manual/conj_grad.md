**Routine Name:** conj_grad 

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine implements the conjugate gradient method for approximating the solution 
of systems of linear equations.  

**Input:** A symmetric positive definite matrix, a right hand side vector, an initial guess of the solution, 
a desired tolerance, maximum number of iterations, and the dimension of the matrix.
 
**Output:** This routine writes the approximate solution to the parameter 'out[]'.

**Implementation/Code:** The following is the code for conj_grad. 
   
```C++ 
void conj_grad(double *A[], double b[], double init_guess[], const double tol, const int max_iter, const int n, double out[]) 
{
    // copy init_guess into x
    double * curr_x = new double[n]; 
    for (int i = 0; i < n; i++)
        curr_x[i] = init_guess[i]; 
    
    // compute d_0 and r_0
    double * curr_d = new double[n]; // current direction vector?  
    double * Ax = new double[n];    // stores Ax
    left_matrix_vector_mult(A, curr_x, Ax, n,n); 
    subtract_vectors(b, Ax, curr_d, n); 
    delete[] Ax; 
    
    double * curr_r = new double[n]; // current residual vector
    for (int i = 0; i < n; i++) 
        curr_r[i] = curr_d[i]; 


    double err = 2 * tol;
    int iter = 0;
    double alpha;                       // a scale factor 
    double beta;                        // the other scale factor
    double * next_d = new double[n];    // next direction vector? 
    double * next_x = new double[n];    // next iterate 
    double * next_r = new double[n];    // next residual vector 
    double * Ad = new double[n];        // to store A * curr_d
    double * alpha_d = new double[n];   // to store alpha * curr_d 
    double * alpha_A_d = new double[n]; // to store alpha * A * curr_d
    double * beta_d = new double[n]; 
    while (err > tol && iter < max_iter) 
    {
        // compute alpha_i
        left_matrix_vector_mult(A, curr_d, Ad, n, n); // compute Ad first as it's used to compute the demoninator below
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

}
```

**Usage/Example:** Sample output with A = 

    1.0000         0.5000         0.3333         0.2500
    0.5000         0.3333         0.2500         0.2000
    0.3333         0.2500         0.2000         0.1667
    0.2500         0.2000         0.1667         0.1429

and b =

    2.08333
    1.28333
    0.95
    0.759524

with a desired tolerance of 1.0E-08.    
After running the algorithm the values stored in out are 

    1
    1
    1
    1

**Last Modified:** 12/11/19 
