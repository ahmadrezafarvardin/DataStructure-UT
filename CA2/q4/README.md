# Question 4 – Shortest Path Visiting Fuel Station

## Overview
This problem models a weighted undirected graph with:
- Traffic lights at each node (green/red cycles)
- Designated fuel stations

The task is to compute the **minimum travel time from node 1 to node n**, such that the path **visits at least one fuel station**.

---

## Approach

1. **Graph Representation**
   - Edges have travel times
   - Nodes may be fuel stations
   - Nodes have traffic lights affecting waiting time

2. **Modified Dijkstra’s Algorithm**
   - State includes:
     - Current node
     - Current time
     - Whether a fuel station has been visited
   - Edge relaxation considers:
     - Travel time along edge
     - Waiting time at next node (traffic light)
     - Updating the fuel station visit state

3. **Priority Queue**
   - Maintains states ordered by **earliest arrival time**
   - Ensures that optimal paths are processed first

4. **Result**
   - Minimum time to reach destination **with fuel station visited**
   - Output `-1` if no such path exists

---

## Time Complexity

- Dijkstra with 2 states per node: `O(2 * (n + m) log n)`
- Efficient for moderate graph sizes

---

## Compilation & Execution

```bash
g++ -std=gnu++17 -O2 main.cpp -o q4
./q4
