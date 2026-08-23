# Design and Analysis of Algorithms (DAA) - Lab 04

This folder contains the C implementations and outputs for DAA Lab 04, focusing on different applications of sorting.

## Questions Overview

| Question | Brief Description |
| :--- | :--- |
| **Q1: Application of sorting-I** | Give an $O(n)$ algorithm to sort $n$ pairs of items (number, colour) by colour (all reds before all blues before all yellows) such that numbers for identical colours stay sorted. |
| **Q2: Application of sorting-II** | Describe an $O(n \cdot \log n)$ algorithm for finding whether there exists a pair of elements, one from set $S_1$ and one from set $S_2$, that add up to $x$. |
| **Q3: Application of sorting-III** | Give an $O(n^{k-1} \cdot \log n)$ algorithm to test whether $k$ integers in a set $S$ of $n$ integers add up to an integer $T$. |
| **Q4: Application of sorting-IV** | Give an $O(n \cdot \log n)$ algorithm to determine the time when the most people were simultaneously present at a party, using tracking entry time $a_i$ and exit time $b_i$. |
| **Q5: Application of sorting-V** | Given a list $I$ of $n$ intervals specified as $(x_i, y_i)$ pairs, return a list where overlapping intervals are merged in worst-case $O(n \cdot \log n)$ time. |
| **Q6: Application of sorting-VI** | Give an $O(n \cdot \log n)$ algorithm to identify a point $p$ on a line that is in the largest number of given $n$ intervals. |

## Folder Structure

```text
.
├── Q01
│   ├── a.out
│   ├── output.png
│   ├── q1.c
│   └── README.md
├── Q02
│   ├── a.out
│   ├── output.png
│   ├── q2.c
│   └── README.md
├── Q03
│   ├── a.out
│   ├── output.png
│   ├── q3.c
│   └── README.md
├── Q04
│   ├── a.out
│   ├── output.png
│   ├── q4.c
│   └── README.md
├── Q05
│   ├── a.out
│   ├── output.png
│   ├── q5.c
│   └── README.md
├── Q06
│   ├── a.out
│   ├── output.png
│   ├── q6.c
│   └── README.md
└── README.md
```

### Prerequisites

To compile and run the programs in this repository, you will need:
* **C Compiler:** GCC (GNU Compiler Collection) or any standard C compiler.
