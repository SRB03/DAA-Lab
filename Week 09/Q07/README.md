# Q07 - Minimise array deviation using odd-doubling and even-halving moves

## Question Title
**[Minimise Deviation in Array (Two-Way Greedy with Max-Heap)]** Given an array of positive integers, you can perform two operations: multiply any odd element by 2, or divide any even element by 2. The deviation is (max(A) − min(A)). Minimise the deviation after any number of operations. By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

## How the Code Works
The array is read (random mode: n elements in [1,1000]). Every odd element is doubled first, so all elements are in their "highest" reachable form. They are pushed into a max-heap while the global minimum is tracked. The program then repeatedly pops the maximum, records `max − min`, and halves the maximum if it is even (updating the minimum and pushing the result back); it stops when the maximum is odd. A brute-force candidate-window search validates the answer for n ≤ 200.

## Maths / Logic Behind This
Write each element as `x = o · 2^k` with o odd. The only values it can ever take are `o·2^j` for `0 ≤ j ≤ max(k, 1)`: an even number can only go down to o (and then up to 2o again), and an odd number can only become 2o. So the **highest** value an element can reach is `o·2^max(k,1)`, which is what we get by doubling odd numbers once.

Start with every element at its highest value (deviation = max − min). The maximum must fall to reduce the deviation; the only way to lower it is to halve the current maximum element, which may lower the minimum but never raises the maximum. If the maximum is odd it cannot be reduced and no further improvement is possible, because the maximum element is stuck at that value. Each element can be halved at most log₂(max A) times, so the process terminates, and recording the best `max − min` along the path gives the optimum. The brute-force validator checks every candidate minimum value and the smallest feasible value ≥ it for each element.

## Complexity Analysis
- **Time complexity:** O(n log n · log M) where M = max(A): each of the at most n·log M halving steps costs one heap pop and push, O(log n).
- **Extra space complexity:** O(n) for the heap.
