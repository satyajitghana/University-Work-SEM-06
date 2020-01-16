# load the rules for building
load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_compile")
load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library")

# native proto_library rule
proto_library(
    name = "zirconiumbank",
    srcs = ["zirconiumbank.proto"],
    deps = ["@com_google_protobuf//:any_proto"],
)

# create the grpc library that our server and client can depend on
cpp_grpc_library(
    name = "zirconium_cpp_grpc",
    deps = [":zirconiumbank"],
)

# cxxopts library
# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "cxxopts",
    srcs = ["cxxopts.hpp"],
    hdrs = ["cxxopts.hpp"],
    visibility = ["//visibility:public"],
)

# loguru loggin library
cc_library(
    name = "loguru",
    srcs = ["loguru.cpp"],
    hdrs = ["loguru.hpp"],
    visibility = ["//visibility:public"],
)

# binary rule to create the server executable
# depends on the grpc-proto library we made above
cc_binary(
    name = "zirconium_server",
    srcs = ["zirconium_server.cc"],
    copts = ["-Wl,-rpath,/usr/local/lib"],
    linkopts = [
        "-lmongocxx",
        "-lbsoncxx",
        "-ldl",
    ],
    deps = [
        ":cxxopts",
        ":loguru",
        ":zirconium_cpp_grpc",
        "@bsoncxx",
        "@mongocxx",
    ],
)

# binary rule to create the clien exeecutable
# depends on the grpc-proto library we made
cc_binary(
    name = "zirconium_client",
    srcs = ["zirconium_client.cc"],
    copts = [
        "-Wl,-rpath,/usr/local/lib",
    ],
    linkopts = [
        "-lmongocxx",
        "-lbsoncxx",
        "-ldl",
        "-std=c++17",
    ],
    deps = [
        ":cxxopts",
        ":loguru",
        ":zirconium_cpp_grpc",
        "@bsoncxx",
        "@mongocxx",
    ],
)
