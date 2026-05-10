#!/bin/bash
for i in $(seq -w 1 16); do
    echo "=== TEST $i ==="
    make test$i
    echo "=== RTEST $i ==="
    make rtest$i
    echo ""
done