**Routine Name:** power\_method 

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine computes the dominant eigenvalue of a diagonalizable matrix. 

**Input:** A diagonalizable matrix, an initial guess of the eigenvector corresponding to 
the dominant eigenvalue. 
 
**Output:** This routine returns the dominant eigenvalue of the matrix.  

**Implementation/Code:** The following is the code for power\_method.
   
```C++ 
double power_method(double *A[], double initial_guess[], double tol, int max_iter, int n)
{
    double err = 2 * tol; 
    double * Acurr = new double[n];    // just a place to store A * curr 
    double * curr = new double[n]; 
    double * next = new double[n];
    double * next_minus_curr = new double[n];

    // compute normalized initial_guess and store it in curr    
    double scale = L2_norm(initial_guess, n); 
    for (int i = 0; i < n; i++) 
        curr[i] = initial_guess[i] / scale; 

    int iter = 0; 
    while (err > tol && iter < max_iter) 
    {
        cout << "curr @ iter " << iter << endl; 
        print_vector(curr , n); cout << endl; 

        // compute A * curr
        left_matrix_vector_mult(A, curr, Acurr, n, n); 

        // compute A * curr / ||A * curr|| and store it in next
        scale_vector(Acurr, 1 / L2_norm(Acurr, n), next, n);

        // update necessary things 
        subtract_vectors(next, curr, next_minus_curr, n); 
        err = fabs(inf_norm(next_minus_curr, n)); 
        for (int i = 0; i < n; i++)
            curr[i] = next[i];
        iter++;        
    }

    // return the dominant eigenvalue as determined by Rayleigh coeffecient 
    left_matrix_vector_mult(A, curr, Acurr, n, n);
    return dot_product(Acurr, curr, n) / dot_product(curr, curr, n); 

    delete[] Acurr; 
    delete[] curr; 
    delete[] next; 
    delete[] next_minus_curr;
}
```

**Usage/Example:** Sample output with A = 

    2006341289.0000      886471.0000   408624125.0000
        886471.0000  1630581824.0000   520922249.0000
     408624125.0000   520922249.0000  1782549033.0000
 
with an initial guess, x = (1,1,1). 
The value returned is 2.46858e+09


**Last Modified:** 12/2/19
