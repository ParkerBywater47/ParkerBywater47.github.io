**Routine Name:** gradient_descent 

**Author:** Parker Bywater

**Language:** C++ 

**Description/Purpose:** This routine implements gradient descent for approximating the solution of systems of linear equations.  

**Input:** A symmetric, positive definite matrix, a right hand side vector, an initial guess of the solution, 
a desired error tolerance, and a maximum number of iterations. 

**Output:** This routine writes the approximate solution to the parameter 'out'.

**Implementation/Code:** The following is the code for gradient_descent. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   
   
```C++ 
int gradient_descent(const Matrix& A, const double b[], const double init_guess[], const double tol, const int max_iter, double out[]) 
{
    const int n = A.get_num_rows();

    // copy init_guess into curr_x
    double * curr_x = new double[n]; 
    # pragma omp parallel for
    for (int i = 0; i < n; i++)
        curr_x[i] = init_guess[i];

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

