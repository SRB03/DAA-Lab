# Q02 - Huffman coding with a canonical codebook

## Question Title
**[Huffman Coding]** Given symbol frequencies, construct a prefix-free binary code of minimum expected length, and output the canonical Huffman codebook (where codes are ordered lexicographically by length). By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## How the Code Works
Symbols and frequencies are stored in two parallel arrays. A min-heap (ordered by frequency, then creation order) repeatedly merges the two lightest nodes to build the Huffman tree, and a traversal records each symbol's code length. The symbols are then sorted by (length, symbol) and canonical codes are assigned by incrementing a binary counter and appending zeros when the length grows. The program prints the codebook and validates it.

## Maths / Logic Behind This
**Greedy choice.** In an optimal prefix code the two least frequent symbols can be siblings at the deepest level (exchange argument), so merging them first is safe. Replacing them by one symbol of weight f₁+f₂ leaves a smaller problem of the same type, giving optimal substructure. The total cost `Σ f_i · len_i` equals the sum of the weights of all internal nodes.

**Canonical code.** Only the code *lengths* matter for optimality. Sorting symbols by (length, symbol) and assigning `code₁ = 0…0`, `code_{k+1} = (code_k + 1) · 2^(len_{k+1} − len_k)` yields a prefix-free code with the same lengths, numerically increasing with length, so the codebook is unique and can be rebuilt from lengths alone. A single symbol gets the 1-bit code `0`.

**Validation.** The program checks the prefix-free property, Kraft's equality `Σ 2^(−len) = 1`, that the cost equals the sum of internal-node weights, and that the canonical order is strictly increasing.

## Complexity Analysis
- **Time complexity:** O(n log n) to build the tree (2n − 2 heap operations of O(log n)) and to sort for the canonical order; writing the code strings costs O(Σ len_i), which is O(n²) only in the degenerate (Fibonacci-like) worst case.
- **Extra space complexity:** O(n) for the tree and heap (plus O(Σ len_i) for the code strings).
