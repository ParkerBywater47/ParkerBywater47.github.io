**Routine Name:** gauss_elim_square 

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine performs gaussian elimination on a square matrix.  

**Input:** A square matrix as an instance of [this](./Matrix.cpp) Matrix class.  
 
**Output:** This routine returns the row echelon form of the matrix as an instance of
the aforementioned Matrix class.   

**Exceptions:** Throws `std::invalid_argument` if the matrix given is not square.

**Implementation/Code:** The following is the code for gauss_elim_square. 
```C++ 
Matrix gauss_elim_square(Matrix& A) {
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");
   
    // Make a copy of the matrix and pass it to the in place Gaussian elimination function  
    Matrix out = A; 
    gauss_elim_square_in_place(out); 
    return out; 
}
```

**Dependencies:**
* `gauss_elim_in_place` code [here](./gauss_elim_in_place.md)

**Usage/Example:** Sample output when the matrix below is passed as input.  
    
    3.6578	    4.3459	    6.6881	   10.1399	    0.9815	
    1.7441	   15.8919	    0.8436	   20.9181	   15.2195	
    19.2112	   12.3691	   16.7053	   14.6983	    0.8400	
    18.3011	   18.6141	   13.1689	    6.6432	    9.8854	
    0.7692	   18.4410	   18.2696	   15.0529	   10.7585
     
The folowing is returned 

    3.6578	    4.3459	    6.6881	   10.1399	    0.9815	
    0.0000	   13.8197	   -2.3453	   16.0833	   14.7515	
    0.0000	    0.0000	  -20.1955	  -26.3885	    6.8461	
    0.0000	    0.0000	    0.0000	  -13.2366	    1.2561	
    0.0000	    0.0000	   -0.0000	    0.0000	   -4.6013 

**Last Modified:** 11/6/19 
