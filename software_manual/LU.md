**Routine Name:** LU  

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the LU-factorization of a square matrix. It does so assuming that the matrix is nonsigular. This is because life gets very hard when your matrices are singular. 
**Input:** A square nonsingular matrix as an instance of [this](../src/Matrix.cpp). 
 
**Output:** This routine returns the LU-factorization of the matrix as a pair of matrices with the first being L and the second being U.  

**Implementation/Code:** The following is the code for LU. 
```C++
std::pair<Matrix, Matrix> LU(const Matrix& A)
{ 
    const int n = A.get_num_rows();  
    Matrix L(n,n);
    Matrix U(A); 

    for (int i = 0, j = 0; i < n; i++, j++) { L[i][j] = 1.0; }

    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        double pivot = U[r][k];
        #pragma omp parallel 
        #pragma omp for
        for (int i = r + 1; i < n; i++) 
        {
            double multiplier = U[i][k] / pivot;
            for (int j = 0; j < n; j++)
            {
                U[i][j] = U[i][j] - multiplier * U[r][j];
            }
            L[i][k] = multiplier;
        }
    }
    return std::pair<Matrix, Matrix>{L, U};
}  
```

**Usage/Example:** Sample output for the matrix A = 

    19.8241	    1.9444	   14.4131	    3.9102	    5.0844	
    12.6527	    8.7957	   19.6549	   18.4340	   11.4366	
    0.7599	    9.9567	    5.6679	    8.1733	   12.3671	
    7.1706	    8.9150	   20.2907	   19.6673	   15.9366	
    14.8775	   14.3102	    2.3970	   18.8819	   14.3528 

The output is then L = 
    
    1.0000	    0.0000	    0.0000	    0.0000	    0.0000	
    0.6383	    1.0000	    0.0000	    0.0000	    0.0000	
    0.0383	    1.3081	    1.0000	    0.0000	    0.0000	
    0.3617	    1.0870	   -0.4336	    1.0000	    0.0000	
    0.7505	    1.7011	    3.0608	   -6.0638	    1.0000	

and U = 

    19.8241	    1.9444	   14.4131	    3.9102	    5.0844	
     0.0000	    7.5546	   10.4557	   15.9384	    8.1915	
    -0.0000	    0.0000	   -8.5617	  -12.8255	    1.4570	
    -0.0000	    0.0000	    0.0000	   -4.6326	    5.8253	
    -0.0000	    0.0000	    0.0000	    0.0000	   27.4671
