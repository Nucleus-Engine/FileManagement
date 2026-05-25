gtest = dependency('gtest', main: false, required: true)
gtest_main = dependency('gtest_main', main: true, required: true)

file_wrapper_test_exe = executable(
  'FileWrapperTests',
  'FileWrapperTest.cpp',
  include_directories: include_directories('../include'),
  link_with: file_wrapper_lib,
  dependencies: [gtest, gtest_main],
)

test('FileWrapperTest', file_wrapper_test_exe)