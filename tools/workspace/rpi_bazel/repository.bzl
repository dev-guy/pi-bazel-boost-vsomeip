load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def rpi_bazel_repository(name):
    # commit = "6079a215f431c8f1b86c2b315fb2ab7e410b64b4"
    commit = "master"
    http_archive(
        name = name,
        url = "https://github.com/mjbots/rpi_bazel/archive/{}.zip".format(commit),
        # sha256 = "XXX",
        strip_prefix = "rpi_bazel-{}".format(commit),
    )
