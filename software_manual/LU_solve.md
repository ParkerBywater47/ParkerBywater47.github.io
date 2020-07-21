**Routine Name:** LU_solver

**Author:** Parker Bywater

**Language:** C++. Pick your favorite compiler (probably g++).   

**Description/Purpose:** This routine solves a square system of linear equations given the 
LU-factorization of the coeffecient matrix. 

**Input:** Lower and upper triangular matrices, a right-hand side vector, and a memory location to 
store the solution. The matrices should be instances of [this](./Matrix.cpp) class and the vector 
should be an array.   
 
**Output:** This routine writes the solution of the system to the 'out' parameter.

**Implementation/Code:** The following is the code for LU\_solver.
```C++ 
inline void LU_solve(Matrix& L, Matrix& U, double b[], double out[]) 
{
    // solve Lc = b 
    double * c = new double[L.get_num_rows()]; 
    lower_triangular_fwd_sub(L, b, c); 

    // solve Ux = c
    up_triangular_back_sub(U, c, out);  
    delete[] c; 
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
