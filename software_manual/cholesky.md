**Routine Name:** cholesky

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the Cholesky facorization of a positive definite real-valued matrix. 

**Input:** A real-valued positive definite matrix represented as an array of pointers to doubles, the dimension of the array, 
and two more arrays of double pointers, to which, the output will be written.  
 
**Output:** This routine "returns" the lower triangular matrix of the factorization to the parameter "\*L[]" and its
transpose to \*L\_trans[].

**Implementation/Code:** The following is the code for cholesky. 
   
```C++
void cholesky(double *A[], const int n, double *L[], *L_trans[]) {
    // check that the matrix is symmetric
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; )
        {
            if (A[i][j] != A[j][i])
                // just return for now as I don't know much about error handling in C++
                return;
        }
    }

    // do special gaussian elimination
    // first compute L[0][0] = sqrt(A[0][0])
    L[0][0] = sqrt(A[0][0]);
    L_trans[0][0] = L[0][0];
    for (int i = 1; i < n; i++) 
    {
        int j;
        for (j = 0; j < i; j++) 
        {
            // compute the below diagonal entries
            double sum0 = 0.0;
            for (int k = 0; k < j; k++)
                sum0 += L[i][k] * L[j][k];
            L[i][j] = (A[i][j] - sum0) / L[j][j];
            L_trans[j][i] = L[i][j]; 
        }
        // j == i
        // compute the diagonal entries
        double sum1 = 0;
        for (int k = 0; k < j; k++)
            sum1 += L[j][k] * L[j][k];
        L[j][j] = sqrt(A[j][j] - sum1);
        L_trans[j][j] = L[j][j]; 
    }
}    
```

**Usage/Example:** Sample output with A = 
    
    12   5
    5   17
    
The output is 

    L =
          3.4641           0.0000
          1.4434           3.8622

    L* =
          3.4641           1.4434
          0.0000           3.8622


**Last Modified:** 11/24/19
