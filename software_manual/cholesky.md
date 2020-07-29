**Routine Name:** cholesky

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the Cholesky facorization of a positive definite real-valued matrix. 

**Input:** A real-valued positive definite matrix which is an instance of [this](../src/Matrix.cpp) Matrix class.
 
**Output:** This routine returns an instance of `std::pair` with the first being L and the second being L\*. 

**Implementation/Code:** The following is the code for cholesky. 
   
```C++
std::pair<Matrix, Matrix> cholesky(const Matrix& A) 
{ 
    const int n = A.get_num_rows();

    // check that the matrix is symmetric
    if (n != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square to be symmetric"); 

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (A[i][j] != A[j][i])
                throw std::invalid_argument("Matrix must be symmetric");
        }
    }

    std::pair<Matrix, Matrix> out(Matrix(n,n), Matrix(n,n));
    Matrix& L = out.first;
    Matrix& L_trans = out.second;

    // do special gaussian elimination
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

        // compute the diagonal entries
        double sum1 = 0;
        for (int k = 0; k < j; k++)
            sum1 += L[j][k] * L[j][k];
        L[j][j] = sqrt(A[j][j] - sum1);
        L_trans[j][j] = L[j][j]; 
    }
    return out; 
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

