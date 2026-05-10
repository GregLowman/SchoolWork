# Attack Lab — Code Injection and Return-Oriented Programming

Exploiting buffer overflow vulnerabilities in x86-64 binaries using code injection and return-oriented programming (ROP) techniques.

## Overview

Two target programs (`ctarget` and `rtarget`) contain intentional buffer overflow vulnerabilities. The goal is to craft input strings that redirect execution to target functions or execute arbitrary code.

- **Code injection** — inject shellcode via the stack overflow in `ctarget`
- **ROP** — chain existing gadgets in `rtarget` to bypass stack randomization and non-executable stack protections

## Tools Used

- `gdb` — step through execution and inspect stack state
- `objdump -d` — find gadget addresses
- `hex2raw` — convert hex strings to raw byte input
