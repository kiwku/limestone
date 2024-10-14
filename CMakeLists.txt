cmake_minimum_required(VERSION 3.16)

#TODO: Add ffmeg
#TODO: Add stb
#TODO: Add rcheevos
#TODO: Add glad2


set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

option(PRODUCTION_BUILD "Make this a production build" OFF)

if(MSVC) 
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

set(NAME limestone)
project(${NAME})

include(FetchContent)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -O3 -pedantic")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/core/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/gui/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/*.hpp"
)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/fmt)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/Vulkan-Headers)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/VulkanMemoryAllocator)

set(ENABLE_PCH OFF CACHE BOOL "Enables Precompiled header" FORCE)
set(BUILD_EXTERNAL OFF CACHE BOOL "Build external dependencies in /External" FORCE)
set(SKIP_GLSLANG_INSTALL ON CACHE BOOL "Skip installation" FORCE)
set(ENABLE_SPVREMAPPER OFF CACHE BOOL "Enables building of SPVRemapper" FORCE)
set(ENABLE_GLSLANG_BINARIES OFF CACHE BOOL "Builds glslangValidator and spirv-remap" FORCE)
set(ENABLE_HLSL OFF CACHE BOOL "Enables HLSL input support" FORCE)
set(ENABLE_OPT OFF CACHE BOOL "Enables spirv-opt capability if present" FORCE)
set(ENABLE_CTEST OFF CACHE BOOL "Enables testing" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glslang)


add_subdirectory(${CMAKE_SOURCE_DIR}/external/imgui)

add_executable(${NAME} WIN32 ${SRC_FILES})

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
target_link_libraries(${NAME} fmt glfw glad glslang imgui)

