**Routine Name:** double_macheps

**Author:** Parker Bywater

**Language:** C++ 

**Description/Purpose:** This routine will determine machine epsilon (macheps) for double precision floating point numbers. This is a routine for analyzing the behavior of any computer. This
usually will need to be run one time for each computer.

**Input:** None.

**Output:** This routine returns double precision macheps.

**Implementation/Code:** The following is the code for `double_macheps` with a main method for demonstration purposes.

```C++ 
#include <iostream>
#include <math.h>


float double_macheps() 
{
    int pow = 0;
    float epsilon = 1;
    float diff;         
    float smallest;         
    do {
        smallest = diff;
        diff = (1 + epsilon * (float)std::pow(1/2.0, ++pow)) - 1;   
    } while (diff != 0);

    return smallest;
}


int main() 
{ 
    std::cout << "double precision machine epsilon: " << double_macheps() << std::endl;

    return 0; 
}
```

**Usage/Example:** To run this code, enter the following commands in your favorite command line environment. 

    $ g++ double_macheps.cpp
    $ ./a.out 

The output should be similar to what's below, although this could vary from machine to machine.

    double precision machine epsilon: 2.22045e-16


**Last Modified:** 9/15/19
