cmake_minimum_required(VERSION 3.15)
project(NucleusFileManagement)

set(CMAKE_CXX_STANDARD 17)

# Add logger library
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

find_package(GTest REQUIRED)

add_executable(FileWrapperTests
    tests/FileWrapperTest.cpp
)

target_link_libraries(FileWrapperTests
    PRIVATE
        FileManagement
        GTest::GTest
        GTest::Main
        pthread
)

add_test(NAME FileWrapperTests COMMAND FileWrapperTests)
