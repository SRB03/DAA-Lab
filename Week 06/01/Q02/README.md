# Q02 - Complexity of 2D Matrix Operations

## Question Title

Given a square matrix of order `n`, determine the worst-case complexity of the following matrix operations:

1. Matrix addition
2. Matrix multiplication
3. Checking whether matrix is zero
4. Checking whether matrix is symmetric
5. Finding determinant
6. In-place transpose
7. Finding eigenvalues and eigenvectors

## How the Code Works

The program demonstrates these operations on a small matrix using C. For determinant it uses a recursive cofactor-based approach. For symmetry and zero-check it scans all entries. For transpose, it swaps elements about the diagonal in place. The largest eigenvalue and eigenvector are approximated using the power iteration method for a symmetric matrix.

## Complexity Analysis

| Operation | Worst-case Time Complexity | Notes |
| --- | --- | --- |
| Matrix addition | $O(n^2)$ | Each element processed once |
| Matrix multiplication | $O(n^3)$ | Standard multiplication |
| Zero matrix check | $O(n^2)$ | Scan all entries |
| Symmetric matrix check | $O(n^2)$ | Compare all pairs |
| Determinant | $O(n^3)$ for Gaussian elimination / recursive implementation roughly $O(n!)$ for naive cofactor expansion | Standard exact determinant is expensive |
| In-place transpose | $O(n^2)$ | Each cell swapped once |
| Eigenvalue/eigenvector | Varies; power iteration is roughly $O(k n^2)$ for $k$ iterations | Practical approximate method |

## Sample Output

```text
Matrix A:
1 2 3
4 5 6
7 8 9

Matrix B:
9 8 7
6 5 4
3 2 1

A + B:
10 10 10
10 10 10
10 10 10

A * B:
30 24 18
84 69 54
138 114 90

Is zero matrix? No
Is symmetric? No
Determinant: 0
Transpose in place:
1 4 7
2 5 8
3 6 9
Largest eigenvalue (approx): 1.80
Eigenvector: 0.23 0.59 0.78
```

