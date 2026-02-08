# Course Planner (BST vs AVL) — Modular C++ Advising Tool

A modular C++ command-line application that loads course data from a CSV file, prints a sorted schedule, and looks up individual courses.  
This enhanced version includes **two interchangeable tree implementations** - a standard **BST** and a self-balancing **AVL**, and a **benchmark mode** that compares search performance between them.

## Features
- Load course records from a comma-delimited CSV file
- Print an ordered schedule (in-order traversal)
- Print details for a single course (title + prerequisites)
- Benchmark **BST vs AVL** repeated-search timing
- Modular structure designed for **testability** and clear separation of concerns

## Project Structure
```
Course_Plan_CLI_Enhanced/
  include/
    avl.h
    bst.h
    benchmark.h
    course.h
    csv_loader.h
    tree_iface.h
    utils.h
  src/
    avl.cpp
    bst.cpp
    benchmark.cpp
    csv_loader.cpp
    utils.cpp
    main.cpp
  tests/
    smoke_test.cpp
    test_trees.cpp
```

## Build
From the `Course_Plan_CLI_Enhanced` directory:

```bash
g++ -std=c++17 -O2 -Iinclude src/*.cpp -o course_planner
```

## Run
Use the default CSV name in the working directory:

```bash
./course_planner
```

Or provide a CSV path:

```bash
./course_planner "CS 300 ABCU_Advising_Program_Input.csv"
```

## Benchmarking (BST vs AVL)
Menu option `4` runs the same repeated-search workload against both trees and prints:
- total searches
- total time (us)
- average time per search (us)

> Note: the same course dataset is loaded into both trees to provide an apples-to-apples comparison.

## CSV Format
Expected line format:
```
CourseId,Title,Prereq1,Prereq2,...
```

Example:
```
CS200,Data Structures,CS100
```

## Unit Tests
Compile unit test manually:

```bash
g++ -std=c++17 -I../include ../src/avl.cpp ../src/benchmark.cpp ../src/bst.cpp ../src/csv_loader.cpp ../src/utils.cpp smoke_test.cpp -o smoke_test
./smoke_test
```

```bash
g++ -std=c++17 -I../include ../src/avl.cpp ../src/benchmark.cpp ../src/bst.cpp ../src/csv_loader.cpp ../src/utils.cpp test_trees.cpp -o test_trees
./test_trees
```

## Notes on Testability
- The tree implementations share a common interface: `ICourseTree`
- CSV parsing is isolated in `csv_loader.*`
- String normalization and parsing helpers are isolated in `utils.*`
- This structure enables unit tests to target components independently (loader behavior, BST/AVL insert + search, benchmark harness)

## License
For educational/portfolio use.
