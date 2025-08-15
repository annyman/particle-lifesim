project(
  'particle-lifesim',
  'cpp',
  version: '0.1',
  meson_version: '1.8.3',
  default_options: ['cpp_std=c++23'],
)

src_files = files(
  'src/main.cpp',
  # Add more cpp files here if needed
)

inc = include_directories('include')

cpp = meson.get_compiler('cpp')

# Configure library selection and cross-platform linking
buildtype = get_option('buildtype')
is_windows = host_machine.system() == 'windows'


raylib_dir = ''

if buildtype == 'debug'
  # Dynamic link from lib/raylib for debug

  raylib_dir = meson.current_source_dir() / 'lib' / 'raylib'
  raylib_dep = cpp.find_library('raylib', dirs: [raylib_dir], required: true, static: false)
  link_args = []

elif buildtype == 'release' and is_windows
  # Static link from lib/raylib-windows for release-windows

  raylib_dir = meson.current_source_dir() / 'lib' / 'raylib-windows'
  raylib_dep = cpp.find_library('raylib', dirs: [raylib_dir], required: true, static: true)

  link_args = ['-mwindows', '-static', '-static-libgcc', '-static-libstdc++']
  windows_mod = import('windows')
  icon_res = windows_mod.compile_resources('assets/img/icon.rc')
  src_files += icon_res

elif buildtype == 'release'
  # Linux release uses system-provided raylib
  raylib_dep = dependency('raylib', required: true)
  link_args = ['-static', '-static-libgcc', '-static-libstdc++']

else
  error('Unknown build configuration: buildtype='+buildtype+' system='+host_machine.system())
endif

executable(
  'particle-lifesim',
  src_files,
  include_directories: inc,
  dependencies: [raylib_dep],
  link_args: link_args,
  win_subsystem: 'windows',
  install: true,
  install_dir: 'bin'
)
