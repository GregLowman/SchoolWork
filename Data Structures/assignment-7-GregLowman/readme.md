# Movie Collection — Binary Search Tree II

Extended BST implementation adding node deletion, left rotation, and lowest common ancestor.

## Overview

Builds on the BST movie collection with three new operations:
- **Delete** (`removeMovie`) — handles all cases: leaf, one child, two children (in-order successor swap)
- **Left rotation** (`rotateLeftCollection`) — rotates a named node left, updating parent links
- **Lowest common ancestor** (`closestParent`) — finds the deepest node that is an ancestor of both input movies

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./run_app <movies.csv>
./run_tests
```
