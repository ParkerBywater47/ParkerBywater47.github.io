**Routine Name:** LU_solver

**Author:** Parker Bywater

**Language:** C++. Pick your favorite compiler (probably g++).   

**Description/Purpose:** This routine solves a square system of linear equations using the LU-factorization 
of the coeffecient matrix. 

**Input:** Lower and upper triangular matrices, a vector to solve for, a memory location to store the solution, and the dimension of the matrix. 
 
**Output:** This routine writes the solution of the system to the parameter 'x[]'.

**Implementation/Code:** The following is the code for LU\_solver.
```C++ 
using namespace std; 

void up_triangular_back_sub(double *U[], int n, double b[], double x[]);
void lower_triangular_fwd_sub(double *L[], int n, double b[], double x[]); 

void LU_solver(double *L[], double *U[], int n, double b[], double x[]) 
{
    // solve Ly = b 
    double y[n]; 
    lower_triangular_fwd_sub(L, n, b, y); 

    // solve Ux = y
    up_triangular_back_sub(U, n, y, x);  
}

void up_triangular_back_sub(double *U[], int n, double b[], double x[]) 
{
    x[n - 1] = b[n - 1] / U[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        double thatSum = 0;
        for (int j = i + 1; j < n; j++)
        {
            thatSum += U[i][j] * x[j];
        }
        x[i] = (b[i] - thatSum) / U[i][i];
    }
}


void lower_triangular_fwd_sub(double *L[], int n, double b[], double x[]) 
{
    x[0] = b[0] / L[0][0];
    for (int i = 1; i < n; i++) {
        double thatSum = 0;
        for (int j = i - 1; j >= 0; j--) 
        {
            thatSum += L[i][j] * x[j];
        }       
        x[i] = (b[i] - thatSum) / L[i][i];
    }
}

```
**Usage/Example:** Sample output with L = 

    1.0000   0.0000   0.0000   0.0000   0.0000
    0.6450   1.0000   0.0000   0.0000   0.0000
    0.5100   1.1060   1.0000   0.0000   0.0000
    0.9830   0.5680   14.5960  1.0000   0.0000
    1.8910   0.7470   18.9800  1.3880   1.0000

and U = 
        
    10.0668  5.8928   18.7510   15.2897    7.7862
    0.0000   7.9274    8.1680   -2.3544   13.7617
    0.0000   0.0000   -1.5204    5.5468   -0.3611
    0.0000   0.0000    0.0000  -85.5213   -2.6918
    0.0000   0.0000    0.0000    0.0000   -5.1434

and b = 
    
    8
    17
    24
    13
    4
    
The value stored in x is then 

    -0.566967
    -0.406618
    -0.790551
     1.12811
     1.75681


**Last Modified:** 12/4/19
