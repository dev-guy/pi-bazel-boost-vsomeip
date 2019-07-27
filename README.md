# Introduction

This project demonstrates:

1. Building Boost (1.65) shared libraries, Google Test, and a CMake-based library (genivi/vsomeip)
   with Bazel using https://github.com/bazelbuild/rules_foreign_cc 
2. Building the above for the Raspberry Pi on a different (preferably faster) platform
   such as x86 64-bit Ubuntu with Bazel using https://github.com/mjbots/rpi_bazel

# ... But building for the Raspberry Pi doesn't work

This repo was created so the community can get this working for the greater good.

# If you don't want to install gcc

The goal of this project is to build everything with clang instead of gcc. If gcc is not
installed, you need to tell Bazel to use clang.

```bash
export CC=/usr/bin/clang
```

# Creating the executable

The executable will be located in bazel-bin/test/test

## For Linux
```bash
bazel build test
```
## For Raspberry Pi
This doesn't work yet!

```bash
bazel build --compiler=clang --cpu=pi test
```
