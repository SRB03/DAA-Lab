# Design and Analysis of Algorithms (DAA) - Lab 02

This folder contains the C implementations and Python plotting scripts for DAA Lab 02, focusing on algorithmic time complexity analysis.

## Questions Overview

| Question | Brief Description |
| :--- | :--- |
| **Q1: Dictionary Operations** | Implements and analyzes the worst-case time complexities of 7 dictionary operations (Search, Insert, Delete, Max, Min, Predecessor, Successor) across various data structures (Unsorted/Sorted Arrays, Singly/Doubly Linked Unsorted/Sorted Lists). Includes Python plots for validation. |
| **Q2: Merge Sort Modifications** | Compares the standard 2-way merge sort against a modified 3-way merge sort (dividing the array into thirds). Plots the order of growth for both approaches. |
| **Q3: Merging K Sorted Arrays** | Evaluates two methods for merging *k* sorted arrays of size *n*. Method 1 uses sequential merging, while Method 2 uses a divide-and-conquer pairwise merging strategy. |

## Folder Structure

```text
.
├── Q01/
│   ├── q1.c                    # C implementation of Dictionary Operations
│   ├── plot.py                 # Python script to plot time complexities
│   ├── benchmark.csv           # Generated execution time data
│   ├── README.md               # Specific instructions for Q1
│   └── plots/                  # Directory containing generated graphs (.png)
├── Q02/
│   ├── q2.c                    # C implementation of 2-way and 3-way Merge Sort
│   ├── plot.py                 # Python script to plot sorting times
│   ├── merge_sort_results.csv  # Generated execution time data
│   ├── README.md               # Specific instructions for Q2
│   └── merge_sort_plot.png     # Generated comparison graph
└── Q03/
    ├── main.c                  # Main driver code for k-way merges
    ├── method1.c               # Sequential merge implementation
    ├── method2.c               # Divide & Conquer merge implementation
    ├── README.md               # Specific instructions for Q3
    └── output.png              # Generated comparison graph
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
(depends on ur particular distro's package manager (`dnf`, `apt`))

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