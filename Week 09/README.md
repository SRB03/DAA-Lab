# Design and Analysis of Algorithms - Lab 09

## Questions Overview
| Question | Description (short one line) |
| :--- | :--- |
| [Q01](./Q01) | Fractional knapsack where each item's value density decays over time |
| [Q02](./Q02) | Huffman coding with a canonical (length-ordered) codebook |
| [Q03](./Q03) | Minimum number of refuelling stops to reach a target distance |
| [Q04](./Q04) | Minimum total cost to connect all sticks into one |
| [Q05](./Q05) | Minimum candies for children with rating constraints (slope greedy) |
| [Q06](./Q06) | Rearrange a string so equal characters are at least K apart |
| [Q07](./Q07) | Minimise array deviation using odd-doubling / even-halving moves |
| [Q08](./Q08) | Minimum number of meeting rooms for a set of intervals |
| [Q09](./Q09) | Hu-Tucker optimal alphabetic binary tree |
| [Q10](./Q10) | Greedy shortest-superstring algorithm versus the exact optimum |

## Folder Structure
```text
Week 09/
├── README.md
├── Q01/
│   ├── q1.c
│   └── README.md
├── Q02/
│   ├── q2.c
│   └── README.md
├── Q03/
│   ├── q3.c
│   └── README.md
├── Q04/
│   ├── q4.c
│   └── README.md
├── Q05/
│   ├── q5.c
│   └── README.md
├── Q06/
│   ├── q6.c
│   └── README.md
├── Q07/
│   ├── q7.c
│   └── README.md
├── Q08/
│   ├── q8.c
│   └── README.md
├── Q09/
│   ├── q9.c
│   └── README.md
└── Q10/
    ├── q10.c
    └── README.md
```

### Prerequisites
- A C compiler supporting C11, e.g. **GCC 9+** (or Clang).
- Standard C library only; no external dependencies. `-lm` is needed because some programs use `math.h`.
- Compile and run any question from its own folder:
  ```bash
  cd Q0X
  gcc qX.c -lm
  ./a.out
  ```
- Every program starts with a menu: `1` = manual input, `2` = randomized input that respects the constraints of that question. After solving, each program runs a built-in validation (brute force, DP, or an optimality check) and prints PASSED / FAILED.
