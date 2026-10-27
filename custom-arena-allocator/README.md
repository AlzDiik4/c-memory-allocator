# Custom Arena Memory Allocator in C

High-performance linear memory allocator designed to eliminate heap fragmentation and avoid garbage collection overhead in performance-critical modules.

## Key Features
- **O(1) Allocation & Deallocation:** Fast linear pointer increments without standard `malloc` overhead.
- **8-Byte Hardware Alignment:** Optimized memory layout for modern CPU architectures.
- **Zero-Fragmentation Reset:** Reset entire memory region instantaneously.

## Build and Run
```bash
gcc -O2 arena.c -o arena
./arena