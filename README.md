# Introduction

This project demonstrates:

1. Building Boost (1.65) shared libraries, Google Test, and a CMake-based library (genivi/vsomeip)
   with Bazel using https://github.com/bazelbuild/rules_foreign_cc 
2. Building the above for the Raspberry Pi on a different (preferably faster) platform
   such as x86 64-bit Ubuntu with Bazel using https://github.com/mjbots/rpi_bazel

# Building for the Raspberry Pi doesn't work

This repository was created so the community can help me and the greater good build
my project for the Raspberry Pi.

# Why Bazel?

Multi-platform C++ projects are common but are notoriously difficult to build. Bazel can fix this
by making it easy for C++ developers to integrate Boost b2, CMake, and toolchain ecosystems.

# If you don't want to install gcc

The goal of this project is to build everything with clang instead of gcc. If gcc is not
installed, you need to tell Bazel to use clang.

```bash
export CC=/usr/bin/clang
```

# Creating the test executable

The executable will be located in bazel-bin/test/test

## For Linux
```bash
bazel build test
```

## For Raspberry Pi
This doesn't work yet!

```bash
bazel build --cpu=pi test
```
