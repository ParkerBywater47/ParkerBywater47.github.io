**Routine Name:** power\_iteration 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the dominant eigenvalue (the eigenvalue with the largest absolute value) of a diagonalizable matrix. 

**Input:** A diagonalizable matrix as an instance of [this](../src/Matrix.cpp) matrix class, an error tolerance, a maximum number of iterations, and an initial guess of the eigenvector corresponding to the dominant eigenvalue. The initial guess can be anything other than a vector of zeroes; better guesses simply mean faster convergence on average.  
 
**Output:** This routine returns an approximation of the dominant eigenvalue of the matrix within the given error tolerance or the most recent approximation if the iteration limit is reached. 

**Implementation/Code:** The following is the code for power\_iteration.
   
```C++ 
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

    return out;
}
```

**Usage/Example:** Sample output with A = 

    2006341289.0000      886471.0000   408624125.0000
        886471.0000  1630581824.0000   520922249.0000
     408624125.0000   520922249.0000  1782549033.0000
 
with an initial guess, x = (1,1,1). 
The value returned is 2.46858e+09

