**Routine Name:** L2\_norm 

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine computes the magnitude of a vector using in the L2-norm. 

**Input:** A vector represented as an array of doubles.  
 
**Output:** This routine returns the magnitude of the vector given.  

**Implementation/Code:** The following is the code for L2\_norm. 
   
```C++ 
inline double L2_norm(const double vec[], const int n) 
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
}
```

**Usage/Example:** Sample output for the vector (1.1, 1.4, 1.8). 
	
	2.5317977802344327

**Last Modified:** 10/30/19
