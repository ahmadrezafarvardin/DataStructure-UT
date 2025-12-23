# Question 5 – Dynamic Price Counting

## Overview
This problem maintains a **dynamic set of prices** and supports two query types:

1. **Insert a new price** into the set
2. **Count the number of prices less than or equal to a given value**

The goal is to answer all queries **efficiently** for large datasets.

---

## Approach

1. **Coordinate Compression**
   - All price values are collected and mapped to **1-indexed positions** in a sorted unique array
   - This reduces the value range and allows efficient indexing

2. **Fenwick Tree (Binary Indexed Tree)**
   - Supports:
     - Adding a price (`O(log n)`)
     - Counting all prices ≤ a given value (`O(log n)`)
   - Works efficiently with the compressed indices

3. **Query Processing**
   - First, read all queries and build the compression map
   - Then, process queries using the Fenwick Tree

---

## Time Complexity

- Coordinate compression: `O(q log q)` for sorting and deduplication
- Each query (insert or count): `O(log q)`
- Total complexity: `O(q log q)`

---

## Compilation & Execution

```bash
g++ -std=gnu++17 -O2 main.cpp -o q5
./q5
