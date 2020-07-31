**Routine Name:** inverse_power_iteration 

**Author:** Parker Bywater

**Language:** C++ 

**Description/Purpose:** This routine approximates the eigenvalue with the smallest magnitude (absolute value) for a given matrix.

<!--
It's important to note that this initial guess cannot be a multiple of any other eigenvector of the matrix,
or else the method will converge to its associated eigenvalue. This routine assumes the matrix is non-singular.
-->

**Input:** A diagonalizable matrix as an instance of [this](../src/Matrix.cpp) matrix class, an error tolerance, a maximum number of iterations, and an initial guess of the eigenvector corresponding to the smallest eigenvalue. The initial guess is ideally a random vector. It is necessary that no entries be zero.  

**Output:** This routine returns an approximation of the smallest magnitude eigenvalue within the specified tolerance.  

**Implementation/Code:** The following is the code for inverse_power_iteration. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   

```C++ 
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
```

**Usage/Example:** Sample output with A =  

      19776.7761        1529.0000        1421.0000          93.0000
       1529.0000       15303.0000        4003.0000        4290.0000
       1421.0000        4003.0000       17794.0000        3949.0000
         93.0000        4290.0000        3949.0000        9196.9832

The result is 6611.17, which is indeed the smallest magnitude eigenvalue according to WolframAlpha. 

