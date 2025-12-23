# Question 2 – Shortest Path with Limited Fuel

## Overview
This problem considers a weighted undirected graph where a vehicle must travel from node `1` to node `n` with fuel constraints.

The vehicle:
- Starts with a limited amount of fuel
- Has a maximum fuel capacity
- May refuel **at most once** at designated fuel stations

The goal is to find the **minimum total distance** to reach the destination, or report failure if it is not possible.

---

## Approach

1. **Graph Modeling**
   - The road network is represented as a weighted undirected graph.

2. **Dijkstra’s Algorithm**
   - Run once from the start node (`1`) to compute shortest distances to all nodes.
   - Run once from the destination node (`n`) to compute distances back to all nodes.

3. **Case Analysis**
   - **No refueling:**
     Check if the destination can be reached directly with the initial fuel.
   - **One refueling stop:**
     For each fuel station:
     - Ensure it is reachable from the start with initial fuel.
     - Ensure the destination is reachable from the station within tank capacity.

4. **Answer Selection**
   - The minimum valid total distance is chosen.
   - If no valid route exists, output `"nemisarfed"`.

---

## Time Complexity

- Dijkstra runs: `O(m log n)`
- Station checks: `O(k)`
- Overall: `O(m log n)`

---

## Compilation & Execution

```bash
g++ -std=gnu++17 -O2 main.cpp -o q2
./q2
