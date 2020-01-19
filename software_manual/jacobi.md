**Routine Name:** JacobiIteration 

**Author:** Parker Bywater

**Language:** C++. Pick your favorite C++ compiler. 

**Description/Purpose:** This routine implements Jacobi method of solving square diagonally dominant systems of 
linear equations.  

**Input:** Coeffecient matrix A, a right-hand side vector, b, an initial guess
of the solution, the dimension of the matrix, desired tolerance, maximum number of iterations, 
and a place to write the solution to memory.  
 
**Output:** This routine returns an approximation of the solution which has an error less than or euqal to the given
tolerance if convergence was not too slow. If convergence was slow the most recently computed approximation will be returned.  

**Implementation/Code:** The following is the code for JacobiIteration.
   
```C++ 
void JacobiIteration(double *A[], double b[], double initial_guess[], const int n, double tol, int max_iter, double out[]) 
{
    int iter = 0;
    double err = 2 * tol;
    double * curr = new double[n];
    double * next = new double[n];

    // make curr = initial_guess
    for (int k = 0; k < n; k++)
        curr[k] = initial_guess[k];

    while (iter++ < max_iter && err > tol) {
        // cout << "curr @ iter: " << iter << endl;
        // print_vector(curr, n);
        // cout << "err = " << err << endl;
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j)
                    sum += A[i][j] * curr[j];
            }
            next[i] = (b[i] - sum) / A[i][i];
        }
        // update the error
        err = fabs(L2_norm(next, n) - L2_norm(curr, n));
        // make curr = next for next iteration
        for (int k = 0; k < n; k++)
            curr[k] = next[k];

    }
    // write the solution to out
    for (int k = 0; k < n; k++)
        out[k] = next[k];
    cout << "iterations = " << iter - 1 << endl; 
    delete[] curr;
    delete[] next; 
}
```

**Usage/Example:** Sample output with A =  

      5.0000    -2.0000      3.0000
     -3.0000     9.0000      1.0000
      2.0000    -1.0000     -7.0000

and b =
    
    -1
     2
     3

The solution returned is x =
    
     0.18612
     0.33123
    -0.42271

**Last Modified:** 11/18/19
