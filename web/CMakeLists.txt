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

# WebAssembly specific flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sUSE_WEBGL2=1 -sFULL_ES3=1 -sWASM=1 -sUSE_GLFW=3 -o index.html")
set(CMAKE_EXECUTABLE_SUFFIX ".html") ###################### untag

# Source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/../src/common/*.cpp"
    "${PROJECT_SOURCE_DIR}/../src/common/*.hpp"
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
    target_compile_definitions(${NAME} PUBLIC WEB_COMP)
else()
    target_compile_definitions(${NAME} PUBLIC ROMS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/roms/")
    target_compile_definitions(${NAME} PUBLIC PRODUCTION_BUILD) 
    target_compile_definitions(${NAME} PUBLIC WEB_COMP)
endif()

if(MSVC)
    set_target_properties(${NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

set(APP_FILES
    "${CMAKE_SOURCE_DIR}/app/*"
)


#add_custom_target(copy_html ALL
#    COMMAND ${CMAKE_COMMAND} -E copy ${APP_FILES} ${CMAKE_BINARY_DIR}/
#    COMMENT "Copying HTML files to the build directory"
#)

target_compile_definitions(${NAME} PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS=1)
target_link_libraries(${NAME} fmt glad imgui)
