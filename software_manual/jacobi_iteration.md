**Routine Name:** jacobi_iteration 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine implements the Jacobi method of solving square strictly diagonally dominant systems of linear equations.  

**Input:** Coeffecient matrix A, a right-hand side vector b, an initial guess of the solution, desired tolerance, maximum number of iterations, and a memory location to write the solution. The matrix must be an instance of [this](../src/Matrix.cpp) matrix class.
 
**Output:** This routine computes an approximation of the solution which has an error less than or euqal to the given
tolerance if convergence was not too slow. If convergence was slow the most recently computed approximation will be returned. The solution is written to the parameter `out`. This routine also returns the number of iterations required to find the solution as this can be useful information in some cases. 

**Implementation/Code:** The following is the code for jacobi_iteration. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   
   
```C++ 
int jacobi_iteration(const Matrix& A, const double b[], const double initial_guess[], const double tol, const int max_iter, double out[]) 
{
    const int n = A.get_num_rows();

    int iter = 0;
    double err = 2 * tol;
    double * curr = new double[n];
    double * next = new double[n];
    double * err_vec = new double[n];

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
        subtract_vectors(next, curr, err_vec, n);
        err = L2_norm(err_vec, n); 

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
    delete[] err_vec;
    return iter - 1;
}
```
**Dependencies**: `L2_norm` code [here](./L2_norm.md)

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

