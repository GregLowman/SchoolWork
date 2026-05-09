# Pancake House — Stack and Queue

A C++ simulation of a pancake shop using a queue for customer orders and a stack-based cash register for transaction history.

## Overview

- **ShopQueue** — linked-list queue holding `CustomerOrder` nodes (name, pancake count, type)
- **Register** — fixed-size array stack tracking order prices (up to 20 entries)
- **PancakeHouse** — coordinates both structures: add/cook/cancel orders, refund last sale, close shop, tally profit

Five pancake types map to prices `{1, 2, 5, 3, 7}`. Orders with an invalid type are silently rejected.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./run_app_1
./run_tests_1
```
