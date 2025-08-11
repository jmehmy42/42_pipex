# 42_pipex

Welcome to **42_pipex** — a minimalist UNIX pipe emulator written in C for the 42 curriculum. This project explores how shells handle command piping and I/O redirection, by recreating the mechanics behind the classic pipe (`|`) operator.

---

## 🚀 Project Overview

**pipex** reproduces the behavior of shell command piping, allowing you to execute two commands with input/output redirection, just like:

```bash
< infile cmd1 | cmd2 > outfile
```

- Reads input from a file
- Pipes the output of the first command to the second
- Writes the final output to another file

---

## 🛠 Features

- Executes two commands connected via a pipe
- Handles file input/output redirection
- Robust error messages for file access and command failure
- Minimal memory leaks (Valgrind-friendly)
- Compact, readable C codebase

---

## 📦 Getting Started

### Prerequisites

- GNU/Linux or macOS
- GCC or Clang
- Make

### Build

```bash
make
```

### Run

```bash
./pipex infile "cmd1" "cmd2" outfile
```

**Example:**

```bash
./pipex input.txt "grep 42" "wc -l" output.txt
```
This runs `grep 42 < input.txt | wc -l > output.txt`

---

## 📚 Project Structure

- **src/** — Source files
- **include/** — Header files
- **Makefile** — Build script

---

## 👨‍💻 Author

- [jmehmy42](https://github.com/jmehmy42)

---

## 🎓 About

Created as part of the [42 School] program, this project teaches low-level process management and inter-process communication in C using UNIX system calls.

---

## 📄 License

This project is for educational purposes only.

---

> _“Everything should be made as simple as possible, but not simpler.”_
