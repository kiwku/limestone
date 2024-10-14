#TODO: Add fmt
#TODO: Add ffmeg
#TODO: Add imgui
#TODO: Add vulkan-headers
#TODO: Add vulkan-memory-allocator
#TODO: Add vulkan-glslang
#TODO: Add stb
#TODO: Add rcheevos
#TODO: Add glad2

cmake_minimum_required(VERSION 3.16)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

option(PRODUCTION_BUILD "Make this a production build" OFF)

if(MSVC) 
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

set(NAME limestone)

include(FetchContent)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -O3 -pedantic")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/fmt)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/Vulkan-Headers)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/VulkanMemoryAllocator)
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
target_link_libraries(${NAME} imgui)

