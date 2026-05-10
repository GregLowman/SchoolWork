# Dungeon Crawler — Graph Traversal

A C++ grid-graph dungeon with contamination zones, DFS-based traversability checking, and adjacency list conversion.

## Overview

- Grid cells are typed: `start`, `END`, `open`, `wall`, `radioactive`
- A cell is **contaminated** if any of its 8 neighbours is `radioactive` — contaminated cells are impassable
- **Adjacency list conversion** maps the grid to a graph, connecting each non-wall cell to its valid neighbours
- **DFS traversal** (`isDungeonTraversable`) determines if a path exists from `start` to `END` avoiding walls and contaminated cells

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./run_app <dungeon_file.txt>
./run_tests
```
