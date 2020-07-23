# CMakeList.txt : CMake project for glvf, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "../include/*.h" "*.h")
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${HEADER_FILES})

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp")
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SOURCE_FILES})
include_directories("../include")

# Add source to this project's executable.
add_library (glvf ${SOURCE_FILES} ${HEADER_FILES})

# TODO: Add tests and install targets if needed.
