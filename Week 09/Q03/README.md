# Q03 - Minimum number of refuelling stops to reach the target

## Question Title
**[Minimum Initial Fuel (Reverse Greedy)]** A vehicle needs to reach the target D starting with fuel F. Along the way are stations (d_i, f_i) (distance from origin and refuel amount). What is the minimum number of refuelling stops required to reach the target? By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## How the Code Works
The target D, initial fuel F and the stations (two fields per station) are read manually or generated randomly (D∈[20,500], 1≤F≤D/4, station distance∈[1,D−1], refuel amount∈[1,60]); stations are sorted by distance. `min_refuel_stops()` drives as far as possible, pushing every passed station into a max-heap keyed by fuel, and when the vehicle cannot go further it "retroactively" refuels at the best passed station. A separate O(n²) dynamic programme re-solves the instance to validate the answer.

## Maths / Logic Behind This
Let `reach` be the farthest distance achievable with the stops used so far (initially F). Every station with `d_i ≤ reach` is a candidate. We never need to decide in advance where to stop: we postpone the decision until the car would run out of fuel and only then take the already-passed station with the **largest** refuel amount.

**Why it is optimal (exchange argument).** After k stops the set of reachable distances is maximised by taking the k largest fuel amounts among stations that were passed in time. Any optimal solution that refuels at a smaller amount at some point can swap it for the larger one without reducing `reach`, so the greedy `reach` after k stops is the maximum possible. If the heap is empty while `reach < D`, no sequence of stops can ever reach D, and the answer is −1.

**Validation.** `dp[j]` = farthest distance reachable using j stops; for each station in order, `dp[j] = max(dp[j], dp[j−1] + f_i)` if `dp[j−1] ≥ d_i`. The smallest j with `dp[j] ≥ D` must equal the greedy answer.

## Complexity Analysis
- **Time complexity:** O(n log n) (sorting plus at most n heap pushes and pops).
- **Extra space complexity:** O(n) for the heap.
