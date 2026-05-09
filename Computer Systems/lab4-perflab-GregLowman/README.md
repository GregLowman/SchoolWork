# Performance Lab — Image Filter Optimization

Optimizing a C++ image convolution pipeline through loop restructuring, cache-friendly access patterns, and SIMD-style techniques.

## Overview

The application reads a `.bmp` image and a `.filter` file, applies a convolution filter, and writes the result. The optimization target is the inner convolution loop across five nested `for` loops (colors, rows, columns, filter rows, filter columns).

Included filters: `avg`, `edge`, `emboss`, `gauss`, `sharpen`, and more.

## Build and Test

```bash
make
make test        # run all filters and compare output images
./Judge          # score performance against the reference implementation
```

## Images

- `blocks-small.bmp` — primary benchmark image
- `boats.bmp` — secondary test image
- `tests/` — filtered output images
