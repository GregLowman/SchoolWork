# Shell Lab — Unix Shell with Job Control

A Unix shell implementation (`tsh`) supporting foreground and background processes, signal handling, and job control built-ins.

## Overview

`tsh.cc` implements:
- Command parsing and `execve`-based process execution
- `fg` / `bg` built-ins to move jobs between foreground and background
- Signal handlers for `SIGCHLD`, `SIGINT`, and `SIGTSTP`
- Job table tracking all active processes

## Build and Test

```bash
make
./runtests.sh    # run all trace-based test cases
```

Test traces in `trace*.txt` drive the shell through progressively more complex job control scenarios. Reference output is in `tshref.out`.
