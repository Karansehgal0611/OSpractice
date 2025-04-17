# 🧠 Operating Systems Practice – C Programs

This repository contains a collection of C programs demonstrating key concepts in Operating Systems. It includes implementations of scheduling algorithms, memory management techniques, synchronization mechanisms, and inter-process communication.

## 📂 Contents

### 🕒 CPU Scheduling Algorithms
- `FCFS.c` – First-Come, First-Served Scheduling
- `SJFpre.c` – Shortest Job First (Preemptive)
- `SJFnonpre.c` – Shortest Job First (Non-Preemptive)
- `RRpre.c` – Round Robin Scheduling
- `prioritypre.c` – Priority Scheduling (Preemptive)

### 📦 Memory Management
- `Partitioning.c` – Memory Partitioning Techniques
- `FIFO.c` – First-In-First-Out Page Replacement
- `LRU.c` – Least Recently Used Page Replacement
- `MRU.c` – Most Recently Used Page Replacement
- `optimal.c` – Optimal Page Replacement Algorithm

### 🔐 Synchronization & Concurrency
- `petersons.c`, `petersons1.c` – Peterson’s Algorithm for Mutual Exclusion
- `dinersPhilo.c`, `dinersPhilo1.c` – Dining Philosophers Problem
- `readerwriter.c` – Reader-Writer Problem
- `prodcons.c` – Producer-Consumer Problem
- `basicFork.c` – Demonstration of Process Creation using `fork()`
- `orphan1.c` – Orphan Process Example

### 🛡️ Deadlock Avoidance
- `Bankers.c`, `Bankers1.c`, `bankers1.c` – Banker's Algorithm Implementations

### 📡 Communication Protocols
- `stopnwait.c` – Stop-and-Wait Protocol
- `checksum.c` – Checksum Error Detection
- `CRC .c` – Cyclic Redundancy Check (CRC)
- `hamming.c` – Hamming Code for Error Detection and Correction

### 🧪 Miscellaneous
- `f1.c`, `f2.c`, `f3.c` – Miscellaneous Practice Programs (forking and pids )
- `s1.c`, `s2.c` – Additional Scheduling Examples  and Semaphores
- `schedule1.c` to `schedule5.c` – Various Scheduling Implementations

## 🚀 Getting Started

To compile and run any of the programs:

```bash
gcc filename.c -o output
./output
```
---

## Author 
Karan Sehgal
