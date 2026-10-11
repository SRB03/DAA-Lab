# Q04 - Minimum total cost to connect all sticks into one

## Question Title
**[Minimum Cost to Connect Sticks]** You have sticks of lengths L₁, L₂, …, L_n. Connecting two sticks of lengths x and y costs x + y, resulting in a single stick of length x + y. Find the minimum total cost to connect all sticks into one. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## How the Code Works
The sticks are stored in an array (random mode: lengths in [1,100]) and copied into a binary min-heap. While more than one stick remains, the two shortest sticks are popped, their sum is added to the running cost, and the new stick is pushed back. For small inputs the merge steps are printed and the cost is checked against a naive O(n²) version that finds the two minima by linear scans.

## Maths / Logic Behind This
Merging sticks is the same process as building a Huffman tree. If the final merge tree puts stick i at depth `d_i`, then stick i's length is paid once per level it passes through, so the total cost is `Σ L_i · d_i`. Minimising this over all binary trees is exactly the Huffman problem.

**Greedy choice.** The two shortest sticks can be assumed to be siblings at the deepest level: if a longer stick were deeper, swapping it with a shorter one would not increase `Σ L_i d_i`. Merging them first reduces the instance to n − 1 sticks with the same structure, so the greedy rule is optimal by induction.

## Complexity Analysis
- **Time complexity:** O(n log n) (building the heap in O(n), then n − 1 merges each with two pops and one push, O(log n) each).
- **Extra space complexity:** O(n) for the heap.
