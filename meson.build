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

cc = meson.get_compiler('c')

sdl3_dep = dependency('sdl3')
glesv2_dep = dependency('glesv2')
math_dep = cc.find_library('m')

if get_option('buildtype') == 'debug'
  add_project_arguments('-DHT_DEBUG', language: 'c')
endif

horsetail_sources = files(
  'src/core/event.c',
  'src/core/main.c',
  'src/lg/lg.c',
  'src/lib/math.c',
  'src/lib/util.c',
  'src/mem/mem.c',
  'src/impl/sdl.c',
  'src/vg/vg.c',
  'src/vg/vg_gl.c',
  'src/vg/display.c',
)

horsetail_dependencies = [
  sdl3_dep,
  glesv2_dep,
  math_dep,
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
