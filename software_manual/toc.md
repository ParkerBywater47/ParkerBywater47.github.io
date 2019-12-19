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
* [Dot Product](./dotProduct.md) - Computes the dot product of two vectors. 
* [Cross Product](./crossProduct.md) - Computes the cross product of two three-dimensional vectors. Someday I'll implement the seven-dimensional cross product [(check out the 7D-cross product)](https://en.wikipedia.org/wiki/Seven-dimensional_cross_product#Coordinate_expressions). 
* [Matrix-Vector Multiplication](./left_matrix_vector_mult.md) - Computes Ax where A is a matrix and x is a vector. 
* [SAXPY](./saxpy.md) - Computes single-precision Ax + y where A is a matrix and x and y are vectors. 
* [LU](./LU.md) - Computes the LU facorization of a matrix. 
* [Diagonal Solver](./diagonalSolver.md) - Solves a diagonal system of linear equations. 
* [Square Solver](./squareSolver.md) - Solves a square system of linear equations. 



## Leetcode Problems
* [Two Sum](./two_sum.md)
* [Add Two Numbers](./add_two_numbers.md)
* [Median of Two Sorted Arrays](./median_sorted_arrays.md)


