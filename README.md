# Introduction

This project demonstrates:

1. Building Boost (1.65) shared libraries, Google Test, and a CMake-based library (GENIVI/vsomeip) with Bazel using https://github.com/bazelbuild/rules_foreign_cc 
2. Building the above for the Raspberry Pi on a different (preferably faster) platform such as x86 64-bit Ubuntu with Bazel using https://github.com/mjbots/rpi_bazel 

# Requirements

Some form of Linux such as Ubuntu 18.

# Building for the Raspberry Pi doesn't work

This repository was created so the community can help me and the greater good build
my project for the Raspberry Pi.

# Why Bazel?

Multi-platform C++ projects are common but are notoriously difficult to build. Bazel can fix this by making it easy for C++ developers to integrate Boost b2, CMake, and toolchain ecosystems. 

# If you don't want to install gcc

The goal of this project is to build everything with clang instead of gcc. If gcc is not
installed, you need to tell Bazel to use clang.

```bash
export CC=/usr/bin/clang
```

# Creating the test executable

The executable will be located in bazel-bin/test/test

## Host (e.g., x86 64-bit Ubuntu)

```bash
bazel build test
```

CMake fails to build. See the Raspberry Pi section below.

## Raspberry Pi

```bash
bazel build --cpu=pi test
```

### Boost Failure
boost/BUILD doesn't work even for the host platform unless this file specifies a toolset. clang is specified.

Despite Boost appearing to build correctly, x86 libraries are built instead of ARM-compatible libraries. This can be verified using the 'file' command. See bazel/BUILD. Perhaps arm-clang should be specified as the toolset. I have tried many things. At any rate, the architecture (--cpu=pi) should affect the Boost build. The toolset should not be hard-coded. 

```bash
ld.lld: error: bazel-out/armeabihf-fastbuild/bin/_solib_armeabihf/_U_S_Sboost_Clog___Uboost_Slog_Slib/libboost_atomic.so.1.65.0 is incompatible with armelf_linux_eabi
```

### CMake Failure
CMake (GENIVI/vsomeip) fails with:

```bash
/tmp/tmp.X5xqrpaTj2/CMakeFiles/CMakeTmp/external/org_llvm_clang/bin/clang: No such file or directory
```
