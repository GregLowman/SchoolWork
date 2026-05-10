# Dynamic Array — Airline Passenger Query

A C++ program that reads passenger records from a text file into a dynamically resizing array of structs, filters by location, airline, and age range, then prints the results sorted by age.

## Overview

- Reads a comma-separated passenger file (name, airline, location, age)
- Stores matching records in a dynamically allocated array starting at size 10
- Doubles the array capacity whenever it fills — tracking the number of doublings
- Filters passengers by location, airline, and age range from command-line arguments
- Sorts results in descending age order (alphabetical name as tiebreaker)

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./run_app <passengers.txt> <location> <airline> <min_age> <max_age>
./run_tests
```
