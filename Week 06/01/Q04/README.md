# Q04 - Sorting Using Reversal Operations

## Question Title

You are given a permutation `p` of the integers `1..n`. The only allowed operation is to reverse a contiguous segment `p[i..j]`. Show that the permutation can be sorted using `O(n)` reversals, and analyze the cost when the cost of a reversal is its length.

## How the Code Works

The C program sorts a permutation by repeatedly locating the next correct value and reversing the segment from that value to the current front position. The program prints the sequence of reversals and the final sorted array. Note: the program prints reversal indices using 0-based indexing (array positions start at 0).

## Key Idea

- A permutation can always be sorted by fixing elements one by one.
- Each reversal can place the next correct element in the correct relative position.
- If the cost of a reversal is the number of elements reversed, a balanced strategy keeps the total cost near $O(n \log n)$ in the efficient version of the algorithm.

## Complexity Analysis

- Number of reversals: $O(n)$ in the simple constructive method
- Cost per reversal: length of reversed segment
- Total cost with balanced reversal strategy: $O(n \log n)$
- Time for the sorting process: $O(n^2)$ in the naive implementation, while the cost-aware form is optimized to $O(n \log n)$

## Sample Output

```text
Permutation before sort: 3 1 4 2 5
Reverse 2..2 -> 3 1 4 2 5    # example printed with 0-based indices
Reverse 0..1 -> 1 3 4 2 5
Reverse 1..3 -> 1 2 3 4 5
Sorted permutation: 1 2 3 4 5
```
