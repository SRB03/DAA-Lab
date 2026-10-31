# Design and Analysis of Algorithms - Lab 11

## Questions Overview

| Question | Description (short one line) |
| :--- | :--- |
| Q01 | Shortest Path on Parity-Constrained Graphs via 0-1 BFS |
| Q02 | Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning |
| Q03 | Bidirectional BFS for Shortest Transformation Sequence in a Word Graph |

## Folder Structure

```text
Week 11/
├── README.md
├── Q01/
│   ├── q1.c
│   └── README.md
├── Q02/
│   ├── q2.c
│   └── README.md
└── Q03/
    ├── q3.c
    └── README.md
```

## Prerequisites

- **C Compiler**: GCC (`gcc` version 9.0+ recommended) or Clang supporting the C99/C11 standard (`-std=c11`).
- **Standard Libraries**: Standard C library headers (`stdio.h`, `stdlib.h`, `string.h`, `stdbool.h`, `stdint.h`, `limits.h`, `time.h`).
- **Compilation & Execution**:
  - Compile Q01: `gcc -std=c11 -O2 -Wall -Wextra "Week 11/Q01/q1.c" -o q1 && ./q1`
  - Compile Q02: `gcc -std=c11 -O2 -Wall -Wextra "Week 11/Q02/q2.c" -o q2 && ./q2`
  - Compile Q03: `gcc -std=c11 -O2 -Wall -Wextra "Week 11/Q03/q3.c" -o q3 && ./q3`
