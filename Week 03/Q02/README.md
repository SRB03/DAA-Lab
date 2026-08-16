## Defective Coin Finder 

### How the Code Works

The program works by simulating a balance scale to find a single lighter coin among a set of standard-weight coins. It employs a recursive divide-and-conquer strategy:

1. **Initialization:** The user provides the total number of coins and chooses whether to input their weights manually or have the program generate them randomly.
2. **Divide:** The `searchDefective` function splits the current set of coins into two equal halves. If the total number of coins in the current subset is odd, one coin is left out.
3. **Conquer (Weighing):** The `weigh` function calculates the total weight of both halves.
    - If the left half is lighter, the defective coin must be in the left half.
    - If the right half is lighter, the defective coin must be in the right half.
    - If both halves weigh the same, the defective coin is the one that was left out (if the subset size was odd).
4. **Base Case:** When the search space is reduced to a single coin, it is weighed against a `known_good` coin (identified in previous balanced steps) to confirm if it is genuinely defective.
5. **Output:** The program prints the index (0-based) and the weight of the defective coin, or reports if no defective coin exists.

### Maths behind this

The core mathematical principle here is the reduction of the search space by half at each iteration, akin to a binary search. 

Let $N$ be the number of coins.
At any step, we divide $N$ into two groups of size $k = \lfloor N / 2 \rfloor$. 
- If $N$ is even, $2k = N$. We compare the two groups.
- If $N$ is odd, $2k = N - 1$. We compare the two groups. If they balance, the $(N)^{th}$ coin is the defective one.

Because the problem guarantees at most one lighter coin, a single comparison between two equal-sized halves definitively tells us which subset contains the defective coin, discarding the other half.

### Complexity overview

* **Time Complexity: $O(N)$**
  Although the algorithm divides the search space in half at each step (which usually implies $O(\log N)$), the `weigh` function iterates through the subarrays to calculate the sum of the weights. 
  The recurrence relation is: 
  $$T(N) = T(N/2) + O(N)$$
  According to the Master Theorem, solving $N + N/2 + N/4 + ... + 1$ yields a geometric series that converges to $O(N)$. 
  *(Note: If the `weigh` operation could be performed in constant $O(1)$ time—such as using a physical balance scale or prefix sum arrays—the time complexity would be $O(\log N)$).*

* **Space Complexity: $O(\log N)$**
  The space complexity is determined by the maximum depth of the recursive call stack. Since the array is halved in each recursive call, the maximum depth of the stack is $\approx \log_2(N)$. The heap memory allocated for the coins array is $O(N)$.

### Observation and output (plots if any)

*(Note: This program runs in the terminal and does not generate graphical plots. Below is an observation of the console output.)*

When running the program with random generation, you will observe standard coins defaulting to a weight of `10`, with one randomly selected coin assigned a weight of `9`. 

**Example Output:**
```text
Enter the number of coins: 5

How would you like to populate the array?
1. Generate random array
2. Enter weights manually
Enter choice (1 or 2): 1

Generated array: 10 10 9 10 10 
Defective coin found at index 2 (Weight: 9)
```
If you manually enter coins with identical weights, the output will correctly state: `No defective coin found.`

#### How to Run

You can compile the C code and run the execution command:

```bash
gcc q2.c && ./a.out 
```


2. Follow the on-screen prompts to input the number of coins and select your preferred method of array population.