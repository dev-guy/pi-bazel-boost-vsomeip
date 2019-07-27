load("@rules_foreign_cc//tools/build_defs:boost_build.bzl", "boost_build")

# See http://www.sven-johannsen.de/programmierung/build_boost_libs.html
# See http://manpages.ubuntu.com/manpages/bionic/man1/b2.1.html

boost_build(
    name = "log",
    bootstrap_options = [
        "--with-toolset=clang",  # This should be passed down by Bazel but is needed
        "--without-libraries=python",
    ],
    lib_source = "@boost//:all",
    shared_libraries = [
        "libboost_atomic.so.1.65.0",
        "libboost_chrono.so.1.65.0",
        "libboost_date_time.so.1.65.0",
        "libboost_filesystem.so.1.65.0",
        "libboost_log.so.1.65.0",
        "libboost_log_setup.so.1.65.0",
        "libboost_regex.so.1.65.0",
        "libboost_system.so.1.65.0",
        "libboost_thread.so.1.65.0",
    ],
    user_options = [
        "threading=multi",
        "link=shared",
        "cxxflags=-std=c++11",  # Is this passed down by Bazel already?
        # "variant=debug",
        "-d0",  # Minimal output
        "-j1",  # Build with this number of processes
        # "--with-log",
    ],
    visibility = ["//visibility:public"],
)
