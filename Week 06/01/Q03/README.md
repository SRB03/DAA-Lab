# Q03 - Convolution using Divide and Conquer / FFT-style Approach

## Question Title

Given vectors `A` and `B` of lengths `m` and `n` respectively, compute the convolution:

$$
C[k] = \sum_{j=0}^{m-1} A[j] \, B[k-j]
$$

for `n >= m`, and derive an $O(n \log n)$ algorithm.

## How the Code Works

The C program uses a radix-2 FFT (Fast Fourier Transform) to compute the convolution efficiently. It pads the two vectors to the next power of two, applies the FFT to each, multiplies the transformed sequences pointwise, and then performs the inverse FFT. This is the standard divide-and-conquer method used to achieve $O(n \log n)$ complexity.

## Complexity Analysis

- FFT of length `N`: $O(N \log N)$
- Pointwise multiplication: $O(N)$
- Inverse FFT: $O(N \log N)$
- Overall: $O(N \log N)$, which is effectively $O(n \log n)$ for the input size

## Sample Output

```text
A: 1 2 3
B: 4 5 6
Convolution result:
4 13 28 27 18
```
