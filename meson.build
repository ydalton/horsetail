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

host_system = host_machine.system()

cc = meson.get_compiler('c')
incbin = find_program('tools/incbin.py')

sdl3_dep = dependency('sdl3')
math_dep = cc.find_library('m')
if host_system == 'linux'
  glesv2_dep = dependency('glesv2')
endif

add_project_arguments('-DHT_ENGINE_VERSION="' + meson.project_version() + '"', language: 'c')

buildtype = get_option('buildtype')
use_resource_file = get_option('use_resource_file')

ht_c_args = [
  '-Wno-error=unused-variable',
  '-Wno-error=unused-but-set-variable',
]

# dumb
if host_system == 'darwin'
  ht_c_args += '-U_LIBCPP_ENABLE_ASSERTIONS'
endif


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

include_dirs = include_directories('include', 'include/vendor', 'src')

horsetail_deps = [
  sdl3_dep,
  math_dep,
]

if host_system == 'linux'
  horsetail_deps += glesv2_dep
elif host_system == 'darwin'
  horsetail_deps += declare_dependency(
    link_args: ['-L../lib', '-lEGL', '-lGLESv2']
  )
  install_data(files('lib/libEGL.dylib'), install_dir: '')
  install_data(files('lib/libGLESv2.dylib'), install_dir: '')
endif

ht_exe = executable(
  'ht',
  horsetail_sources,
  c_args: ht_c_args,
  cpp_args: ht_c_args,
  link_args: ht_link_args,
  dependencies: horsetail_deps,
  include_directories: include_dirs,
)
