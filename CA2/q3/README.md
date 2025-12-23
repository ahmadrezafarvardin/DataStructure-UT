# Question 3 – Shortest Path with Traffic Lights

## Overview
This problem models a weighted undirected graph where each node has a traffic light with a green/red cycle.
The goal is to compute the **earliest arrival time** from node `1` to node `n`, accounting for **wait times at red lights**.

---

## Approach

1. **Graph Representation**
   - Each edge has a travel time (`weight`).
   - Each node has a traffic light with:
     - `greenDuration`
     - `redDuration`
   - Wait time at a node is computed based on the current arrival time and traffic light cycle.

2. **Modified Dijkstra’s Algorithm**
   - Standard Dijkstra with a **departure time adjustment** at each node:
     - At source node: depart immediately
     - At other nodes: add waiting time if the light is red

3. **Edge Relaxation**
   - For each neighbor:
     - Compute `departureTime = currentTime + waitTime`
     - Compute `arrivalTime = departureTime + edgeWeight`
     - Update distance if `arrivalTime` is smaller

---

## Time Complexity

- Dijkstra’s algorithm: `O((n + m) log n)`
- Efficient enough for typical graph sizes

---

## Compilation & Execution

```bash
g++ -std=gnu++17 -O2 main.cpp -o q3
./q3
