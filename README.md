# Operating_Systems

Coursework and lab assignments from my university course in Operating Systems (NTUA, ECE, 03121026).

Author: **Michail‑Athanasios Peppas (ntua‑el21026)**

## Contents

- [Operating\_Systems](#operating_systems)
  - [Contents](#contents)
  - [About](#about)
  - [Repository Structure](#repository-structure)
  - [Learning Goals](#learning-goals)
  - [Quick Start](#quick-start)
  - [Assignments — Concepts \& What I Implement](#assignments--concepts--what-i-implement)
    - [1η Άσκηση — System Calls, `fork()`, IPC](#1η-άσκηση--system-calls-fork-ipc)
    - [2η Άσκηση — POSIX Threads \& Synchronization](#2η-άσκηση--posix-threads--synchronization)
    - [3η Άσκηση — `mmap()` \& Multi‑process Mandelbrot](#3η-άσκηση--mmap--multiprocess-mandelbrot)
  - [How to Run \& Evaluate](#how-to-run--evaluate)
  - [Reports \& Templates](#reports--templates)
  - [License](#license)

---

## About

This repository hosts the code and deliverables for three OS assignments. Each directory focuses on **a core OS concept** and includes **a concrete implementation** that exposes the trade‑offs you meet in real systems (fairness, synchronization overhead, I/O vs CPU balance, memory isolation, etc.).

## Repository Structure

```
- Προπαρασκευαστική Άσκηση/
- 1η Άσκηση/
- 2η Άσκηση/
- 3η Άσκηση/
- LICENSE
- README.md
```

## Learning Goals

- Build intuition for **processes vs threads** and when to prefer each.

- Practice **synchronization**: mutexes, condition variables, semaphores, and atomic operations.

- Understand **memory mappings** (`mmap`) and **copy‑on‑write** across `fork()`.

- Apply these tools to non‑trivial programs (e.g., **Mandelbrot renderer**) and analyze performance/behavior changes as the synchronization/IPC choices change.

## Quick Start

```bash
git clone https://github.com/ntua-el21026/Operating_Systems.git
cd Operating_Systems

# Build an assignment of interest:
cd "2η Άσκηση/Κώδικες Ασκήσεων"
make
./pthread-test 4 200000
./simplesync-mutex
./kgarten 4 8 2
./mandel 4 2000
./mandel_sema 4 2000
./mandel_cond 4 2000
make clean
```

> Paths use Greek names; quote them or use tab completion.

## Assignments — Concepts & What I Implement

### 1η Άσκηση — System Calls, `fork()`, IPC

**Big idea:** move from high‑level I/O to **raw system calls** and from single process to **multiple processes** that can communicate.

**What I implement & observe:**

- **`a1.1-system_calls.c`** — direct use of `open/read/write/close` and similar calls. I check return values, **handle `errno`**, and compare behavior to buffered stdio.

- **`a1.2-fork*.c`** — several `fork()` variants that create one or many child processes; I measure/observe **address‑space isolation**, **execution order**, and the effect of `wait()`/`exec()` on lifecycle control.

- **`a1.3-comm.c`** — a simple **pipe‑based IPC** demo. I set up a pipe between processes, write/read messages, and learn **EOF semantics** (closing the write end lets the reader see EOF).

**Why it matters:** This unit grounds the OS abstraction of **process** and the boundary between **kernel** and **user space** via syscalls and IPC.

### 2η Άσκηση — POSIX Threads & Synchronization

**Big idea:** shift to **threads** within a process to share address space, then enforce correctness with **synchronization primitives**.

**What I implement & compare:**

- **`pthread-test.c`** — thread creation/joining and parameter passing; stresses memory by working on big arrays to reveal cache effects.

- **`simplesync-mutex.c` vs `simplesync-atomic.c`** — increment a shared counter under two strategies: a **mutex** and **atomic ops**. I compare **correctness** and discuss when atomics are enough vs when you need higher‑level locks/conds.

- **`kgarten.c`** — classic concurrency control: I model a **kindergarten entrance/exit** where resources are limited. Using **condition variables or semaphores**, I enforce capacity/fairness and avoid starvation.

- **`mandel.c / mandel_sema.c / mandel_cond.c`** — I parallelize the **Mandelbrot set** renderer, each variant showcasing a different sync tool (plain threads, **semaphores**, **condition variables**) for work distribution and barriers.

**What to look for:**

- Throughput vs **synchronization overhead**.

- **Work partitioning** (static rows, work queues) and how it affects balance.

- Artifacts from **false sharing** and cache locality.

### 3η Άσκηση — `mmap()` & Multi‑process Mandelbrot

**Big idea:** memory as a file and files as memory; then revisit Mandelbrot with **processes** instead of threads to study IPC and OS scheduling costs.

**What I implement & explore:**

- **Part 3.1 — `mmap.c`**: I create **anonymous and file‑backed mappings**, then `fork()` to observe **copy‑on‑write**. I test how **writes** in parent/child appear, and when mappings are **shared vs private**. I also use helpers (`help.c`) to print map info and reason about page state.

- **Part 3.2 — `mandel-fork1.c`, `mandel-fork2.c`**: I split the image across **child processes**. Each variant uses a different **IPC strategy** (e.g., multiple pipes or a shared file) and partitioning scheme. Then I compare against the threaded versions to discuss **process creation/IPC overhead**, **I/O contention**, and **determinism**.

**Take‑aways:** Processes are heavier but stronger isolation can simplify failure containment. `mmap()` bridges files and memory to build zero‑copy pipelines when used carefully.

## How to Run & Evaluate

For each sub‑folder, `make` builds the targets listed in the local Makefile. Example invocations:

```bash
# 1η Άσκηση
cd "1η Άσκηση/Κώδικες Ασκήσεων" && make
./a1.1-system_calls
./a1.2-fork
./a1.3-comm

# 2η Άσκηση
cd "../../2η Άσκηση/Κώδικες Ασκήσεων" && make
./pthread-test 4 200000
./simplesync-mutex
./simplesync-atomic
./kgarten 4 8 2
./mandel 4 2000
./mandel_sema 4 2000
./mandel_cond 4 2000

# 3η Άσκηση
cd "../../3η Άσκηση/Κώδικες Ασκήσεων/3.1" && make
./mmap
cd "../3.2" && make
./mandel-fork1 4
./mandel-fork2 4
```

**Evaluation checklist:**

- Verify **correctness** under different thread/process counts and inputs.

- Observe **ordering** and **liveness** properties (no deadlocks, no starvation).

- Measure **runtime** or throughput; relate differences to synchronization/IPC choices.

- Inspect outputs (images/ASCII) for deterministic vs non‑deterministic behavior across runs.

## Reports & Templates

- Preparatory exercise PDFs and screenshots live in `Προπαρασκευαστική Άσκηση/`.

- Each assignment includes a **Παραδοτέο** folder with final submissions.

- A Word template is provided at repository root: `oslab005 - report template.docx`.

## License

Licensed under the **MIT License**. See [`LICENSE`](LICENSE).
