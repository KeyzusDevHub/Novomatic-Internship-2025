cmake_minimum_required(VERSION 3.17)
project(NOVOMATIC_TASK_2)

cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)

FetchContent_MakeAvailable(glm)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(NOVOMATIC_TASK_2 ${SOURCES})

target_include_directories(NOVOMATIC_TASK_2 PRIVATE dependencies headers)

target_link_libraries(NOVOMATIC_TASK_2 OpenGL::GL glfw glm)

add_custom_command(
    TARGET NOVOMATIC_TASK_2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:NOVOMATIC_TASK_2>/shaders
)

enable_testing()

add_executable(NOVOMATIC_TASK_2_TEST
    tests/Test.cpp
    src/Triangle.cpp
)

target_link_libraries(NOVOMATIC_TASK_2_TEST PRIVATE
    GTest::gtest_main
    OpenGL::GL
    glfw
    glm
)

target_include_directories(NOVOMATIC_TASK_2_TEST PRIVATE dependencies headers)

include(GoogleTest)
gtest_discover_tests(NOVOMATIC_TASK_2_TEST)
