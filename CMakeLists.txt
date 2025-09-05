cmake_minimum_required(VERSION 3.10.0)
project(Scratch VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Scratch main.cpp Tensor.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Scratch PRIVATE SCRATCH_BUILD_DEBUG)
else()
    target_compile_definitions(Scratch PRIVATE SCRATCH_BUILD_RELEASE)
endif()