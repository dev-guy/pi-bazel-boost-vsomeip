cc_test(
    name = "test",
    srcs = [
        "dir_test.cc",
        "vsomeip_test.cc",
    ],
    linkstatic = 1,
    deps = [
        "//boost:log",
        "//vsomeip",  # @vsomeip doesn't work
        "@com_google_googletest//:gtest_main",
        "@org_llvm_libcxx//:libcxx",
    ],
)
