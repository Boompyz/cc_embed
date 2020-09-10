load("//:cc_embed.bzl", "cc_embed")

cc_embed(
    name = "example",
    file = "example.bin",
)

cc_binary(
    name = "hello_world",
    srcs = ["hello_world.cpp"],
    deps = [
        ":example",
    ],
)