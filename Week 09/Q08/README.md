# Q08 - Minimum number of meeting rooms for a set of intervals

## Question Title
**[Minimum Number of Meeting Rooms]** Given an array of meeting time intervals consisting of start and end times [[s₁, e₁], [s₂, e₂], …], find the minimum number of conference rooms required. By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

## How the Code Works
Meetings are stored as two parallel arrays `s[]` and `e[]` (random mode: start in [0,100], duration in [1,40], so always start < end). Intervals are treated as half-open `[s, e)`, so a meeting that starts exactly when another ends can reuse its room. The start times and end times are copied and sorted independently; a two-pointer sweep opens a new room when the next start is before the earliest unfinished end, and otherwise reuses a room. A brute-force maximum-overlap count validates the result.

## Maths / Logic Behind This
The minimum number of rooms equals the **maximum number of meetings that overlap at any single time** (interval graphs are perfect: the chromatic number equals the clique number). Lower bound: at the busiest moment every overlapping meeting needs its own room. Upper bound: process meetings by start time; when a meeting begins and every opened room is still busy, a new room is unavoidable, otherwise it can take a freed room.

Sorting starts and ends separately works because only the *counts* matter: the number of meetings running at time t is `#starts ≤ t − #ends ≤ t`, and the pointer `j` counts how many meetings have already ended before the current start, so `rooms = i + 1 − j` at its maximum.

## Complexity Analysis
- **Time complexity:** O(n log n) (two sorts, then an O(n) sweep).
- **Extra space complexity:** O(n) for the two sorted copies.
