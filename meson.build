project('NucleusFileWrapper', 'cpp', default_options: ['cpp_std=c++20'])

subdir('src')

file_wrapper_lib = library('NucleusFileWrapper', file_wrapper_sources,
  include_directories: include_directories('../include'),
  install: true
)

install_headers('include/FileWrapper.h',
                subdir: 'NucleusFileWrapper')

subdir('examples')
