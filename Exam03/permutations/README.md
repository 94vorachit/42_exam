EXERCISE: PERMUTATIONS

DESCRIPTION:
Generate all permutations of a given string in alphabetical order.

KEY CONCEPTS:
1. BACKTRACKING: Exhaustive search algorithm
2. SORTING: Ensure alphabetical order
3. RECURSION: Generate permutations level by level
4. STATE: Track which characters have already been used

ALGORITHM:
1. Sort the original string alphabetically
2. For each position, try every unused character
3. Mark the character as used and recurse
4. Unmark the character when returning (backtrack)
5. Print when a permutation is complete