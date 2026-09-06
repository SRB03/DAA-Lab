# Q01 - Fibonacci Number using Dynamic Programming (originally Q05)

## Question Title

Write a program to find the `n`th Fibonacci number using dynamic programming.

## How the Code Works

The program uses the standard dynamic programming recurrence:

$$
F(0) = 0, \quad F(1) = 1
$$

and for `n >= 2`:

$$
F(n) = F(n-1) + F(n-2)
$$

It stores intermediate values in an array so each Fibonacci value is computed once. Note: the implementation uses heap allocation (`malloc`) for the DP array and performs basic input validation to avoid stack overflow for large `n`.

## Complexity Analysis

- Time complexity: $O(n)$
- Space complexity: $O(n)$

## Sample Output

```text
Enter n: 10
The 10th Fibonacci number is: 55
```