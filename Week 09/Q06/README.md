# Q06 - Rearrange a string so equal characters are at least K apart

## Question Title
**[Reorganise String with K-Distance Apart]** Given a string S and an integer K, rearrange S such that the same characters are at least distance K apart. If impossible, return an empty string. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## How the Code Works
The string is read (random mode: length 4–16, 2–5 distinct letters, 1≤K≤4) and the character frequencies go into a 256-entry table and then into a max-heap ordered by (count, character). For every output position the most frequent available character is placed, its count is decremented and it is parked in a FIFO cool-down queue; once K characters are parked, the oldest returns to the heap if it still has copies left. If the heap is empty before the string is complete, an empty string is returned. The result is validated, and for |S| ≤ 9 an exhaustive search confirms feasibility.

## Maths / Logic Behind This
Two equal characters must occupy positions differing by at least K, so any window of K consecutive positions contains K *distinct* characters. The character with the highest remaining count is the most constrained, so it is placed as early as the rule allows; placing a less frequent character first can only leave the frequent ones with fewer legal positions (exchange argument). The cool-down queue enforces the distance: a character placed at position i cannot return before position i + K.

Feasibility is detected exactly: the greedy gets stuck (empty heap while characters remain) only when every remaining character is within its cool-down window, which means no valid arrangement exists. A necessary condition is `(max_count − 1) · K + (number of characters with max_count) ≤ |S|`.

## Complexity Analysis
- **Time complexity:** O(n log σ), where σ ≤ 256 is the number of distinct characters (so O(n) for a fixed alphabet); each position needs one heap pop and at most one push.
- **Extra space complexity:** O(σ + K) for the heap, counts and cool-down queue (the implementation allocates the queue with n entries for simplicity, so O(n) in practice).
