**Routine Name:**    singleMachinePrecision

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine will compute the single precision value for the machine epsilon or the number of digits
in the representation of real numbers in single precision. This is a routine for analyzing the behavior of any computer. This
usually will need to be run one time for each computer.

**Input:** None.

**Output:** This routine returns a two-element array with the first value being the number of binary digits that can be accurately 
represented on the computer being queried and the second being the smallest decimal number which was computed. 

**Usage/Example:**   The following sample output was generated as follows. A file named SingleMachinePrecision.java defines the public class SingleMachinePrecision which contains only `singleMachinePrecision()` as a public static method. Another file named TestSingleMachinePrecision.java defines the public class TestSingleMachinePrecision which contains only a standard Java `main()` method which calls `singleMachinePrecision()` and prints the values. Compiling and running these using Cygwin as follows produces the sample output.

        $ javac SingleMachinePrecision.java
        $ javac TestSingleMachinePrecision.java
        $ java TestSingleMachinePrecision
        
        Number of accurate binary digits: 23
        Smallest float value computed: 1.1920929E-7

As labeled, 23 is the number of binary digits that define the machine epsilon and the last line is the smallest decimal number
which was computed. The power (-7) implies that my machine can represent roughly 7 decimal digits accurately.

**Implementation/Code:** The following is the code for `singleMachinePrecision()`. Code for the SingleMachinePrecision and TestSingleMachinePrecision classes is not provided here becuase I assume the reader knows how to define a Java class with a method.

```java 
public static float[] singleMachinePrecision() {
    int iPow = 0;
    float epsilon = 1;
    float diff = 1;     // dummy value to make compiler behave
    float smallest;     // the smallest value
    do {
        smallest = diff;
        diff = (1 + epsilon * (float)(Math.pow(.5, ++iPow))) - 1;   // Math.pow returns a double
    } while (diff != 0);

    float[] outArray = {iPow - 1, smallest};
    return outArray;    // returns iPow -1 because the value stored in iPow when the loop terminates was
                        // the value which made diff = 0.
}
```

**Last Modified:** 9/15/19
