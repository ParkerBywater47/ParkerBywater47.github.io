**Routine Name:** random\_diag\_dom\_symmetric\_matrix 

**Author:** Parker Bywater

**Language:** C++. Pick your favorite C++ compiler. 

**Description/Purpose:** This routine generates a random square matrix which is symmetric and diagonally dominant. 

**Input:** A storage location for generated matrix, the dimension of the matrix, and a seed for the random
number generator. 
 
**Output:** This routine returns a symmetric diagonally dominant matrix with random entries.  

**Implementation/Code:** The following is the code for random\_diag\_dom\_symmetric\_matrix. 
   
```C++
void random_symmetric_matrix(double *out[], const int n, const int seed)
{
    srand(seed);
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int num = (double)rand();
            out[i][j] = num;
            out[j][i] = num;
        }
    }
}
```

**Usage/Example:** Sample output with n = 5 and seed = 2000.  

    1809459948.0000     4432358.0000   267858601.0000   106737995.0000   387057710.0000
       4432358.0000  1696108846.0000   397341739.0000   338819749.0000   358555904.0000
     267858601.0000   397341739.0000  1254623156.0000   206506458.0000   271635441.0000
     106737995.0000   338819749.0000   206506458.0000  1063503700.0000   112678450.0000
     387057710.0000   358555904.0000   271635441.0000   112678450.0000  1833536749.0000

**Last Modified:** 11/18/19 
