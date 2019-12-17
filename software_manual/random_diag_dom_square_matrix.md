**Routine Name:** random\_diag\_dom\_sqaure\_matrix 

**Author:** Parker Bywater

**Language:** C++. Pick your favorite C++ compiler. 

**Description/Purpose:** This routine generates a "random" diagonally dominant square matrix.  

**Input:** A place to store the matrix, the dimension of the matrix, and a seed for the (psuedo)random number  
generator. 
 
**Output:** This routine returns a square matrix with random entries which is also diagonally dominant. 

**Implementation/Code:** The following is the code for random\_diag\_dom\_sqaure\_matrix. 
   
```C++  
void random_diag_dom_square_matrix(double *out[], const int n, const int seed)
{
    // use a seed so that I can get the same matrix if needed 
    srand(seed); 
    for (int i = 0; i < n; i++)
    {
        double sum = 0; 
        const int max_non_diag_val = (RAND_MAX / n) - 1; 
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                out[i][j] = (double)(rand() % max_non_diag_val);
                sum += fabs(out[i][j]); 
            }
        }
        double num = (double)rand();
        while (fabs(num) <= sum) 
            num = (double)rand(); 
        out[i][i] = num; 
    }
}
```

**Usage/Example:** Sample output with n = 5 and seed = 2000.   

    1809459948.0000     4432358.0000   267858601.0000   106737995.0000   387057710.0000
     397341739.0000  1696108846.0000   338819749.0000   358555904.0000   336038441.0000
     206506458.0000   271635441.0000  1063503700.0000   395629700.0000   112678450.0000
     115549837.0000   286323089.0000   147373156.0000  2112349894.0000    84043442.0000
      28470719.0000    70170982.0000   356308103.0000   203886430.0000  1114900177.0000
    

**Last Modified:** 11/18/19 
