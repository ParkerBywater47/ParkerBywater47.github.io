**Routine Name:** LU_compressed_in_place

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the LU-factorization of a matrix and stores it in a 
single matrix to save storage space. Read the output section below for more.  

**Input:** A square matrix which is an instance of this [Matrix class](../src/Matrix.cpp). 
 
**Output:** This routine returns a matrix which is a compressed representation of the LU-factorization. This representation essentially merges L and U into one matrix by replacing entries that are always 0 or 1 by the definition of the LU-factorization. This is best understood by looking at the example given at the bottom of the page.

**Implementation/Code:** The following is the code for LU_compressed_in_place. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   
 
```C++ 
void LU_compressed_in_place(Matrix& A) 
{
    const int n = A.get_num_rows();

    for (int k = 0, r = 0; k < n; k++, r++) 
    {
        double pivot = A[r][k];
        #pragma omp parallel for
        for (int i = r + 1; i < n; i++) 
        {
            double multiplier = A[i][k] / pivot;                                               

            // A[r] = A[r] - multiplier * A[r-1]
            for (int j = k; j < n; j++) 
            {
                A[i][j] = A[i][j] - multiplier * A[r][j];                                        
            }
            A[i][k] = multiplier;
        }
    } 
}
```

**Usage/Example:** Sample output with A = 

    10.0668	    5.8928	   18.7510	   15.2897	    7.7862	
    6.4984	   11.7314	   20.2723	    7.5155	   18.7879	
    5.1422	   11.7827	   17.0966	   10.7515	   18.8450	
    9.8980	   10.3043	    0.8913	    9.1373	    7.5222	
    19.0364	   17.0692	   12.7061	   13.7253	    9.2764	

The output is 

    10.0668	    5.8928	   18.7510	   15.2897	    7.7862	
    0.6455	    7.9274	    8.1680	   -2.3544	   13.7617	
    0.5108	    1.1066	   -1.5204	    5.5468	   -0.3611	
    0.9832	    0.5689	   14.5966	  -85.5213	   -2.6918	
    1.8910	    0.7475	   18.9806	    1.3881	   -5.1434	

To clarify what this output is, the LU-factorization of A is L = 

    1.0000	    0.0000	    0.0000	    0.0000	    0.0000	
    0.6455	    1.0000	    0.0000	    0.0000	    0.0000	
    0.5108	    1.1066	    1.0000	    0.0000	    0.0000	
    0.9832	    0.5689	   14.5966	    1.0000	    0.0000	
    1.8910	    0.7475	   18.9806	    1.3881	    1.000

and U = 

    10.0668	    5.8928	   18.7510	   15.2897	    7.7862	
    0.0000	    7.9274	    8.1680	   -2.3544	   13.7617	
    0.0000	    0.0000	   -1.5204	    5.5468	   -0.3611	
    0.0000	    0.0000	    0.0000	  -85.5213	   -2.6918	
    0.0000	    0.0000	    0.0000	    0.0000	   -5.1434

As you can see, the diagonal and above is identical to U while everything below the diagonal is identical to L.
   
