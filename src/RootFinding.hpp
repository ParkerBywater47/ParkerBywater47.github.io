#ifndef ROOTFINDING_H
#define ROOTFINDING_H

const double cosh_function_prime(double x); 

const double cosh_function(double x)  ; 

double bisect_newton_hybrid(const double (*f)(double), const double (*df)(double), double a, double b, const double tol) ; 

double secant(const double (*f)(double), const double x0, const double x1, const double tol, const int max_iter) ;

double newton(const double (*f)(double), const double (*df)(double), const double initial, const double tol, const int max_iter); 

double bisection(const double (*f)(double), double a, double b, const double tol) ;


















#endif 
