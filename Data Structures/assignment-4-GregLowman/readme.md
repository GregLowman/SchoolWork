# Music Playlist — Linked Lists II

Extended linked list implementation adding Floyd's cycle detection, range deletion, and two-playlist merging.

## Overview

Builds on a singly linked list playlist with three new operations:
- **Loop detection** (`findLoopInPlaylist`) — Floyd's slow/fast pointer algorithm; returns loop length or -1
- **Range removal** (`removeSongs`) — deletes nodes from index `start` to `end` (1-based)
- **Merge** (`mergeTwoPlaylists`) — interweaves two playlists by alternating nodes in-place without allocating new nodes

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
