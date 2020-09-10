def _cc_embed_impl(ctx):
    out = ctx.actions.declare_file(ctx.label.name + ".h")
    args = [out.path] + [ctx.file.file.path]
    ctx.actions.run(
        inputs = ctx.files.file,
        outputs = [out],
        arguments = args,
        progress_message = "Generating embedded file %s" % out.short_path,
        executable = ctx.executable.gen_tool,
    )
    compilation_context = cc_common.create_compilation_context(
        headers = depset([out])
    )
    return [DefaultInfo(files = depset([out])), CcInfo(
        compilation_context = compilation_context
    )]

cc_embed = rule(
    implementation = _cc_embed_impl,
    attrs = {
        "file": attr.label(allow_single_file = True, mandatory = True),
        "gen_tool": attr.label(
            executable = True,
            cfg = "host",
            allow_files = True,
            default = Label("//:cc_embed"),
        )
    }
)