**Routine Name:** square_solve_spp

**Author:** Parker Bywater

**Language:** C++

**Description/Purpose:** This routine solves a square linear system of equations using Gaussian elimination and 
back substitution. This routine performs the Gaussian elimination using scaled partial pivoting (spp) for the sake of greater numerical stability.

**Input:** A square matrix, a right-hand side vector, and a memory location to store the result. The
matrix should be an instance of [this](../src/Matrix.cpp) class and the vector should be an array.
 
**Output:** This routine writes the solution of the system to the provided memory location. 

**Exceptions:** Throws `std::invalid_argument` if A is not square. 

**Implementation/Code:** The following is the code for square_solver. This code includes OpenMP compiler directives to take advantage of multiple threads. To use these, the `omp.h` header
must be included and you must use the `-fopenmp` option when compiling.   

```C++  
inline void square_solve_spp(const Matrix& A, const double b[], double out[])
{
    if (A.get_num_rows() != A.get_num_cols())
        throw std::invalid_argument("Matrix must be square");

    // initialize U and copy the values of A into it
    Matrix U = A;  

    const int n = A.get_num_rows(); 

    // make a copy of b 
    double * c = new double[n];
    # pragma omp parallel for 
    for (int i = 0; i < n; i++)
        c[i] = b[i];

    // pass the work off to the in place version
    square_solve_spp_in_place(U, c, out);

    delete[] c; 
}
```
**Exceptions:** `square_solve_spp_in_place` code [here](./square_solve_spp_in_place.md) 

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
