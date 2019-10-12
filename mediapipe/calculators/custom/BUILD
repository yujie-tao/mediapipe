licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:private"])

load("//mediapipe/framework/port:build_config.bzl", "mediapipe_cc_proto_library")

cc_library(
    name = "landmarks_to_plot_calculator",
    srcs = ["landmarks_to_plot_calculator.cc"],
    visibility = ["//visibility:public"],
    deps = [
    	"//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:landmark_cc_proto",
        "//mediapipe/framework/formats:location",
        "//mediapipe/framework/port:ret_check",
        "//mediapipe/framework/port:status",
    ],
    alwayslink = 1,
)