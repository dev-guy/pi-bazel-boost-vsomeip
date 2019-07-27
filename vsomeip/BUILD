load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cmake_external(
    name = "vsomeip",
    # Values to be passed as -Dkey=value on the CMake command line;
    # here are serving to provide some CMake script configuration options
    cache_entries = {
        "BOOST_ROOT": "$EXT_BUILD_DEPS/boost/",
        "BOOST_INCLUDEDIR": "$EXT_BUILD_DEPS/boost/include",
        "MAKEFLAGS": "-j5",
        # "ENABLE_SIGNAL_HANDLING": "1"
    },
    lib_source = "@vsomeip//:all",
    # We are selecting the resulting static library to be passed in C/C++ provider
    # as the result of the build;
    # However, the cmake_external dependants could use other artefacts provided by the build,
    # according to their CMake script
    shared_libraries = [
        "libvsomeip.so.2",
        "libvsomeip-cfg.so.2",
        "libvsomeip-sd.so.2",
    ],
    visibility = ["//visibility:public"],
    deps = [
        # This is specified in the main build file because Boost Filesystem is needed
        # which is also used by boost::log
        # "//boost:log",
    ],
)
