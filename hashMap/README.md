# Hash Map Implementations in C++

This repository contains different implementations of **Hash Maps** in C++ along with a report analyzing their runtime performance.

## 📂 Contents
- **Separate Chaining with Red-Black Tree**
  - Handles collisions by maintaining a Red-Black Tree at each bucket.
  - Ensures efficient insert, delete, and search operations with balanced tree properties.

- **Open Addressing**
  - **Linear Probing**
  - **Double Hashing**
  - Both strategies handle collisions by probing alternative slots within the hash table.

- **Performance Report**
  - Includes analysis and comparison of runtime performance for each method.
  - Evaluates metrics such as:
    - Collisions
    - Probes
    - Load factor effect
    - Average search, insert, and delete times

## 🚀 Features
- Fully implemented hash map data structures
- Red-Black Tree based chaining for optimized performance
- Comparison between linear probing and double hashing
- Detailed runtime report for experimental evaluation

## 🛠️ Compilation & Usage
Make sure you have a C++ compiler (e.g., `g++`).

```bash
# Compile
g++ -std=c++17 filename.cpp -o output

# Run
./output
