if (NOT MSVC)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(SRCS
  stb_image.h
  stb_image.cpp
)

add_library(stb STATIC ${SRCS})
target_include_directories(stb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")