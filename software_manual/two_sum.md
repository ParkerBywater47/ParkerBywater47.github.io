**Routine Name:** twoSum

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** Solves the Two Sum problem on leetcode.com. The link to the problem is [here](https://leetcode.com/problems/two-sum/).
A brief description of the problem is the following. Given an array of integers and a target number (an integer) and asked to find the indices 
of two numbers which sum to the target number. You are allowed to assume that there is one unique solution. 

**Input:** An array of integers, and an integer target. 

**Output:** This routine returns the indices of the two numbers having a sum equal to the target as an array.  

**Implementation/Code:** The following is the code for twoSum. 
   
```java 
public static int[] twoSum(int[] data, int target) {
        int[] outArray = new int[2];
        for (int i =0; i < data.length - 1; i++) {
            for (int j = i + 1; j < data.length; j++) {
                if (data[i] + data[j] == target) {
                    outArray[0] = i;
                    outArray[1] = j;
                    return outArray;
                }
            }
        }
    return outArray;
}
```

**Usage/Example:** Sample output with the following inputs

    int[] data = {4, 5, 6, 7, 8}; 
    int target = 13;
    

This returns [1, 4]

**Last Modified:** 2/14/19
