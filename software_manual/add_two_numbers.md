**Routine Name:** addTwoNumbers

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** Solves the Add Two Numbers problem on leetcode.com. The link to the problem is [here](https://leetcode.com/problems/add-two-numbers/).
A brief description of the problem is the following. Given two non-empty linked lists representing two non-negative integers in reverse order, find their sum and return it as a similar linked list representation. The following ListNode definition is assumed. 

```java 
class ListNode { 
    int val; 
    ListNode next; 
    ListNode(int x) { val = x; } 
}
```

**Input:** Two ListNodes representing the heads of two linked lists. 

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
    

Printing the output to the console shows 

      [1, 4]

**Last Modified:** 2/14/19
