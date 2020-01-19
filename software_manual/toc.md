# Software Manual

## Numerical Analysis Routines

### Basic Routines
* [Single Machine Precision](./single_machine_precision.md) - Computes machine epsilon for single precision floating point numbers. 
* [Double Machine Precision](./double_machine_precision.md) - Computes machine epsilon for double precision floating point numbers.
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
Many of these routines use a Matrix class I defined. It's essentially a nice container for two-dimensional arrays. The source is [here](./Matrix.cpp).  
* [Dot Product](./dot_product.md) - Computes the dot product of two vectors. 
* [Cross Product](./cross_product.md) - Computes the cross product of two three-dimensional vectors. Someday I'll implement the seven-dimensional cross product [(check out the 7D-cross product)](https://en.wikipedia.org/wiki/Seven-dimensional_cross_product#Coordinate_expressions). 

* [Matrix-Vector Multiplication](./left_matrix_vector_mult.md) - Computes Ax where A is a matrix and x is a vector. 
* [SAXPY](./saxpy.md) - Computes single-precision a\*x + y where a is a scalar and x and y are vectors. 

* Gaussian Elimination - Performs Gaussian elimination on a square matrix. My library includes an
in-place implementation (to save memory) and an implementation that initially copies the matrix given
into a new matrix to not alter the given data if necessary. 
    * [In-place](./gauss_elim_square_in_place.md)
    * [Memory Hog](./gauss_elim_square.md)
* LU-factorization - Computes the LU-factorization of a square matrix. Like before I have both an in-place implementation and an implementation which copies the data given. But, the in-place implementation 
used here is a compressed storage version of the LU-factorization of a matrix. Given that the diagonal entries of the lower-triangular matrix are always 1, we can "merge" L and U into one matrix that stores
the important information of the LU-factorization.  
    * [Compressed Storage](./LU_compressed.md)
    * [Memory Hog](./LU.md) 

* [Diagonal Solver](./diagonal_solver.md) - Solves a diagonal system of linear equations. 
* [Square Solver](./square_solver.md) - Solves a square system of linear equations. 
* [LU Solver](./LU_solver.md) - Solves a square system of linear equations given the LU-factorization of the coeffecient matrix. 


## Leetcode Problems
* [Two Sum](./two_sum.md)
* [Add Two Numbers](./add_two_numbers.md)
* [Median of Two Sorted Arrays](./median_sorted_arrays.md)


