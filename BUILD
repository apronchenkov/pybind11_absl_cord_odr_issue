load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")
load("@rules_python//python:defs.bzl", "py_binary")

licenses(["notice"])

pybind_extension(
    name = "clib",
    srcs = ["clib.cc"],
    deps = [
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings:string_view",
        "@pybind11_abseil//pybind11_abseil:status_casters",
    ],
)

py_binary(
    name = "test",
    srcs = ["test.py"],
    data = ["@pybind11_abseil//pybind11_abseil:status.so"],
    deps = [":clib"],
)
