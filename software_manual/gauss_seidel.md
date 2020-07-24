**Routine Name:** gauss_seidel 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine implements the Gauss-Seidel method of solving square systems of linear equations. The coeffecient matrix must be either strictly diagonally dominant or symmetric and positive definite to guarantee convergence. 

**Input:** Coeffecient matrix A, a right-hand side vector b, an initial guess of the solution, desired tolerance, maximum number of iterations, and a memory location to write the solution.  
 
**Output:** This routine computes an approximation of the solution which has an error less than or euqal to the given
tolerance if convergence was not too slow. If convergence was slow the most recently computed approximation will be returned. The solution is written to the parameter `out`. This routine also returns the number of iterations required to find the solution as this can be useful information in some cases. 

**Implementation/Code:** The following is the code for gauss_seidel.
   
```C++ 
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
```

**Usage/Example:** Sample output with A =  

      6.0000    -2.0000      3.0000
     -3.0000     9.0000      1.0000
      2.0000    -1.0000     -7.0000

and b =

    -1
     2
     3

The solution returned is x =
 
    0.155673
    0.3219
    -0.430079

