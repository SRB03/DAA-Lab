# Q03 - Longest Common Subsequence (LCS) using Dynamic Programming (originally Q07)

## Question Title

Given two strings, find the length of their longest common subsequence and display the subsequence.

## How the Code Works

The DP table `dp[i][j]` stores the LCS length for prefixes `X[0..i-1]` and `Y[0..j-1]`.

Recurrence:

- If the last characters match, extend the LCS by 1.
- Otherwise, take the maximum of the two previous states.

$$
LCS(i,j) =
\begin{cases}
LCS(i-1, j-1) + 1 & \text{if } X[i] = Y[j] \\
\max(LCS(i-1, j), LCS(i, j-1)) & \text{otherwise}
\end{cases}
$$

## Complexity Analysis

- Time complexity: $O(mn)$
- Space complexity: $O(mn)$ (current implementation uses a heap-allocated table to avoid large VLAs)

## Sample Output

```text
Enter first string: ABCDGH
Enter second string: AEDFHR
LCS length: 3
LCS: ADH
```
