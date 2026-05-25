cmake_minimum_required(VERSION 3.15)
project(NucleusFileManagement)

set(CMAKE_CXX_STANDARD 17)

add_library(NucleusFileManagement src/FileWrapper.cpp
)

target_include_directories(NucleusFileManagement PUBLIC include)

add_executable(example examples/main.cpp)
target_link_libraries(example NucleusFileManagement)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(FileWrapperTests
  tests/FileWrapperTest.cpp
)
target_link_libraries(FileWrapperTests
  PRIVATE
  NucleusFileManagement
  gtest
  gtest_main
  pthread
)

add_test(NAME FileWrapperTests COMMAND FileWrapperTests)
