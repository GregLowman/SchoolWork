# Data Lab — Bit Manipulation in C

Implementing integer and floating-point operations using only bitwise operators — no conditionals, no loops, limited operator count per function.

## Overview

All work is in `bits.c`. Each puzzle implements a standard operation (e.g., `bitOr`, `isNonNegative`, `floatScale2`) using only:

```
! ~ & ^ | + << >>
```

Constants are restricted to 8-bit values; larger constants must be constructed.

## Build and Test

```bash
make
./btest          # correctness tests
./dlc bits.c     # operator count checker
```
