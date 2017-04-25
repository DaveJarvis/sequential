# Overview

Searches for a sequential representation of a number in terms of increasing
orders of 1 to 9.

https://arxiv.org/pdf/1302.1479.pdf

# Build

Build the `main` program as follows:

1. Ensure development tools are installed (`gcc`).
1. Change into the `sequential` directory.
1. Type: `make`

# Run

Run the program as follows:

    ./main

The program will not terminate until it finds a valid expression.

Press `Control+C` to end the program at any time.

## Goal

The default target number is 10958, which can be changed on the command line:

    ./main 10001

## Digit Set

The default sequential set of digits is {123456789}, which can be changed on
the command line:

    ./main 10001 12345678

At least two digits must be supplied.

# Output

When an expression is found that evaluates to the goal, that expression is
written to the console (standard output).

