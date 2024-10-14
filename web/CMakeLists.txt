cmake_minimum_required(VERSION 3.16)

# Set up runtime library for MSVC
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

option(PRODUCTION_BUILD "Make this a production build" OFF)

if(MSVC)
    add_compile_options(/arch:AVX2) # Ensure SIMD optimizations take place
endif()

set(NAME limestone)
project(${NAME})

# Use FetchContent for external dependencies
include(FetchContent)

# Compiler flags for different build types
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -O3 -pedantic")

# WebAssembly specific flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1")
set(CMAKE_EXECUTABLE_SUFFIX ".html")

# Source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/../src/core/*.cpp"
    "${PROJECT_SOURCE_DIR}/../src/core/*.hpp"
    "${PROJECT_SOURCE_DIR}/../src/web/*.cpp"
    "${PROJECT_SOURCE_DIR}/../src/web/*.hpp"
)

# Specify binary directories for external libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/../external/fmt "${CMAKE_BINARY_DIR}/fmt_build")
add_subdirectory(${CMAKE_SOURCE_DIR}/../external/glad "${CMAKE_BINARY_DIR}/glad_build")
add_subdirectory(${CMAKE_SOURCE_DIR}/../external/imgui "${CMAKE_BINARY_DIR}/imgui_build")

# Create the main executable
add_executable(${NAME} WIN32 ${SRC_FILES})

# Conditional compilation definitions
if(PRODUCTION_BUILD)
    target_compile_definitions(${NAME} PUBLIC ROMS_PATH="./roms/")
else()
    target_compile_definitions(${NAME} PUBLIC ROMS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/roms/")
    target_compile_definitions(${NAME} PUBLIC PRODUCTION_BUILD) 
endif()

if(MSVC)
    set_target_properties(${NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

target_compile_definitions(${NAME} PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS=1)
target_link_libraries(${NAME} fmt glad imgui)
