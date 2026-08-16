## Divide and Conquer: Min-Max Algorithm

This file contains a C program that finds the minimum and maximum elements in an array using the **Divide and Conquer** (Tournament) method.

### How the Code Works
The algorithm recursively divides the array into two halves until it reaches small manageable sub-arrays, then combines the results.

1. **Base Case 1:** If the array has only 1 element, both the minimum and maximum are that single element (0 comparisons).
2. **Base Case 2:** If the array has exactly 2 elements, they are compared with each other to determine the minimum and maximum (1 comparison).
3. **Recursive Step:** For an array of size `n > 2`, it is divided into two halves. The algorithm recursively finds the minimum and maximum of both the left and right halves. 
4. **Combine:** It then compares the maximums of both halves to find the overall maximum, and the minimums of both halves to find the overall minimum (2 comparisons per combine step).

The code tracks the actual number of comparisons made using a pointer (`*comps`), allowing you to compare the empirical performance against theoretical limits.

### Maths behind this
The number of comparisons $T(n)$ for an array of size $n$ can be expressed using a recurrence relation:
- $T(n) = 0$ for $n = 1$
- $T(n) = 1$ for $n = 2$
- $T(n) = 2T(n/2) + 2$ for $n > 2$

To solve this for $n = 2^k$ (where $n$ is a power of 2):
$T(n) = 2 \cdot T(n/2) + 2$
$T(n) = 2(2 \cdot T(n/4) + 2) + 2 = 4 \cdot T(n/4) + 4 + 2$
$T(n) = 2^{k-1} \cdot T(2) + (2^{k-1} + 2^{k-2} + ... + 2)$
$T(n) = \frac{n}{2}(1) + (n - 2) = \frac{3n}{2} - 2$

Thus, the theoretical formula for the exact number of comparisons (when $n$ is a power of 2) is **3n/2 - 2**.

### Complexity overview
- **Time Complexity:** $\mathcal{O}(3n/2)$ 
  Even though it's a divide and conquer algorithm, we process all elements. The total number of comparisons is bounded by $\approx \frac{3n}{2}$, making the overall time complexity strictly linear.
- **Space Complexity:** $\mathcal{O}(\log n)$ 
  Since we are using recursion, the maximum depth of the call stack will be $\log_2(n)$ levels deep. The auxiliary space complexity is $\mathcal{O}(\log n)$.

### Observation and output 
When you run the program, you will notice:
- For $n$ as a power of 2 (e.g., 2, 4, 8, 16, 32), the actual comparisons exactly match the formula $3n/2 - 2$.
- For $n$ not a power of 2, the actual comparisons might deviate slightly from the exact formula because the recursion tree is not perfectly balanced, but it remains extremely close to $\approx \frac{3n}{2}$.
- **Example Output**:
  ```text
  Enter the number of elements for the array: 8
  Generated Array: 4123 124 992 8412 11 345 61 7431 

  Minimum element is 11
  Maximum element is 8412

  Elements in Array (n): 8
  Theoretical formula (3n/2 - 2): 10
  Actual comparisons made: 10
  ```

#### How to Run

1. You can compile the C code and run the execution command:

```bash
gcc q3.c && ./a.out 
```

2. The program will prompt you to enter the number of elements. It will then dynamically allocate the array, populate it with random integer values, and output the computed minimum, maximum, and the comparison counts for analytical purposes.