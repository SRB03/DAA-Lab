# Q02 - 0/1 Knapsack using Dynamic Programming (originally Q06)

## Question Title

Given `n` items with weights and profits and a knapsack of capacity `W`, determine the maximum profit that can be obtained.

## How the Code Works

The dynamic programming table `dp[i][w]` stores the maximum profit obtainable using the first `i` items and capacity `w`. The implementation uses a heap-allocated contiguous table (`calloc`) to avoid large VLAs on the stack; this reduces stack overflow risk for large `n` or `W`.

Transition:

- If the item does not fit, carry forward the previous value.
- If it fits, choose the better of including or excluding the item.

$$
dp[i][w] = \max(dp[i-1][w],\, p_i + dp[i-1][w-w_i])
$$

## Complexity Analysis

- Time complexity: $O(nW)$
- Space complexity: $O(nW)$

## Sample Output

```text
Enter number of items: 4
Enter capacity: 5
Item 1 weight: 2 profit: 3
Item 2 weight: 3 profit: 4
Item 3 weight: 4 profit: 5
Item 4 weight: 5 profit: 6
Maximum profit: 7
```