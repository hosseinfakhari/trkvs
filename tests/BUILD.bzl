load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "kvslib_test",
    srcs = ["libkvs_test.cpp"],
    deps = [
        "//src/lib:libkvs",
        "@com_google_googletest//:gtest_main",
    ],
)