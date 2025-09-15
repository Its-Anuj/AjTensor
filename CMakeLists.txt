cmake_minimum_required(VERSION 3.10.0)
project(Example VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tensor)

include_directories("Tensor/")
# Set output directories for all targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   # Static libraries (.lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   # Shared libraries (.dll)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   # Executables (.exe)

add_executable(Example main.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Example PRIVATE EXAMPLE_DEBUG_BUILD)
    message("[ENGINE] Debug build enabled")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Example PRIVATE EXAMPLE_RELEASE_BUILD)
    message("[ENGINE] Release build enabled")
endif()
 
target_link_libraries(Example PRIVATE kernel32 user32 gdi32 comdlg32 Tensor)