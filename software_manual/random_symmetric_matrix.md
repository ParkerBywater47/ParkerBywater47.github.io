**Routine Name:** random\_symmetric\_matrix 

**Author:** Parker Bywater

**Language:** C++. Pick your favorite C++ compiler. 

**Description/Purpose:** This routine generates a random symmetric matrix. 

**Input:** A storage location for generated matrix, the dimension of the matrix, and a seed for the random
number generator. 
 
**Output:** This routine returns a symmetric matrix with random entries.  

**Implementation/Code:** The following is the code for random\_symmetric\_matrix. 
   
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
    
       4432358.0000  1126852057.0000  1395228179.0000   387057710.0000  1809459948.0000
    1126852057.0000  2115328651.0000  1197813205.0000  2076542816.0000   765535169.0000
    1395228179.0000  1197813205.0000  1696108846.0000  1494996642.0000   701132169.0000
     387057710.0000  2076542816.0000  1494996642.0000  1254623156.0000  1830665362.0000
    1809459948.0000   765535169.0000   701132169.0000  1830665362.0000  1063503700.0000 

**Last Modified:** 11/18/19 
