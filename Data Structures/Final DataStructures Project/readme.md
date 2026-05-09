# Dungeon Crawler Item Management — C++

A C++ terminal application simulating item management in a dungeon crawler using three data structures.

## Overview

- **Hash Table** — stores and retrieves dungeon items by name in O(1) average time
- **Priority Queue** — manages item pickup order by priority
- **Graph** — models room connections for dungeon navigation

## Build

```bash
mkdir -p build && cd build
cmake ..
make
```

## Usage

```bash
./crawl ../dungeon1.txt 10
./my_tests
```
