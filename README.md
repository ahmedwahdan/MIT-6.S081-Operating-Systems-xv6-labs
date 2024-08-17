# MIT-6.S081 Operating Systems xv6 Labs

This repository contains my solutions and implementations for the labs in the MIT 6.S081 Operating Systems course, focusing on the xv6 operating system.

## Lab 1: Ping-Pong IPC

### Description

In this lab, I implemented a program that uses UNIX system calls to "ping-pong" a byte between two processes over a pair of pipes, one for each direction. The program also measures its performance in exchanges per second.

### Implementation Details

- The program creates two pipes: one for sending data from parent to child (ping pipe) and another for sending data from child to parent (pong pipe).
- It uses `fork()` to create a child process.
- The parent process sends a byte through the ping pipe and receives it back through the pong pipe.
- The child process receives the byte from the ping pipe, increments it, and sends it back through the pong pipe.
- This exchange is repeated 1000 times.
- The program measures the time taken for these exchanges using the `uptime()` system call and calculates the exchanges per second.

### Key Learnings

- Understanding and implementing inter-process communication (IPC) using pipes.
- Proper handling of file descriptors in parent and child processes.
- Measuring performance in a minimal operating system environment.
- Importance of using `exit()` instead of `return` in the main function when working with xv6.

### How to Run

1. Clone the xv6 repository and set it up according to the course instructions.
2. Copy the `pingpong.c` file into the xv6 source directory.
3. Modify the Makefile to include `pingpong` in the `UPROGS` list.
4. Compile xv6 using `make`.
5. Run xv6 in QEMU using `make qemu`.
6. At the xv6 shell prompt, type `pingpong` to run the program.

### Performance

The program measures and outputs its performance in exchanges per second. The actual performance may vary depending on the system and QEMU configuration.

## Future Labs

This README will be updated as more labs are completed, with each lab having its own section detailing the implementation, key learnings, and any specific instructions for running the programs.
