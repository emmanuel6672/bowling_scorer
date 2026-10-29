# 🎳 Bowling Score Calculator

## Overview

A ten-pin bowling score calculator developed in C. The project processes bowling rolls and calculates cumulative scores across a complete game, accounting for the scoring rules associated with strikes, spares and open frames.

The project demonstrates practical application of programming fundamentals, data structures and problem-solving in C.

## Features

- **Score Calculation:** Calculates cumulative scores across a ten-frame bowling game.
- **Strike and Spare Handling:** Accounts for bonus points awarded for strikes and spares.
- **Input Processing:** Processes sequences of bowling rolls to determine game scores.
- **Data Structures:** Uses linked lists and queues to organise and process data.
- **Memory Management:** Applies dynamic memory allocation and deallocation in C.
- **Modular Design:** Organises functionality into separate components for maintainability.

## How to Use

### 1. Prerequisites

Before running the program, ensure you have the following installed:

- GCC (C compiler)
- Make (build automation tool)

### 2. Clone the Repository

Clone the repository and navigate into the project directory:

```bash
git clone <your-github-repository-url>
cd bowling-score-calculator
```

Replace the repository URL and directory name with your actual GitHub details.

### 3. Compile the Program

Build both program versions using the included Makefile:

```bash
make
```

This compiles the source files and creates the `task1` and `task2` executables.

### 4. Run the Program

Run either version by passing a bowling game as a command-line argument:

```bash
./task1 "XXXXXXXXXXXX"
```

Or run the second version:

```bash
./task2 "XXXXXXXXXXXX"
```

The example represents a perfect game of twelve consecutive strikes. The program processes the input and displays the corresponding bowling scoreboard.

### 5. Try Different Bowling Games

You can test different scoring scenarios by passing different sequences of rolls:

```bash
./task1 "7-5/xxxxxx71xxx"
```

The input uses standard bowling notation:

| Symbol | Meaning |
|---|---|
| `X` or `x` | Strike |
| `/` | Spare |
| `-` | Zero pins knocked down |
| `1` to `9` | Number of pins knocked down |
| `F` | Foul |

The program supports multiple game inputs in a single command, provided each game is passed as a separate argument.

### 6. Run the Included Test Commands

The Makefile includes commands for running the predefined test input:

```bash
make task1_test_run
make task2_test_run
```

These commands compile the relevant version if needed and execute it using the test cases defined in the Makefile.

### 7. Clean Generated Files

To remove compiled executables and object files, run:

```bash
make clean
```

This allows the project to be rebuilt from its source files.



## Technologies and Skills

- **Language:** C
- **Concepts:** Data structures, algorithms, pointers and dynamic memory management
- **Techniques:** Input parsing, validation and modular programming
- **Tools:** Git and command-line compilation

## Key Learning Outcomes

Through this project, I developed my understanding of:

- Implementing rule-based logic to solve a structured programming problem.
- Using linked lists and queues to manage sequential data.
- Working with pointers and dynamically allocated memory.
- Breaking down a problem into smaller, manageable components.
- Writing and debugging C programs with attention to correctness and edge cases.

## Getting Started

### Prerequisites

A C compiler, such as GCC, and Make if the project uses a Makefile.

### Build and Run

Refer to the project's build configuration and source files for the appropriate compilation and execution commands.

## Future Improvements

Potential extensions include:

- Adding automated tests for strikes, spares and edge cases.
- Improving error handling for invalid roll sequences.
- Expanding the program to support more detailed score summaries.
- Adding a simple user interface for entering rolls and viewing results.

## Purpose

This project showcases my interest in software development, logical problem-solving and building reliable programs. It reflects my experience working with C and my continued development of core technical skills.
