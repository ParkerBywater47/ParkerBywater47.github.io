**Routine Name:**    doubleMachinePrecision

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine will compute the double precision value for the machine epsilon or the number of digits
in the representation of real numbers in single precision. This is a routine for analyzing the behavior of any computer. This
usually will need to be run one time for each computer.

**Input:** None.

**Output:** This routine returns a two-element array with the first value being the number of binary digits that can be accurately 
represented on the computer being queried and the second being the smallest decimal number which was computed. 

**Usage/Example:**
The following sample output was generated as follows. A file named DoubleMachinePrecision.java defines the public class DoubleMachinePrecision which contains only `doubleMachinePrecision()` as a public static method. Another file named TestDoubleMachinePrecision.java defines the public class TestDoubleMachinePrecision which contains only a standard Java `main()` method which calls `doubleMachinePrecision()` and prints the values. Compiling and running these using Cygwin as follows produces the sample output. 

      $ javac DoubleMachinePrecision.java
      $ javac TestDoubleMachinePrecision.java
      $ java TestDoubleMachinePrecision
 
      Number of accurate binary digits: 52
      Smallest float value computed: 2.220446049250313E-16

As labeled, 52 is the number of binary digits that define the machine epsilon and the last line is the smallest decimal number 
which was computed. The power (-16) implies that my machine can represent roughly 16 decimal digits accurately.

**Implementation/Code:** The following is the code for `doubleMachinePrecision()`. Code for the DoubleMachinePrecision and TestDoubleMachinePrecision classes is not provided here becuase I assume the reader knows how to define a Java class with a method. 
   
```java 
public static double[] doubleMachinePrecision() {
    int iPow = 0;
    double epsilon = 1;
    double diff = 1;     // dummy value to make compiler behave
    double smallest;     // the smallest value
    do {
        smallest = diff;
        diff = (1 + epsilon * Math.pow(.5, ++iPow)) - 1;
    } while (diff != 0);

    double[] outArray = {iPow - 1, smallest};
    return outArray;    // returns iPow -1 because the value stored in iPow when the loop terminates was
                        // the value which made diff = 0.
}
```

**Last Modified:** 9/15/19
