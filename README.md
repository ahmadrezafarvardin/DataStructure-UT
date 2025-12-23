# Data Structures and Algorithms – Coding Assignments (CA)

This repository contains the **Coding Assignments (CA)** for the **Data Structures and Algorithms (DSA)** course at **University of Tehran**.  
The assignments are divided into **CA1** and **CA2**, each with modular C++ implementations and organized folder structures.

---

## Folder Structure

```

.
├── CA1/                 # Assignment 1
│   ├── ca1.pdf          # Problem statements (Persian)
│   ├── CA-MultiFile/    # Source and header files for modular implementation
│   ├── README.md        # README for CA1
├── CA2/                 # Assignment 2
│   ├── CA2.pdf          # Problem statements (Persian)
│   ├── q1/ ... q5/      # Individual question folders
│   ├── README.md        # README for CA2
└── README.md            # Top-level README

````

---

## CA1 – Music Player Simulation

- **Overview:** Implements a modular music player using object-oriented design.
- **Key Data Structures:** Circular Doubly Linked List, Class-based state management.
- **Algorithms/Patterns:** State pattern for playback control, playlist management, file I/O.
- **How to Run:**
  - Using Makefile (recommended):
    ```bash
    cd CA1/CA-MultiFile
    make
    ./main
    ```
  - Using g++ directly:
    ```bash
    g++ -std=gnu++17 -O2 main.cpp CircularDoubleLinkedList.cpp MusicPlayer.cpp PlaybackState.cpp Playlist.cpp Song.cpp -o ca1
    ./ca1
    ```

---

## CA2 – Graph and Query Problems

- **Overview:** Implements 5 questions covering various graph algorithms, dynamic queries, and data structures.
- **Problem statements:** Detailed in **`CA2.pdf`** (Persian).
- **Folder Structure:** Each question has its own folder (`q1` to `q5`) with code and README.
- **Key Data Structures and Algorithms:**

| Question | Data Structures | Algorithms / Techniques |
|----------|----------------|------------------------|
| **Q1**  | DSU, Multiset  | Maximum Spanning Tree (Kruskal), LCA with binary lifting, bottleneck path queries |
| **Q2**  | Graph adjacency list | Dijkstra’s algorithm, limited fuel path, single refueling optimization |
| **Q3**  | Graph adjacency list | Modified Dijkstra with traffic light delays |
| **Q4**  | Graph adjacency list, extended state | Dijkstra with fuel station visit tracking, traffic light delays |
| **Q5**  | Fenwick Tree, Coordinate Compression | Efficient dynamic insertions and range counting |

- **Compilation & Execution:** Each question can be compiled individually:
  ```bash
  cd CA2/q1   # Replace q1 with q2, q3, etc.
  g++ -std=gnu++17 -O2 main.cpp -o q1
  ./q1
````

---

## Notes

* Repository is structured for **clarity and modularity**.
* Only **essential code files** are tracked; auxiliary files, archives, and outputs are excluded.
* All implementations are optimized for **time and space efficiency**.
* This repository is submission-ready for **DSA course at University of Tehran**.

---
