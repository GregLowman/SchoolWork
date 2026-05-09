# Bomb Lab — Reverse Engineering

Defusing a binary bomb by analyzing x86-64 assembly with GDB and `objdump`.

## Overview

The bomb executable runs through six phases; each phase requires the correct input string. Wrong input detonates the bomb. The solution was determined entirely through disassembly and debugger inspection — no source code was provided for the phases.

## Contents

```
bomb502/
  bomb           — the binary executable
  bomb.c         — main routine (provided)
  solution.txt   — defuse strings for all six phases
  BombCodeDissassembly.txt  — annotated full disassembly
  BombSections.txt          — phase-by-phase breakdown
  BombSymbolTable.txt       — symbol table dump
  BombsMappings.txt         — key address mappings
  DisassemblyFull.txt       — raw objdump -d output
  RoDataInspect.txt         — read-only data segment inspection
```

> Note: the `identikey` file was removed from this repo as it contained a personal login credential.

## Tools Used

- `gdb` — step through instructions, inspect registers and memory
- `objdump -d` — disassemble all phases
- `strings` — extract readable strings from the binary
