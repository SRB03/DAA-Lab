## DAA Lab Assignment: Selection Sort & Loop Invariants

Based on the problem description in the image, the algorithm being discussed is **Selection Sort**.

### 1. Pseudocode
```text
SELECTION-SORT(A)
n = A.length
for i = 1 to n - 1
    min_idx = i
    for j = i + 1 to n
        if A[j] < A[min_idx]
            min_idx = j
    exchange A[i] with A[min_idx]
```

### 2. Loop Invariant
At the start of each iteration of the outer `for` loop (indexed by `i`), the subarray `A[1 ... i-1]` contains the `i-1` smallest elements of the entire array `A`, and they are in sorted (monotonically increasing) order. The remaining subarray `A[i ... n]` contains the rest of the elements originally in `A`.

### 3. Why run for only the first (n - 1) elements?
The algorithm only needs to run for the first `n - 1` elements because after the `(n - 1)`-th iteration, the subarray `A[1 ... n-1]` will contain the `n - 1` smallest elements in sorted order. By process of elimination, the single remaining element residing in `A[n]` must be the largest element in the array. Since it is the only element left, it is already in its correct, final position. Thus, completing an `n`-th iteration is redundant.

### 4. Worst-case Running Time
The outer loop iterates `n - 1` times. For a given `i`, the inner loop iterates `n - i` times. 
The total number of comparisons is given by the arithmetic series sum:
$$(n - 1) + (n - 2) + \dots + 1 = \frac{n(n - 1)}{2}$$

Expanding this gives $\frac{n^2}{2} - \frac{n}{2}$. In $\Theta$-notation, we drop the lower-order terms and constant coefficients, which evaluates to **$\Theta(n^2)$**.

### 5. Best-case Running Time
**No, the best-case running time is not any better.** 
Selection sort must scan all remaining elements to find the absolute minimum in every iteration, regardless of whether the array is already sorted or partially sorted. The inner loop condition is unconditionally evaluated over the remaining items. Therefore, the number of comparisons remains exactly $\frac{n(n - 1)}{2}$, yielding a best-case running time of **$\Theta(n^2)$**.