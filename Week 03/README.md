# Design and Analysis of Algorithms (DAA) - Lab 03

This folder contains the C implementations and Python plotting scripts for DAA Lab 03, focusing on searching algorithms, the divide and conquer approach, and loop invariants.

## Questions Overview

| Question | Brief Description |
| :--- | :--- |
| **Q1: Binary vs Ternary Search** | Implements and compares binary and ternary search on a sorted list to validate that binary search performs better. |
| **Q2: Search the Defective Coin** | Uses a divide and conquer algorithm to identify a single defective (lighter) coin among *n* coins in *O(log n)* time using a balance scale. |
| **Q3: Max and Min using D&C Approach** | Finds the maximum and minimum elements in an array using a divide and conquer approach, ensuring comparisons are bounded by *3n/2*. |
| **Q4: Matrix Multiplication using D&C Approach** | Implements Strassen's divide and conquer method to multiply two *n × n* square matrices. |
| **Q5: Multiply special-pattern square matrices** | Implements an *O(n²)* divide and conquer algorithm to multiply special-pattern square matrices with identical diagonal and off-diagonal blocks. |
| **Q6: Use of loop invariants in sorting** | Implements selection sort, analyzing its loop invariants (initialisation, maintenance, termination) and its Θ-notation worst-case and best-case running time. |

## Folder Structure

```text
.
├── Q01/
│   ├── q1.c                    # C implementation of Binary and Ternary Search
│   ├── plot.py                 # Python script to plot search comparisons
│   ├── search_comps.csv        # Generated comparison data
│   ├── search_comps.png        # Generated comparison graph
│   ├── a.out                   # Compiled executable
│   └── README.md               # Specific instructions for Q1
├── Q02/
│   ├── q2.c                    # C implementation for Defective Coin problem
│   ├── a.out                   # Compiled executable
│   └── README.md               # Specific instructions for Q2
├── Q03/
│   ├── q3.c                    # C implementation for Max and Min D&C
│   ├── a.out                   # Compiled executable
│   └── README.md               # Specific instructions for Q3
├── Q04/
│   ├── q4.c                    # C implementation for Strassen's Matrix Multiplication
│   ├── a.out                   # Compiled executable
│   └── README.md               # Specific instructions for Q4
├── Q05/
│   ├── q5.c                    # C implementation for Special-pattern Matrix Multiplication
│   ├── a.out                   # Compiled executable
│   └── README.md               # Specific instructions for Q5
└── Q06/
    ├── q6.c                    # C implementation for Selection Sort and Loop Invariants
    ├── a.out                   # Compiled executable
    └── README.md               # Specific instructions for Q6
```

## Prerequisites

To compile and run the programs in this repository, you will need:
* **C Compiler:** GCC (GNU Compiler Collection) or any standard C compiler.
* **Python 3.x:** For running the data visualization scripts.
* **Python Libraries:** `pandas` and `matplotlib` for generating the graphs.

## Installing Python

### Windows
1. Download the latest Python installer from the [official Python website](https://www.python.org/downloads/).
2. Run the installer.
3. **Important:** Ensure you check the box that says **"Add Python to PATH"** at the bottom of the installation window before clicking "Install Now".

### Linux
Open your terminal and run the following commands:
```bash
sudo dnf update
sudo dnf install python3 python3-pip
```
*(depends on ur particular distro's package manager (`dnf`, `apt`))*

### macOS
The easiest way to install Python on macOS is using [Homebrew](https://brew.sh/). Open your terminal and run:
```bash
brew install python
```

### Installing Python Dependencies

Once Python is installed, you need to install the required libraries for generating plots. Open your terminal or command prompt and run:

```bash
pip install pandas matplotlib
```
*(Note: If `pip` is not recognized on Linux/Mac, try using `pip3 install pandas matplotlib`)*