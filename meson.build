project(
  'horsetail',
  'c',
  version: 'v0.0.1',
  default_options: [
    'c_std=c89',
    'warning_level=2',
    'werror=true'
  ]
)

sdl3_dep = dependency('sdl3')
glesv2_dep = dependency('glesv2')

horsetail_sources = files(
  'src/core/event.c',
  'src/core/main.c',
  'src/core/util.c',
  'src/impl/sdl.c',
  'src/vg/vg.c',
)

horsetail_dependencies = [
  sdl3_dep,
  glesv2_dep
]

include_dirs = [
  include_directories('include')
]

ht_exe = executable(
  'ht',
  horsetail_sources,
  dependencies: horsetail_dependencies,
  include_directories: include_dirs
)
