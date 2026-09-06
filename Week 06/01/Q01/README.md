# Q01 - Complexity of 1D Array Operations

## Question Title

Given an array with `n` unsorted integer elements, determine the worst-case complexity of the following operations:

1. Finding the maximum element
2. Finding the first and second largest elements
3. Finding the mean
4. Finding the median
5. Finding the standard deviation
6. Finding the mode
7. Removing all duplicates
8. Reversing the elements of the array
9. Partitioning around a random pivot

## How the Code Works

The C program implements the major tasks on a sample unsorted array and prints the result of each operation. It uses:

- a linear scan for finding the maximum
- a simple O(n^2) sort for computing the median (selection-style)
- an O(n^2) frequency scan to compute the mode and to remove duplicates (no hashing used)
- a reverse loop for reversing the array
- a partition routine that locates the given pivot value (if present), moves it to the end, and performs a Lomuto partition

## Complexity Analysis

| Operation | Worst-case Time Complexity | Notes |
| --- | --- | --- |
| Maximum element | $O(n)$ | Single pass through the array |
| First and second largest | $O(n)$ | One pass with tracking of two maxima |
| Mean | $O(n)$ | Sum all elements |
| Median | $O(n^2)$ | Current code uses a simple O(n^2) sort on a temporary array |
| Standard deviation | $O(n)$ | Sum squared deviations after computing mean |
| Mode | $O(n^2)$ | Current code uses an O(n^2) frequency scan (no hashing) |
| Removing duplicates | $O(n^2)$ | Current code uses a scan that preserves first occurrences |
| Reversing | $O(n)$ | One swap per pair |
| Partitioning around a pivot | $O(n)$ | One scan through the array |

## Sample Output

```text
Original array: 9 3 7 2 9 5 8 1 7 4 6 9
Maximum: 9
First largest: 9
Second largest: 9
Mean: 6.25
Median: 6.50
Standard deviation: 2.46
Mode: 9
Array after removing duplicates: 9 3 7 2 5 8 1 4 6
Reversed array: 9 6 4 7 1 8 5 9 2 7 3 9
Partitioned array around pivot 7 (example): 1 3 4 2 5 6 7 9 8 9 7 9

Note: exact partitioned order may vary depending on which pivot occurrence is located first; the program locates a pivot value and then applies Lomuto partitioning.
```
