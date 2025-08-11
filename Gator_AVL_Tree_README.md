
# Gator AVL Tree

## Overview
The **Gator AVL Tree** is a C++ implementation of a self-balancing binary search tree (AVL tree) designed to maintain **O(log n)** performance for insertion, deletion, and search operations.  
It includes rotation logic to preserve tree balance, recursive traversal methods, and optimized search for name-based queries.  
The project also applies memory management best practices for handling large datasets efficiently.

---

## Features
- **Self-Balancing Tree:** Automatic height balancing after insertions and deletions using AVL rotations.
- **Efficient Operations:** O(log n) complexity for insert, delete, and search.
- **Recursive Traversals:** Pre-order, in-order, and post-order implementations.
- **Optimized Name Lookup:** Enhanced search using pre-order traversal for name-based queries.
- **Memory Management:** Reduced memory footprint and improved efficiency for large datasets.

---

## Concepts Demonstrated
- Data structures (AVL tree)
- Tree balancing via rotations (LL, RR, LR, RL)
- Recursive algorithms
- Search optimization
- Memory management in C++

---

## AVL Rotations
AVL trees use four types of rotations to maintain balance:

**Right Rotation (LL Case):**
![Right Rotation Diagram](examples/right_rotation.png)

**Left Rotation (RR Case):**
![Left Rotation Diagram](examples/left_rotation.png)

**Left-Right Rotation (LR Case):**
![Left-Right Rotation Diagram](examples/left_right_rotation.png)

**Right-Left Rotation (RL Case):**
![Right-Left Rotation Diagram](examples/right_left_rotation.png)

These diagrams illustrate how the tree restructures itself after insertions or deletions that cause imbalance.

---

## Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/gator-avl-tree.git
cd gator-avl-tree

# Compile
g++ -o gator_avl main.cpp avl_tree.cpp

# Run
./gator_avl
```

---

## Usage
The program accepts commands for:
- **Insert**: Add a node to the tree.
- **Delete**: Remove a node from the tree.
- **Search**: Find nodes by key or name.
- **Traverse**: Display nodes in pre-order, in-order, or post-order.

Example:
```plaintext
INSERT John
INSERT Alice
DELETE John
SEARCH Alice
TRAVERSE PREORDER
```

---

## Example Output
```plaintext
Tree before deletion:
Alice John Mark
Deleting John...
Tree after deletion:
Alice Mark
Search for Alice: Found
```

---

## Performance
The AVL tree guarantees:
- O(log n) search time even with frequent insertions and deletions.
- Height difference between subtrees never exceeds 1.

---

## Skills Demonstrated
- C++ data structures
- Algorithm optimization
- Memory management
- Recursive programming
- Self-balancing trees

---

## License
This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
