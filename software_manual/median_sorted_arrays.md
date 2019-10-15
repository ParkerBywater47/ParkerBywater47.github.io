**Routine Name:** findMedianSortedArrays

**Author:** Parker Bywater

**Language:** Java. This can be compiled using an appropriate Java compiler. 

**Description/Purpose:** This routine solves the prob

**Input:** 

**Output:** This routine returns 

**Implementation/Code:** The following is the code for
   
```java 
public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
    // Check to see if the smallest element of one array is larger than the largest of another.
    int len1 = nums1.length;
    int len2 = nums2.length;
    boolean pickTwo = (len1 + len2) % 2 == 0;
    if (len1 == 0) {
        if (len2 % 2 == 0)
            return (nums2[nums2.length/2 -1] + nums2[nums2.length/2]) / 2.0;
        return nums2[nums2.length / 2];
    }
    else if (len2 == 0) {
        if (len1 % 2 == 0)
            return (nums1[nums1.length/2 -1] + nums1[nums1.length/2]) / 2.0;
        return nums1[nums1.length / 2];
    }
    int p1 = 0;
    int p2 = 0;
    // if the len of the merged arrays would be even we need to select two elements and return their average
    if (pickTwo) {
        if (len1 + len2 == 2)
            return (nums1[0] + nums2[0]) / 2.0;
        int elementsToCount = (len1 + len2) / 2 - 1;
        for (int elementsCounted = 0; elementsCounted <= elementsToCount; elementsCounted++) {
            // first check that the pointers are within bounds
            if (p1 < len1 && p2 < len2) {
                int e1 = nums1[p1];
                int e2 = nums2[p2];
                if (e1 < e2) {
                    if (elementsCounted >= elementsToCount) {
                        int nextNums1;
                        // check that I can look in nums1 for the next integer without throwing indexOutOfBounds
                        if (p1 + 1 < len1) {
                            nextNums1 = nums1[p1 + 1];
                            if (nextNums1 < e2)
                                return (e1 + nextNums1) / 2.0;
                        }
                        return (e1 + e2) / 2.0;
                    }
                    p1++;
                } else if (e1 == e2) {
                    if (elementsCounted == elementsToCount)
                        return (e1 + e2) / 2.0;
                    if (elementsCounted % 2 == 0)
                        p1++;
                    else
                        p2++;
                } else { // e1 > e2
                    if (elementsCounted >= elementsToCount) {
                        int upperElement2;
                        if (p2 + 1 < len2) {
                            upperElement2 = nums2[p2 + 1];
                            if (upperElement2 < nums1[p1]) {
                                return (nums2[p2] + upperElement2) / 2.0;
                            }
                            return (nums2[p2] + nums1[p1]) / 2.0;
                        }
                        return (nums1[p1] + nums2[p2]) / 2.0;
                    }
                    p2++;
                }
            }
            else if (p1 < len1) {
                if (elementsCounted == elementsToCount)
                    return (nums1[p1] + nums1[p1 + 1]) / 2.0;
                p1++;
            } else {
                if (elementsCounted == elementsToCount)
                    return (nums2[p2] + nums2[p2 + 1]) / 2.0;
                p2++;
            }
        }
    // length of merged array is odd case
    } else {
        int target = (len1 + len2) / 2;
        for (int counter = 0; counter <= target; counter++) {
            if (p1 < len1 && p2 < len2) {
                if (nums1[p1] < nums2[p2]) {
                    if (counter == target)
                        return nums1[p1];
                    else
                        p1++;
                } else if (nums1[p1] == nums2[p2]) {
                    counter++;
                    if (counter == target || counter == target + 1)
                        return nums1[p1];
                    else {
                        p1++;
                        p2++;
                    }
                } else {
                    if (counter == target)
                        return nums2[p2];
                    else
                        p2++;
                }
            } else if (p1 < len1) {
                if (counter == target)
                    return nums1[p1];
                else
                    p1++;
            } else {
                if (counter == target)
                    return nums2[p2];
                else
                    p2++;
            }
        }
    }
    return -2000000000; // placeholder return value as the java compiler can't prove the correctness of the algorithm
}
```

**Usage/Example:** Sample output  


**Last Modified:** 6/23/19
