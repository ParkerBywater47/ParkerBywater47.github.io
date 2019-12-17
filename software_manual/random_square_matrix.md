**Routine Name:** random\_square\_matrix 

**Author:** Parker Bywater

**Language:** C++. Pick your favorite C++ compiler. 

**Description/Purpose:** This routine generates a random square matrix. 

**Input:** A place to store the matrix, the dimension of the matrix, and a seed for the (psuedo)random number  
generator. 
 
**Output:** This routine returns a square matrix with random entries. 

**Implementation/Code:** The following is the code for random\_square\_matrix
   
```C++ 
void random_square_matrix(double *out[], const int n, const int seed)
{
    // use a seed so that any matrix can be reproduced if needed 
    srand(seed); 
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++)
            out[i][j] = (double)rand(); 
}
```

**Usage/Example:** Sample output with n = 5 and seed = 2000. 
    
    4432358.0000     1126852057.0000  1395228179.0000   387057710.0000  1809459948.0000
    2115328651.0000  1197813205.0000  2076542816.0000   765535169.0000  1696108846.0000
    1494996642.0000   701132169.0000  1254623156.0000  1830665362.0000  1063503700.0000
    1833536749.0000   715819817.0000  1435863340.0000    84043442.0000   147919237.0000
    2112349894.0000  1746457631.0000  1358661166.0000  1644798287.0000  1062879886.0000
 

**Last Modified:** 11/18/19
