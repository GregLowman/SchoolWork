# Malloc Lab — Dynamic Memory Allocator

A custom `malloc`, `free`, and `realloc` implementation in C, balancing correctness, throughput, and memory utilization.

## Overview

`mm.c` contains the allocator. The design uses an explicit free list with boundary tags for coalescing adjacent free blocks.

## Build and Test

```bash
make
./mdriver -v     # run all allocation traces and report utilization + throughput
```

Traces in `traces/` exercise a range of allocation patterns (e.g., binary trees, realloc-heavy workloads).
