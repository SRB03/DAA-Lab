## Strassen's Matrix Multiplication in C

This file contains a C implementation of **Strassen's Algorithm** for matrix multiplication. It includes dynamic memory allocation, handles non-power-of-2 matrix dimensions using zero-padding, and provides a command-line interface for both randomized and manual matrix inputs.

### How the Code Works

1. **Input & Padding**: The program accepts the desired matrix size `n`. Since Strassen's algorithm inherently works by recursively halving matrices, it requires dimensions that are powers of 2. The code includes a `nextPowerOf2` function that calculates the nearest power of 2 (`m`) greater than or equal to `n`, and pads the extra rows and columns with zeros.
2. **Matrix Initialization**: The user is prompted to choose between generating random matrix values (0-9) or manually inputting them. The program handles the full $N \times N$ grid, while the internal padded space is automatically filled with `0`s.
3. **Recursive Strassen Multiplication**:
   - The matrices are recursively divided into four quadrants (A11, A12, A21, A22, etc.).
   - The algorithm computes 7 intermediate matrices (`M1` to `M7`) using combinations of matrix additions, subtractions, and multiplications.
   - It computes the resulting quadrants of matrix `C` (`C11`, `C12`, `C21`, `C22`) from the `M` matrices.
4. **Memory Management**: At each step of the recursion, dynamic memory is heavily utilized. The `freeMatrix` function meticulously frees the allocated quadrants (`A11`...`C22`) and intermediate states to prevent memory leaks.
5. **Output**: Finally, the code strips the padding and prints the final resulting `n x n` matrix.

### Maths behind this

Standard matrix multiplication takes 8 multiplications for a 2x2 split. Volker Strassen discovered a way to do this using only 7 multiplications by introducing cleverly designed algebraic combinations.

Given matrices $A$ and $B$, split them into 4 quadrants:
$$ A = \begin{bmatrix} A_{11} & A_{12} \\ A_{21} & A_{22} \end{bmatrix}, B = \begin{bmatrix} B_{11} & B_{12} \\ B_{21} & B_{22} \end{bmatrix} $$

**The 7 Strassen Products (M1 to M7):**
* $M_1 = (A_{11} + A_{22}) \cdot (B_{11} + B_{22})$
* $M_2 = (A_{21} + A_{22}) \cdot B_{11}$
* $M_3 = A_{11} \cdot (B_{12} - B_{22})$
* $M_4 = A_{22} \cdot (B_{21} - B_{11})$
* $M_5 = (A_{11} + A_{12}) \cdot B_{22}$
* $M_6 = (A_{21} - A_{11}) \cdot (B_{11} + B_{12})$
* $M_7 = (A_{12} - A_{22}) \cdot (B_{21} + B_{22})$

**Result Matrix $C$ sub-matrices:**
* $C_{11} = M_1 + M_4 - M_5 + M_7$
* $C_{12} = M_3 + M_5$
* $C_{21} = M_2 + M_4$
* $C_{22} = M_1 - M_2 + M_3 + M_6$

### Complexity overview

* **Time Complexity**: 
  Instead of 8 recursive multiplications, Strassen's algorithm only performs 7. 
  The recurrence relation is: $T(N) = 7T(N/2) + \mathcal{O}(N^2)$
  After solving the recurrence relation, time complexity is **$\mathcal{O}(N^{\log_2 7}) \approx \mathcal{O}(N^{2.81})$**.
  This is asymptotically faster than the standard $\mathcal{O}(N^3)$ approach.
  
* **Space Complexity**: **$\mathcal{O}(N^2)$** 
  Because of the recursive nature and the requirement to allocate memory for the sub-matrices (`A11`, `M1`, etc.) at each level of the recursion tree, additional memory proportional to the matrix size is consumed.


#### How to Run

1. You can compile the C code and run the execution command:

```bash
gcc q4.c && ./a.out 
```

2. The program will prompt you to enter the size of the matrix (`n`).
3. Choose your initialization method:
   * **Option 1**: Generates random values (0-9) for the entire $n \times n$ matrices.
   * **Option 2**: Allows you to manually type values for the entire $n \times n$ matrices.
4. The program will display Matrix A, Matrix B, and the Resultant Matrix C (A * B).