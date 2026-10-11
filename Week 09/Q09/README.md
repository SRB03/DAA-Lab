# Q09 - Hu-Tucker optimal alphabetic binary tree

## Question Title
**[Hu-Tucker Greedy Simulation]*** Given an ordered sequence of weights w₁, w₂, …, w_n, construct an optimal alphabetic binary search tree or merge pattern that maintains the strict in-order sequence of indices while minimizing Σ w_i·depth(i). By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## How the Code Works
The ordered weights are stored in an array (random mode: weights in [1,50]). Phase 1 keeps a sequence of nodes and repeatedly merges the lightest *compatible* pair, putting the new node where the right member stood. Phase 2 reads the depth of every leaf from that tree. Phase 3 scans the leaves left to right with a stack and merges equal-level neighbours, which rebuilds a true alphabetic tree with the same levels. The cost Σ w_i·depth_i and the tree are printed, and an O(n³) interval DP validates optimality (n ≤ 150).

## Maths / Logic Behind This
In an *alphabetic* tree the leaves must stay in the given order, so the unrestricted Huffman merge (any two lightest nodes) is not allowed. Hu–Tucker restores this with the notion of compatibility: two nodes can be merged only if no original leaf (terminal) lies strictly between them in the current sequence, otherwise merging them could force a leaf to be placed out of order.

1. **Combination:** choose the compatible pair with the minimum total weight (ties: leftmost) and merge. The resulting tree T₁ need not be alphabetic, but its leaf levels are the right ones.
2. **Level assignment:** record each leaf's depth in T₁.
3. **Recombination:** a stack merge on equal levels turns the level sequence into an alphabetic tree with identical depths, so `Σ w_i · depth_i` is unchanged and is the minimum over all alphabetic trees (Hu & Tucker, 1971).

The finding of the minimum compatible pair uses a single right-to-left scan: for position p, the best partner is the lightest node between p and the next terminal after p (inclusive), which is maintained as a running minimum.

## Complexity Analysis
- **Time complexity:** O(n²) for this implementation (n − 1 combination steps, each an O(n) scan, plus O(n) for levels and recombination). Hu–Tucker can be made O(n log n) with a priority-queue based implementation.
- **Extra space complexity:** O(n) for the node sequence and tree arrays.
