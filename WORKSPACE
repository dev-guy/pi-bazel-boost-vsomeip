workspace(name = "pecomp")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# Raspberry Pi (begin)
# This also sets up clang
load("//tools/workspace:default.bzl", "add_default_repositories")

add_default_repositories()

load(
    "@rpi_bazel//tools/workspace:default.bzl",
    rpi_bazel_add = "add_default_repositories",
)

rpi_bazel_add()
# Raspberry Pi (end)

# Building with cmake and b2 (begin)
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""
# Building with cmake and b2 (end)

# Boost
http_archive(
    name = "boost",
    build_file_content = all_content,
    strip_prefix = "boost_1_65_0",
    urls = ["https://sourceforge.net/projects/boost/files/boost/1.65.0/boost_1_65_0.tar.gz"],
)

# Google Test
http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-master",
    url = "https://github.com/google/googletest/archive/master.zip",
    #     sha256 = "d21ba93d7f193a9a0ab80b96e8890d520b25704a6fac976fe9da81fffb3392e3",
    #     strip_prefix = "googletest-8b6d3f9c4a774bef3081195d422993323b6bb2e0",
    #     urls = ["https://github.com/google/googletest/archive/8b6d3f9c4a774bef3081195d422993323b6bb2e0.zip"],  # 2019-03-05
)

# GENIVI/vsomeip
http_archive(
    name = "vsomeip",
    build_file_content = all_content,
    strip_prefix = "vsomeip-master",
    urls = ["https://github.com/GENIVI/vsomeip/archive/master.zip"],
    # sha256 = "211fc6264f38508a16da28904829b7e3d2b37e6c8e8265341b0d21a09e7d92d5",
    # strip_prefix = "vsomeip-2.10.21",
    # urls = ["https://github.com/GENIVI/vsomeip/archive/2.10.21.zip"],  # 2018-05-22
)
