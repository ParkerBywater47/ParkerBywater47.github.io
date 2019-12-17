**Routine Name:** gradient_descent 

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine implements gradient descent for approximating the solution 
of systems of linear equations.  

**Input:** A symmetric positive definite matrix, a right hand side vector, an initial guess of the solution, 
a desired tolerance, maximum number of iterations, and the dimension of the matrix.
 
**Output:** This routine writes the approximate solution to the parameter 'out[]'.

**Implementation/Code:** The following is the code for gradient_descent. 
   
```C++ 
void gradient_descent(double *A[], double b[], double init_guess[], double tol, int max_iter, int n, double out[]) 
{
    // curr x 
    // next x 
    double * curr_x = new double[n]; 
    double * next_x = new double[n]; 

    // curr r 
    // next r
    double * curr_r = new double[n]; 
    double * next_r = new double[n]; 

    // curr step
    // next step
    double curr_step;
    double next_step; 

    // var to store A * curr r
    double * A_times_r = new double[n]; 
    double * step_times_r = new double[n];
    double * delta_r = new double[n]; // stores curr_step * A *curr_r

    // var for err 
    double err = 2 * tol;     

    // copy init_guess into curr_x
    for (int i = 0; i < n; i++)
        curr_x[i] = init_guess[i];

    // compute the first iteration outside the loop because residual stuff
    double * delete_me = new double[n]; 
    left_matrix_vector_mult(A, curr_x, delete_me, n, n); 
    subtract_vectors(b, delete_me, curr_r, n);  
    delete[] delete_me;

    // compute A*r_i
    left_matrix_vector_mult(A, curr_r, A_times_r, n, n); 
 
    // compute the current step 
    curr_step = dot_product(curr_r, curr_r, n) / dot_product(curr_r, A_times_r, n);
        
    int iter = 0; 
    while (err > tol && iter < max_iter)
    {
        // compute next_x
        scale_vector(curr_r, curr_step, step_times_r, n); 
        add_vectors(curr_x, step_times_r, next_x, n); 

        // set next r = curr r - (curr step)*A*curr r 
        scale_vector(A_times_r, curr_step, delta_r, n); 
        subtract_vectors(curr_r, delta_r, next_r, n);         

        // update A*r_i
        left_matrix_vector_mult(A, next_r, A_times_r, n, n); 

        // compute next step = dot(curr r, curr r) / dot(curr r, A*curr r)
        next_step = dot_product(next_r, next_r, n) / dot_product(next_r, A_times_r, n); 
        curr_step = next_step; 

        // update the error 
        err = L2_norm(next_r, n); 
        
        // update other vars 
        for (int i = 0; i < n; i++) 
        {
            curr_r[i] = next_r[i]; 
            curr_x[i] = next_x[i]; 
        }
        iter++; 
    }

    // write the solution to out
    for (int i = 0; i < n; i++)
        out[i] = curr_x[i]; 

    // delete what's necessary
    delete[] curr_x; 
    delete[] next_x;  
    delete[] curr_r; 
    delete[] next_r; 
    delete[] A_times_r; 
    delete[] step_times_r; 
    delete[] delta_r; 
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

    0.999998
    1.00003
    0.999939
    1.00004
     

**Last Modified:** 12/11/19
