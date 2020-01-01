**Routine Name:** square_solver   

**Author:** Parker Bywater

**Language:** C++. This can be compiled using an appropriate C++ compiler. 

**Description/Purpose:** This routine solves a square linear system of equations using Gaussian elimination and 
back substitution. This routine performs the gaussian elimination naiively, that is, it assumes the matrix is not singular.  

**Input:** A matrix, a right-hand side vector, and a memory location to store the result.   
 
**Output:** This routine writes the solution of the system to the provided memory location. 

**Implementation/Code:** The following is the code for squareSolver.
```C++  
void square_solver(Matrix& A, double b[], double out[]) 
{
    // copy the Matrix  
    Matrix copy = A;

    // do elimination on the matrix
    gauss_elim_in_place(copy); 

    // call function which back-substitutes to get the solution
    up_triangular_back_sub(copy, b, out);
}
```

* Matrix class code [here](./Matrix.cpp)
* Gaussian elimination code [here](./gauss_elim_in_place.md)
* up_triangular_back_sub code [code](./upTriangularBackSub.md). 

**Usage/Example:** Sample output for the matrix A = 

      1.0000	    0.0000	    1.0000	    0.0000	
      0.0000	    5.0000	    0.0000	    1.0000	
    -25.0000	    0.0000	   -1.0000	    0.0000	
      0.0000	 -125.0000	    0.0000	   -1.0000	

and b = 

       6.0000
     -28.0000
    -102.0000
     622.0000

The output solution is 

     4.0000
    -4.9500
     2.0000
    -3.2500

**Last Modified:** 11/8/19
