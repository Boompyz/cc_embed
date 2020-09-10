# `cc_embed` -- Bazel rule to embed a binary file in C++

To use these rules, add the following to your `WORKSPACE` file:

```bazel
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "com_github_boompyz_cc_embed",
    commit = "78e62db86cc1769c14e1d82127a3363caae050a6",
    remote = "https://github.com/Boompyz/cc_embed",
)
```

You can then load the rule and use it.

```bazel
load("@com_github_boompyz_cc_embed//:cc_embed.bzl", "cc_embed")

cc_embed(
    name = "some_file",
    file = "some_file.bin",
)
```

You can then get the contents of the file by calling a function.

For a file named `example/example.bin` in a rule `//example:example`:

```cpp
#include "example/example.h"
...
    std::string contents = example_example_bin::GetContentString();
    const std::vector<unsigned char> content = example_example_bin::GetContent();
...
```