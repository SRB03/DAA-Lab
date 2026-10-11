# Q01 - Fractional knapsack where item value density decays with time

## Question Title
**[Fractional Knapsack with Deterioration Rate]** You have n items with base values v_i, weights w_i, and decay rates λ_i > 0. If an item is consumed at time t, its effective value density decays to (v_i/w_i) − λ_i·t. Knapsack capacity is W. Determine the optimal scheduling order and fractional choices to maximise total value. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## How the Code Works
Items are stored as records (v, w, λ, density, amount taken). The menu reads either manual data or random data (v∈[10,200], w∈[1,20], λ∈[0.01,1], 0<W≤Σw). `solve_knapsack()` repeatedly finds the leading item(s) by marginal gain, gives mass to the one with the smallest λ among the leaders, and advances to the next event (item full, a new item ties, capacity used, or gain reaches 0). `print_schedule()` then orders the chosen items by decreasing λ and prints start times, amounts and values; `validate_solution()` tries 4000 random feasible perturbations and checks none improves the value.

## Maths / Logic Behind This
**Model used.** Consumption runs at 1 unit of weight per unit of time, so mass consumed after `s` units of earlier consumption is consumed at time `t = s`. A unit of item i consumed at time t earns `d_i − λ_i t`, where `d_i = v_i / w_i`.

**Order.** Take two units of mass from items i, j and swap their time slots t < t'. Putting i in the earlier slot gains `(λ_i − λ_j)(t' − t)` compared with putting j there, so the item with the larger decay rate must be consumed earlier. Hence the optimal order is **decreasing λ**, and plain "pick the best current density" is *not* optimal (e.g. d=(10, 9), λ=(0, 5), w=(1, 1), W=2 gives 11.6 for best-density-first but 16.5 for decay-first).

**Amounts.** With the order fixed, a block of x_i units that starts at time s_i earns `d_i x_i − λ_i (s_i x_i + x_i²/2)`. Summing gives the concave function

F(x) = Σ d_i x_i − ½ Σ_i Σ_j min(λ_i, λ_j) x_i x_j, with 0 ≤ x_i ≤ w_i and Σ x_i ≤ W.

The gradient is `g_i = d_i − Σ_j min(λ_i, λ_j) x_j`. At an optimum all items with 0 < x_i < w_i share the same gain μ ≥ 0 (KKT). Lowering μ continuously shows that, among the tied leaders, only the one with the **smallest λ** receives mass (the inverse of the matrix min(λ_i, λ_j) is tridiagonal), while the others stay frozen and tied. Once an item enters the leader set it stays there until it becomes full, so there are at most 2n events. Because F is concave, KKT is sufficient, so the result is globally optimal. The result was also cross-checked against an independent numerical optimiser on random instances.

## Complexity Analysis
- **Time complexity:** O(n²). There are at most 2n + 1 events, each costing O(n) to find the next event and update the gradients. Sorting the chosen items for the final schedule adds O(n log n). (The optional validation is extra: O(n log n) per perturbation.)
- **Extra space complexity:** O(n) (the sorted copy of the schedule; the flags and gradients live inside the item records).
