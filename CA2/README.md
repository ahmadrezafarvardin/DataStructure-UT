# CA2 – Data Structures and Algorithms

## Overview
This folder contains the implementations of the CA2 assignments.
Detailed problem statements can be found in **`CA2.pdf`** (in Persian).

Each question is placed in its own folder (`q1` to `q5`) with a separate `README.md` and `main.cpp` for clarity and modularity.

---

## Data Structures and Algorithms Used

| Question | Key Data Structures | Key Algorithms / Techniques |
|----------|------------------|----------------------------|
| **Q1** | Disjoint Set Union (DSU), Multiset | Maximum Spanning Tree (Kruskal), Lowest Common Ancestor (LCA) with binary lifting, bottleneck path queries |
| **Q2** | Graph adjacency list | Dijkstra’s algorithm with limited fuel, single refueling stop optimization |
| **Q3** | Graph adjacency list | Modified Dijkstra’s algorithm with traffic light wait times |
| **Q4** | Graph adjacency list, state tracking | Dijkstra with extended state (fuel station visited), traffic light delays |
| **Q5** | Fenwick Tree (Binary Indexed Tree), Coordinate Compression | Efficient dynamic insertions and range counting |

---

## Usage

Each question can be compiled and executed individually. Example:

```bash
cd q1
g++ -std=gnu++17 -O2 main.cpp -o q1
./q1
