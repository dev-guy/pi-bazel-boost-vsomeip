load("@rules_foreign_cc//tools/build_defs:boost_build.bzl", "boost_build")

# See http://www.sven-johannsen.de/programmierung/build_boost_libs.html
# See http://manpages.ubuntu.com/manpages/bionic/man1/b2.1.html

boost_build(
    name = "log",
    #bootstrap_options = [
    #    "--with-toolset=clang",
    #    "--without-libraries=python",
    #],
    lib_source = "@boost//:all",
    shared_libraries = [
        # Linux
        "libboost_atomic.so.1.65.0",
        "libboost_chrono.so.1.65.0",
        "libboost_date_time.so.1.65.0",
        "libboost_filesystem.so.1.65.0",
        "libboost_log.so.1.65.0",
        "libboost_log_setup.so.1.65.0",
        "libboost_regex.so.1.65.0",
        "libboost_system.so.1.65.0",
        "libboost_thread.so.1.65.0",
        # OSX
        # "libboost_atomic.dylib",
        # "libboost_chrono.dylib",
        # "libboost_date_time.dylib",
        # "libboost_filesystem.dylib",
        # "libboost_log.dylib",
        # "libboost_log_setup.dylib",
        # "libboost_regex.dylib",
        # "libboost_system.dylib",
        # "libboost_thread.dylib",
    ],
    user_options = [
        "threading=multi",
        "link=shared",
        "cxxflags=-std=c++11",
        # "toolset=clang-arm",
        # "toolset=armv7-linux-gnueabihf",
        # "toolset=arm-linux-gnueabihf",
        # "variant=debug",
        "-d0",  # Minimal output
        "-j5",  # Build with parallel processes
        "--with-log",
    ],
    visibility = ["//visibility:public"],
)
