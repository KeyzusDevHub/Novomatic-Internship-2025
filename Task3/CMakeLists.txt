cmake_minimum_required(VERSION 3.17)
project(NOVOMATIC_TASK_3)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(NOVOMATIC_TASK_3_TEST
    tests/Test.cpp
    tests/FloatType.cpp
)

target_link_libraries(NOVOMATIC_TASK_3_TEST PRIVATE
    GTest::gtest_main
)

target_include_directories(NOVOMATIC_TASK_3_TEST PRIVATE dependencies headers)

include(GoogleTest)
gtest_discover_tests(NOVOMATIC_TASK_3_TEST)

