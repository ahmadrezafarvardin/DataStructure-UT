# CA1 – Data Structures and Music Player Implementation

## Overview
This folder contains the implementations for CA1 assignments.  
Detailed problem statements are available in **`ca1.pdf`** (in Persian).

The main part of the assignment is in the **`CA-MultiFile`** folder, which contains modular C++ source and header files for a music player simulation.

---

## Folder Structure

```

CA-MultiFile/
├── main.cpp             # Entry point
├── Makefile             # Build system
├── CircularDoubleLinkedList.* # Data structure implementation
├── MusicPlayer.*        # Music player logic
├── PlaybackState.*      # State handling
├── Playlist.*           # Playlist management
├── Song.*               # Song representation

````

- **`main.cpp`** uses the above classes to demonstrate functionality.
- Other files in `CA1` (like `mp.cpp`, `music_player`, or archives) are **not tracked** in the repository.

---

## Data Structures and Techniques Used

- **Circular Doubly Linked List**: Playlist management and song queue
- **Object-Oriented Design**: Classes for `MusicPlayer`, `PlaybackState`, `Playlist`, and `Song`
- **State Pattern**: Playback state handling (`Play`, `Pause`, etc.)
- **File I/O**: Optional music data loading and saving

---

## Compilation and Running

### Using Makefile (recommended)
```bash
cd CA-MultiFile
make
./main
````

### Using g++ directly

```bash
cd CA-MultiFile
g++ -std=gnu++17 -O2 main.cpp CircularDoubleLinkedList.cpp MusicPlayer.cpp PlaybackState.cpp Playlist.cpp Song.cpp -o ca1
./ca1
```

* Output will demonstrate playlist management, song playback, and state transitions.
