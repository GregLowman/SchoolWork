# LinkedIn Network — Graph and BFS

A C++ undirected graph modelling a professional network, with breadth-first traversal and k-th order connection suggestions.

## Overview

- Nodes are `Professional` structs (name, visited flag, connection order)
- Edges are bidirectional adjacency lists
- **BFS traversal** from a source node, printing each reachable professional with their degree of separation
- **k-th order suggestions** — returns all professionals reachable within k connections from a given source

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./run_app
./run_tests
```
