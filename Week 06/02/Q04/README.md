# Q04 - Matrix Chain Multiplication using Dynamic Programming (originally Q08)

## Question Title

Given the dimensions of `N-1` matrices in an array `arr[]`, determine the minimum number of scalar multiplications required to compute the full matrix chain product.

## How the Code Works

This uses dynamic programming to compute the minimum multiplication cost for each sub-chain of matrices.

If matrices `A[i..j]` are multiplied, then the split point `k` determines:

$$
dp[i][j] = \min_{i \le k < j} \left(dp[i][k] + dp[k+1][j] + p[i-1]p[k]p[j]\right)
$$

## Complexity Analysis

- Time complexity: $O(N^3)$
- Space complexity: $O(N^2)$

## Sample Output

```text
Enter number of matrices: 3
Enter 4 dimensions: 10 30 5 60
Minimum scalar multiplications: 4500
```

Note: the program expects `m` (number of matrices) and then `m+1` dimensions `p0 p1 ... p_m`. The implementation uses heap allocation for the DP table to avoid stack VLAs.