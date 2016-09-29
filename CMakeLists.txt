cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(lat LANGUAGES CXX)

find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(LibLZMA REQUIRED)
find_package(EXPAT REQUIRED)
find_package(LibArchive REQUIRED)
find_path(LIBUCHARDET_INCLUDE_DIRS uchardet/uchardet.h)
find_library(LIBUCHARDET_LIBRARIES NAMES uchardet libuchardet)
find_library(ICONV_LIBRARIES NAMES iconv libiconv)
find_library(ICONV_LIBRARIES NAMES iconv libiconv)

include_directories(${LibArchive_INCLUDE_DIRS} ${LIBUCHARDET_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
  ${LibArchive_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${BZIP2_LIBRARIES}
  ${LIBLZMA_LIBRARIES}
  ${EXPAT_LIBRARIES}
  ${LIBUCHARDET_LIBRARIES}
  ${ICONV_LIBRARIES}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
