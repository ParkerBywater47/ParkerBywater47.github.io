**Routine Name:** InversePowerMethod 

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine approximates the eigenvalue with the smallest magnitude for a given matrix.
This requires an initial guess of the eigenvector corresponding to the smallest magnitude eigenvalue. 
It's important to note that this initial guess cannot be a multiple of any other eigenvector of the matrix,
or else the method will converge to its associated eigenvalue. This routine assumes the matrix is non-singular.

**Input:** A matrix, an initial guess of the associated eigenvector, a desired tolerance, and the dimension of
the matrix. 
 
**Output:** This routine returns an approximation of the smallest magnitude eigenvalue within the specified 
tolerance.  

**Implementation/Code:** The following is the code for InversePowerMethod.
   
```C++ 
double InversePowerMethod(double *A[], double initial_guess[], double tol, const int max_iter, const int n)
{
    // compute the LU factorization of A
    double ** L = new double*[n]; 
    for (int i = 0; i < n; i++) 
        L[i] = new double[n]; 
    double ** U = new double*[n];
    for (int i = 0; i < n; i++) 
        U[i] = new double[n]; 

    LU_fact(A, L, U, n);     

    // initialize currX and update with values from initial_guess
    double * currX = new double[n]; 
    for (int i = 0; i < n; i++)    
        currX[i] = initial_guess[i]; 

    // initialize nextX and y    
    double * nextX = new double[n]; 
    double * y = new double[n]; 


    diff stores the difference of nextX and currX to compute error at each iteration
    double * diff = new double[n];

    double err = 2 * tol; 
    int iter = 0; 
    while (err > tol && iter < max_iter) 
    {
        // solve for y
        LU_sub_solver(L, U, currX, y, n); 

        // compute next x
        scale_vector(y, 1.0 / L2_norm(y, n), nextX, n);

        // update error
        subtract_vectors(nextX, currX, diff, n);
        err = L2_norm(diff, n);

        // set currX = nextX forward
        for (int i = 0; i < n; i++)
            currX[i] = nextX[i]; 
        ++iter; 
    } 

    // compute the dominant eigenvalue of A inverse using modified Rayleigh quotient 
    double eig = dot_product(y, currX, n) / dot_product(currX, currX, n); 

    // clean up memory
    for (int i = 0; i < n; i++) 
        delete[] L[i] ; 
    delete[] L;  
    for (int i = 0; i < n; i++) 
        delete[] U[i]; 
    delete[] U;

    delete[] currX;  
    delete[] nextX; 
    delete[] y;
    delete[] diff; 
    
    // return 1 / eig because eig is dominant eig of A inverse and we want min eigenvalue of A 
    return 1.0 / eig; 
}
```

**Usage/Example:** Sample output with A =  

      19776.7761        1529.0000        1421.0000          93.0000
       1529.0000       15303.0000        4003.0000        4290.0000
       1421.0000        4003.0000       17794.0000        3949.0000
         93.0000        4290.0000        3949.0000        9196.9832

The result is 6611.17, which is indeed the smallest magnitude eigenvalue according to WolframAlpha. 


**Last Modified:** 12/11/19
