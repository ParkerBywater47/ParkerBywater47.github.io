**Routine Name:** centeredDifferenceExample 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes a centered difference quotient approximation of f(x) = x^4 + x^2 at x = 1. 

**Input:** None. 

**Output:** Prints the successively more accurate approximations of the derivative of the function. 

**Usage/Example:** Sample output when run from my machine. 

    Approximating the derivative of f(x) = x^4 + x^2 at x = 1 using a two sided difference quotient
    Maximum number of iterations is 100.
    approx value of f'(x): 7.0                    h: 0.5
    approx value of f'(x): 6.25                   h: 0.25
    approx value of f'(x): 6.0625                 h: 0.125
    approx value of f'(x): 6.015625               h: 0.0625
    approx value of f'(x): 6.00390625             h: 0.03125
    approx value of f'(x): 6.0009765625           h: 0.015625
    approx value of f'(x): 6.000244140625         h: 0.0078125
    approx value of f'(x): 6.00006103515625       h: 0.00390625
    approx value of f'(x): 6.0000152587890625     h: 0.001953125
    approx value of f'(x): 6.000003814697266      h: 9.765625E-4
    approx value of f'(x): 6.000000953674316      h: 4.8828125E-4
    approx value of f'(x): 6.000000238418579      h: 2.44140625E-4
    approx value of f'(x): 6.000000059603735      h: 1.220703125E-4
    approx value of f'(x): 6.000000014901161      h: 6.103515625E-5
    approx value of f'(x): 6.00000000372529       h: 3.0517578125E-5
    approx value of f'(x): 6.000000000931323      h: 1.52587890625E-5
    approx value of f'(x): 6.000000000232831      h: 7.62939453125E-6
    approx value of f'(x): 6.000000000029104      h: 3.814697265625E-6
    approx value of f'(x): 6.0                    h: 1.9073486328125E-6
    approx value of f'(x): 6.0                    h: 9.5367431640625E-7
    approx value of f'(x): 6.0                    h: 4.76837158203125E-7
    approx value of f'(x): 6.0                    h: 2.384185791015625E-7
    approx value of f'(x): 6.0                    h: 1.1920928955078125E-7
    approx value of f'(x): 6.0                    h: 5.9604644775390625E-8
    approx value of f'(x): 6.0                    h: 2.9802322387695312E-8
    approx value of f'(x): 6.000000007450581      h: 1.4901161193847656E-8
    approx value of f'(x): 6.0                    h: 7.450580596923828E-9
    approx value of f'(x): 6.0                    h: 3.725290298461914E-9
    approx value of f'(x): 6.0                    h: 1.862645149230957E-9
    approx value of f'(x): 6.0                    h: 9.313225746154785E-10
    approx value of f'(x): 6.0                    h: 4.6566128730773926E-10
    approx value of f'(x): 6.0                    h: 2.3283064365386963E-10
    approx value of f'(x): 6.0                    h: 1.1641532182693481E-10
    approx value of f'(x): 6.0                    h: 5.820766091346741E-11
    approx value of f'(x): 6.0                    h: 2.9103830456733704E-11
    approx value of f'(x): 6.0                    h: 1.4551915228366852E-11
    approx value of f'(x): 6.0                    h: 7.275957614183426E-12
    approx value of f'(x): 6.0                    h: 3.637978807091713E-12
    approx value of f'(x): 6.0                    h: 1.8189894035458565E-12
    approx value of f'(x): 6.0                    h: 9.094947017729282E-13
    approx value of f'(x): 6.0                    h: 4.547473508864641E-13
    approx value of f'(x): 6.0                    h: 2.2737367544323206E-13
    approx value of f'(x): 6.0                    h: 1.1368683772161603E-13
    approx value of f'(x): 6.0                    h: 5.6843418860808015E-14
    approx value of f'(x): 6.0                    h: 2.8421709430404007E-14
    approx value of f'(x): 6.0                    h: 1.4210854715202004E-14
    approx value of f'(x): 6.0                    h: 7.105427357601002E-15
    approx value of f'(x): 6.0                    h: 3.552713678800501E-15
    approx value of f'(x): 6.0                    h: 1.7763568394002505E-15
    approx value of f'(x): 6.0                    h: 8.881784197001252E-16
    approx value of f'(x): 6.0                    h: 4.440892098500626E-16
    approx value of f'(x): 6.0                    h: 2.220446049250313E-16
    approx value of f'(x): 6.0                    h: 1.1102230246251565E-16
    approx value of f'(x): NaN                    h: 5.551115123125783E-17

**Implementation/Code:** The following is the code for a CeneteredDifferenceExample class:
   
```java
import java.lang.Math.*; 

public class CenteredDifferenceExample {  
    public static void main(String[] args) {
        System.out.println("\nApproximating the derivative of f(x) = x^4 + x^2 at x = 1 using a two sided" + 
	"difference quotient\nMaximum number of iterations is 100.");
        differenceQuotient( 1, 100);
    }

    /**
     * Computes centered difference quotient for the function f(x) = x^4 + x^2
     * @param x The value at which f(x) is to be computed
     * @param maxIterations maximum number of iterations
     * @author Parker Bywater
     */
    public static void differenceQuotient(double x, int maxIterations) {
        // print the approximate value of f'(x) and the value of h each iteration of the loop =
        // set h = 1/2*h after each loop
        double h = .5;
        double diff = 1; // dummy value to enter while loop
        int iter = 0; // number of iterations completed
        while (Double.isFinite(diff) && iter < maxIterations) {
            double numerator = Math.pow(x + h, 4) + Math.pow(x + h, 2) - (Math.pow(x-h, 4) + Math.pow(x-h, 2));
            double denominator = (x + h) - (x - h);
            diff = numerator / denominator;
            System.out.printf("%-45s %-20s\n", "approx value of f'(x): " + diff, "h: " + h);
            h = .5 * h;
            iter++;	
	}
}
```

**Last Modified:** 9/16/19
