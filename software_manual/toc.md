# Software Manual

## Numerical Analysis Routines

### Basic Routines
* [Single Machine Precision](./single_macheps.md) - Computes machine epsilon for single precision floating point numbers. 
* [Double Machine Precision](./double_macheps.md) - Computes machine epsilon for double precision floating point numbers.
* [Absolute Error](./abs_err.md) - Computes the absolute error between a number, say x, and approximation of a number, say y. 
* [Relative Error](./rel_err.md) - Computes the relative error between a number, say x, and approximation of a number, say y.

### Root Finding Methods
* [Fixed Point Iteration](./fixed_point.md) - Computes the approximate root of a function of a single real variable using a functional iteration technique. 
* [Bisection Method](./bisection.md) - Computes the approximate root of a function of a single real variable using the bisection method. 
* [Newton's Method](./newton.md) - An implementation of Newton's method for computing approximate roots of a function of a single real variable. 
* [Secant Method](./secant.md) - An implementation of the secant method for computing approximate roots of a function of a single real variable.
* [Bisection-Newton Hybrid](./bisectNewtonHybrid.md) - My very own hybrid root finding method which uses Newton's
method for fast convergence and the bisection method to guarantee convergence. 
* [Bisection-Secant Hybrid](./bisectSecantHybrid.md) -  

### Linear Algebra Routines 
Many of these routines use a Matrix class I defined. It's essentially a nice container for two-dimensional arrays. The source is [here](../src/Matrix.cpp).  
* [Dot Product](./dot_product.md) - Computes the dot product of two vectors. 
* [Cross Product](./cross_product.md) - Computes the cross product of two three-dimensional vectors. Someday I'll implement the seven-dimensional cross product [(check out the 7D-cross product)](https://en.wikipedia.org/wiki/Seven-dimensional_cross_product#Coordinate_expressions). 
* [Matrix-Vector Multiplication](./left_matrix_vector_mult.md) - Computes Ax where A is a matrix and x is a vector. 
* [SAXPY](./saxpy.md) - Computes single-precision a\*x + y where a is a scalar and x and y are vectors. 
* Gaussian Elimination - Performs Gaussian elimination on a square matrix. My library includes an
in-place implementation (to save memory) and an implementation that initially copies the matrix given
into a new matrix to not alter the given data if necessary. 
    * [In-place](./gauss_elim_square_in_place.md)
    * [Memory Hog](./gauss_elim_square.md)
* LU-factorization Routines - Computes the LU-factorization of a square matrix. There are two different versions of this. One stores the result in two separate matrices and the other stores the result in one matrix by not storing unimportant information of the LU-factorization. This compressed storage version has both an in-place and copy implementation.  
    * [Compressed Storage](./LU_compressed.md)
    * [Compressed Storage In Place](./LU_compressed_in_place.md)
    * [Memory Hog](./LU.md) 
* [Diagonal Solver](./diagonal_solve.md) - Solves a (square) diagonal system of linear equations. 
* Square System Solvers - Four different implementations here: Two of them use scaled partial pivoting (SPP) to improve the numerical stability of the Gaussian elimination and back substitution method these use to determine the solution. The other two perform the Gaussian elimination more naively and are thus more prone to numerical errors. These are however slightly faster. Both versions just described have an in-place and copy implementation.
    * [Copy](./square_solve.md)    
    * [In-place](./square_solve_in_place.md)
    * [Scaled Partial Pivoting](./square_solve_spp.md)
    * [Scaled Partial Pivoting In-place](./square_solve_spp_in_place.md)
* [LU Solver](./LU_solve.md) - Solves a square system of linear equations given the LU-factorization of the coeffecient matrix. 
* [Cholesky Factorization](./cholesky.md) - Computes the Cholesky factorization of a positive definite real-valued matrix.
* [Jacobi Iteration](./jacobi_iteration.md) - Solves a square stricly diagonally dominant system of linear equations iteratively using the Jacobi method. 
* [Gauss-Seidel Iteration](./gauss_seidel_iteration.md) - Solves a square stricly diagonally dominant system of linear equations iteratively using the Gauss-Seidel method. 

## Leetcode Problems
* [Two Sum](./two_sum.md)
* [Add Two Numbers](./add_two_numbers.md)
* [Median of Two Sorted Arrays](./median_sorted_arrays.md)


