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

**Output:** This routine returns the sum of the two numbers in a reversed linked list representation.  

**Implementation/Code:** The following is the code for addTwoNumbers. 
   
```java 
public static ListNode addTwoNumbers(ListNode head1, ListNode head2) {
    boolean carryTheOne = false;   
    ListNode currentLL1 = head1;   // the current node of interest in the list headed by head1
    ListNode currentLL2 = head2;   // the current node of interest in the list headed by head2
    ListNode outHead = new ListNode(0); // the head node with a placeholder value as this node's next will actually be returned
    ListNode out = outHead;
    
    // iterate over both linked lists adding numbers until one (or both) of the ends of the lists is reached
    while (currentLL1 != null && currentLL2 != null) {
        // add the two numbers 
        int theSum = currentLL1.val + currentLL2.val;
        
        // if the previous addition resulted in a value greater than or equal to 10
        if (carryTheOne) {
            theSum += 1;
        }
        if (theSum >= 10) {
            carryTheOne = true;
            out.next = new ListNode(theSum - 10);
        } else {
            carryTheOne = false;
            out.next = new ListNode(theSum);
        }
        currentLL1 = currentLL1.next;
        currentLL2 = currentLL2.next;
        out = out.next;
    }
    
    // try to advance to the next element of list1 as the end of list2 could have been reached before that of list1.
    // this would leave elements in list one which haven't been added to the total
    while (currentLL1 != null) {
        int theSum = currentLL1.val;
        if (carryTheOne) {
            theSum += 1;
        }
        if (theSum >= 10) {
            carryTheOne = true;
            out.next = new ListNode(theSum - 10);
        } else {
            carryTheOne = false;
            out.next = new ListNode(theSum);
        }
        currentLL1 = currentLL1.next;
        out = out.next;
    }
    
    // try to advance to the next element of list2 for similar reasons. 
    while (currentLL2 != null) {
        int theSum = currentLL2.val;
        if (carryTheOne) {
            theSum += 1;
        }
        if (theSum >= 10) {
            carryTheOne = true;
            out.next = new ListNode(theSum - 10);
        } else {
            carryTheOne = false;
            out.next = new ListNode(theSum);
        }
        currentLL2 = currentLL2.next;
        out = out.next;
    }
    
    // check to see if the last addition performed resulted in a value greater than or equal to 10
    if (carryTheOne) {
        out.next = new ListNode(1);
    }

    return outHead.next;
}
```

**Usage/Example:** Sample output adding 765 and 43 as their reverse linked list representations. The code below constructs the linked lists and prints 

```java
ListNode h1 = new ListNode(5);
h1.next = new ListNode(6);
h1.next.next = new ListNode(7);

ListNode h2 = new ListNode(3);
h2.next = new ListNode(4);

ListNode result = addTwoNumbers(h1, h2);
System.out.print(result.next.next.val + " -> " + result.next.val + " -> " + result.val + "\n");
```

The following is then output to the console

    8 -> 0 -> 8

**Last Modified:** 6/24/19
