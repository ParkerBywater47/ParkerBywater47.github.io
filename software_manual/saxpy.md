**Routine Name:** saxpy 

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine computes a "single-precision ax plus y" operation. In precise terms it computes
the product of a scalar (a) and a vector (x) and adds it to another vector (y).  

**Input:** Two vectors represented as an array of floats and a scalar as a float. 
 
**Output:** This routine returns a\*x + y. 

**Implementation/Code:** The following is the code for saxpy. 
```java 
static float[] saxpy(float a, float[] x, float[] y) {
	if (x.length != y.length)
		throw new IllegalArgumentException("Vectors must be of the same dimension");

    float[] out = new float[x.length];
	for (int i = 0; i < out.length; i++)
    	out[i] = a * x[i] + y[i];
	return out;
}
```

**Usage/Example:** Sample output with a = 3.14159, x = (1,2,3,4,5), and y = (1,2,3,4,5).   
    
	[4.14159, 8.28318, 12.42477, 16.56636, 20.70795]

**Last Modified:** 10/31/19
