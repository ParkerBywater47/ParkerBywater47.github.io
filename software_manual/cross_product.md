**Routine Name:** cross_product3D	 

**Author:** Parker Bywater

**Language:** C++.  This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine computes the cross product of two 3-dimensional vectors.  

**Input:** Two 3-dimensional vectors represented as arrays of doubles, a memory location to store
the result.  
 
**Output:** This routine writes the cross product of the two vectors to the provided memory location.

**Implementation/Code:** The following is the code for cross_product3D. 
   
```C++ 
void cross_product3D(double vec1[], double vec2[], double out[]) {
    out[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    out[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    out[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}
```

**Usage/Example:** Sample output for (1, 0, 0) and (0, 1, 0).   

    [0.0, 0.0, 1.0]

**Last Modified:** 12/28/19
