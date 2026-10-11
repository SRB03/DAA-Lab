# Q05 - Minimum candies for children with rating constraints

## Question Title
**[Candy Distribution Problem (Bi-directional Slope Greedy)]** n children stand in a line, each assigned a rating. Each child must get at least one candy. Children with a higher rating than their immediate neighbours must get more candies than their neighbours. Find the minimum total number of candies needed. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## How the Code Works
Ratings are read into an integer array (random mode: ratings in [0,10]). `candies_slope()` makes one left-to-right pass and tracks the length of the current rising run (`up`), the current falling run (`down`) and the rising length of the last peak (`peak`); each step adds the next term of an arithmetic series. A classic two-pass algorithm (left→right, then right→left) is run as a reference and also builds the explicit distribution, which is checked against every neighbour rule.

## Maths / Logic Behind This
The ratings form alternating slopes. On a strictly rising run of length u the candies must be at least 1, 2, …, u+1, and on a falling run of length d at least d+1, …, 2, 1 (read left to right). The two sides of a peak share the peak child, who needs `max(u, d) + 1` candies.

- Rising step: `up++`, `peak = up`, `down = 0`, add `1 + up`.
- Equal ratings: reset all counters, add 1.
- Falling step: `up = 0`, `down++`, add `1 + down`; if `peak ≥ down` the peak already holds enough candies, so subtract 1 to avoid double counting.

**Why minimal.** Every child gets the smallest value forced by the longest strictly monotone chain ending at, or starting from, that child, and these lower bounds are all that the constraints require; the slope sums reach those bounds exactly. The two-pass method gives the same pointwise values `max(left[i], right[i])`.

## Complexity Analysis
- **Time complexity:** O(n) (one pass over the ratings).
- **Extra space complexity:** O(1) for the slope method (the two-pass validation uses O(n) extra space, but it is not part of the algorithm).
