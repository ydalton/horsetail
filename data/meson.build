builtin_sources = files(
  'builtin/simple.vert.glsl',
  'builtin/simple_mvp.vert.glsl',
  'builtin/simple.frag.glsl',
)

builtin_h = custom_target(
  output: 'builtin.h',
  input: builtin_sources,
  command: [incbin, '-H', '-o', '@OUTPUT@', '@INPUT@' ],
  build_by_default: true
)

builtin_c = custom_target(
  output: 'builtin.c',
  input: builtin_sources,
  command: [incbin, '-o', '@OUTPUT@', '@INPUT@' ],
  depends: builtin_h,
  build_by_default: true
)

horsetail_sources += builtin_c
