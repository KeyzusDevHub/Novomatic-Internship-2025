cmake_minimum_required(VERSION 3.17)
project(NOVOMATIC_TASK_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(NOVOMATIC_TASK_1
    src/SearchComplete.cpp
)

target_include_directories(NOVOMATIC_TASK_1 PRIVATE headers)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(NOVOMATIC_TASK_1_TEST
    tests/Test.cpp
)

target_include_directories(NOVOMATIC_TASK_1_TEST PRIVATE headers)

add_custom_command(
    TARGET NOVOMATIC_TASK_1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:NOVOMATIC_TASK_1>/tests
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/inputs
        $<TARGET_FILE_DIR:NOVOMATIC_TASK_1>/tests
)

target_include_directories(NOVOMATIC_TASK_1_TEST PRIVATE src)

target_link_libraries(NOVOMATIC_TASK_1_TEST
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(NOVOMATIC_TASK_1_TEST)