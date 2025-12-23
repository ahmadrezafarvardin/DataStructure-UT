# Question 1 – Freight Routing with Constraints

## Overview
This problem models a freight routing system on a weighted graph.
Cities are connected by roads with height limits, and trucks of different heights are dynamically added or removed.

For each route query, the goal is to determine **the tallest available truck** that can travel between two cities without exceeding any road height limit along the path.

---

## Approach

1. **Maximum Spanning Tree (MST)**
   - Built using **Kruskal’s algorithm**
   - Guarantees the maximum possible minimum edge (bottleneck) between any two nodes

2. **Lowest Common Ancestor (LCA) with Binary Lifting**
   - Preprocessed on the MST
   - Used to compute the **minimum edge weight (bottleneck)** on the path between two nodes in `O(log n)`

3. **Disjoint Set Union (DSU)**
   - Ensures connectivity checks between cities

4. **Truck Management**
   - Uses a `multiset` to support:
     - Adding trucks
     - Removing trucks
     - Finding the tallest truck that fits a height constraint

---

## Query Types

- **Type 1:** Add a truck with given height
- **Type 2:** Remove a truck with given height
- **Type 3:** Given two cities, output the tallest truck that can travel between them
  - Outputs `-1` if no valid route or truck exists

---

## Time Complexity

- MST construction: `O(m log m)`
- LCA preprocessing: `O(n log n)`
- Each query: `O(log n)`

---

## Compilation & Execution

```bash
g++ -std=gnu++17 -O2 main.cpp -o q1
./q1
