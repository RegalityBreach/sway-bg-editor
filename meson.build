project('sway-bg-editor', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

gtkmm_dep = dependency('gtkmm-4.0')

sources = files(
  'main.cc',
  'window.cc',
  'folderselector.cc',
  'backgroundslist.cc'
)

executable('sway-bg-editor',
  sources,
  dependencies : gtkmm_dep,
  install : true)
