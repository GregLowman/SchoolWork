# Stock Data Processor

A C++ program that reads stock price records from CSV files, computes per-company averages, sorts prices in ascending order, and writes the results to an output file.

## Overview

- Reads up to 6 stock records from a `.csv` file (company name + 5 monthly prices)
- Stores data in a statically allocated array of structs
- Computes the average price for each company
- Sorts each company's price array in ascending order using bubble sort
- Outputs sorted data to both stdout and a new CSV file

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./run_app <input_file.csv> <output_file.csv>
./run_tests
```
