**Routine Name:** dot_product 

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine computes the dot prodcut of two vectors.  

**Input:** Two vectors represented as arrays of doubles and the dimension (length) of the arrays. 
 
**Output:** This routine returns the dot product of two vectors. 

**Implementation/Code:** The following is the code for dot_product. 
   
```C++ 
inline double dot_product(const double vec1[], const double vec2[], const int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec1[i] * vec2[i]; 
    return sum;
}
```

**Usage/Example:** Sample output for the vectors (0.1, 0.2, 0.3, 0.4, 0.5) and (6, 7, 8, 9, 10). 

    13.0

**Last Modified:** 11/1/19 
