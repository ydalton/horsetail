project(
  'horsetail',
  ['c', 'cpp'],
  version: 'v0.0.1',
  default_options: [
    'c_std=c99',
    'cpp_std=c++98',
    'warning_level=2',
    'werror=true'
  ]
)

cc = meson.get_compiler('c')
incbin = find_program('tools/incbin.py')

sdl3_dep = dependency('sdl3')
glesv2_dep = dependency('glesv2')
math_dep = cc.find_library('m')

add_project_arguments('-DHT_ENGINE_VERSION="' + meson.project_version() + '"', language: 'c')

buildtype = get_option('buildtype')
use_resource_file = get_option('use_resource_file')

ht_c_args = [
  '-Wno-error=unused-variable',
  '-Wno-error=unused-but-set-variable',
]

ht_link_args = [
  # nope
  # '-nostdlib++'
]

if buildtype == 'debug'
  ht_c_args += '-DHT_DEBUG'
endif

if use_resource_file != ''
  ht_c_args += '-DRS_USE_RESOURCE_FILE=\"' + use_resource_file + '\"'
endif

horsetail_sources = files()

subdir('src')
subdir('data')

include_dirs = include_directories('include', 'src')

horsetail_deps = [
  sdl3_dep,
  glesv2_dep,
  math_dep,
]

ht_exe = executable(
  'ht',
  horsetail_sources,
  c_args: ht_c_args,
  cpp_args: ht_c_args,
  link_args: ht_link_args,
  dependencies: horsetail_deps,
  include_directories: include_dirs,
)
