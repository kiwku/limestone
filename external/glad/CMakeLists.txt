set(SRCS
  include/glad/gl.h
  include/KHR/khrplatform.h
  src/gl.c
)

if(APPLE)
  add_library(glad OBJECT ${SRCS})
else()
  add_library(glad ${SRCS})
endif()

target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(glad PUBLIC include/)
if(WIN32)
  target_sources(glad PRIVATE
    include/glad/wgl.h
    src/wgl.c
  )
else()
  target_sources(glad PRIVATE
    include/EGL/eglplatform.h
    include/glad/egl.h
    src/egl.c
  )
endif()