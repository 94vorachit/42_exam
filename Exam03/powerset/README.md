EXERCISE: POWERSET
DESCRIPTION: Find all subsets of a set of integers whose sum equals a target.
KEY CONCEPTS:
* 1. BACKTRACKING: Explore all possible combinations
* 2. SUBSET SUM: Classic subset sum problem
* 3. BINARY DECISION: For each element, include or exclude
* 4. ORDER PRESERVED: Elements must maintain their original order
ALGORITHM:
* 1. For each element, make two decisions: include or exclude
* 2. Keep current sum and current subset
* 3. If sum == target, print subset
* 4. Continue recursively with the remaining elements
