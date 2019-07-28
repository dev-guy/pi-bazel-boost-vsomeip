# Introduction

This project attempts to demonstrate the following:

1. Building Boost (1.65) shared libraries, Google Test, and a CMake-based library (GENIVI/vsomeip) with Bazel, via [bazelbuild/rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc)
2. Targeting the above for the Raspberry Pi using a different (preferably faster) platform such as Ubuntu, via [mjbots/rpi_bazel](https://github.com/mjbots/rpi_bazel)

# The Problem

[A similar project](https://github.com/dev-guy/vsomeip-bazel) works on x86 Ubuntu. I want to build that project for the Raspberry Pi, but on Ubuntu because it's faster and more convenient. mjbots/rpi_bazel to the rescue!

Unfortunately, mjbots/rpi_bazel doesn't play nice with bazelbuild/rules_foreign_cc. As demonstrated by this project, not even the Ubuntu build works. Let's fix it!

*Can we power lift this boulder together?*

We need to fix the following two issues:

1. Boost shared libraries are successfully created for the host operating system but fails to create shared libraries for the Raspberry Pi
2. CMake projects don't work when building for either the host or the Raspberry Pi

# Related GitHub Issues

1. https://github.com/bazelbuild/rules_foreign_cc/issues/297
2. https://github.com/mjbots/rpi_bazel/issues/3

# Why Bazel?

Multi-platform C++ projects are common. However, they are difficult to build. Bazel can fix this by making it easy for C++ developers to integrate the Bazel, Boost:b2, CMake, and toolchain ecosystems so that a single machine containing fast hardware can target multiple platforms including constrained systems such as the Raspberry Pi, thus avoiding complex orchestration and software installation on target platforms.

My ultimate goal is to support other platforms than the Raspberry Pi with a similar approach to mjbots/rpi_bazel, such as [IMX Linux](https://www.nxp.com/support/developer-resources/run-time-software/linux-software-and-development-tools/embedded-linux-for-i.mx-applications-processors:IMXLINUX). I admit that I have no idea how to do this. Today, rpi_bazel is black magic to me. I either want to learn or someone else needs to step up and do the same for more platforms, particularly embedded platforms that need C++. All other types of hardware can and should run [memory-safe code](https://en.wikipedia.org/wiki/Memory_safety).

Know your customer, Bazel evangelists!

Here is some additional reading on this topic:

- [Bazel Toolchains](https://docs.bazel.build/versions/master/toolchains.html)
- [Configuring bazel to cross compile for the Raspberry Pi 3](https://jpieper.com/2018/10/28/configuring-bazel-to-cross-compile-for-the-raspberry-pi-3)

# Requirements

1. Some form of Linux such as Ubuntu 18
2. Bazel 0.26.1 or later. Version 0.28.1 seems to work OK.

# If you don't want to install gcc

The goal of this project is to build everything with clang instead of gcc. If gcc is not installed, you need to tell Bazel to use clang.

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
boost/BUILD doesn't work even for the host platform unless this file specifies a toolset. Therefore, --with-toolset=clang is used.

Despite Boost appearing to build correctly, x86 shared libraries are built instead of ARM-compatible libraries. This can be verified using the 'file' command. I tried hard-coding toolset=arm-clang instead, but was still unsuccessful.

At any rate, the architecture (--cpu=pi) should affect the Boost build. The specified toolset should not be hard-coded. 

```bash
ld.lld: error: bazel-out/armeabihf-fastbuild/bin/_solib_armeabihf/_U_S_Sboost_Clog___Uboost_Slog_Slib/libboost_atomic.so.1.65.0 is incompatible with armelf_linux_eabi
```

### CMake Failure
CMake (GENIVI/vsomeip) fails with:

```bash
/tmp/tmp.X5xqrpaTj2/CMakeFiles/CMakeTmp/external/org_llvm_clang/bin/clang: No such file or directory
```
