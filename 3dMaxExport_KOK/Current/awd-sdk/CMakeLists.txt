set(LIBRARY_NAME libawd)

cmake_policy(SET CMP0043 NEW)
file(GLOB INCS cpp-libawd/include/*.h cpp-libawd/include/*.cc)
file(GLOB SRCS cpp-libawd/src/*.h cpp-libawd/src/*.cc)
file(GLOB ZLIB cpp-libawd/lib/zlib/*.h cpp-libawd/lib/zlib/*.c)
file(GLOB LZMA cpp-libawd/lib/lzma/*.h cpp-libawd/lib/lzma/*.c)
set(LIBRARY_SRCS ${INCS} ${SRCS} ${ZLIB} ${LZMA})

ADD_DEFINITIONS(-D_7ZIP_ST)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/cpp-libawd/include
  ${CMAKE_CURRENT_SOURCE_DIR}/cpp-libawd/lib/zlib
  ${CMAKE_CURRENT_SOURCE_DIR}/cpp-libawd/lib/lzma
)

add_library(${LIBRARY_NAME} STATIC
  ${LIBRARY_SRCS}
)