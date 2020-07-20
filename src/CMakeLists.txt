# CMakeList.txt : CMake project for glvf, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB SOURCE_FILES "*.cpp" "**/*.cpp")
file(GLOB HEADER_FILES "../include/*.h" "../include/**/*.h")
file(GLOB IMPL_HEADER_FILES "*.h" "**/*.h")
include_directories("../include")

# Add source to this project's executable.
add_library (glvf ${SOURCE_FILES} ${HEADER_FILES} ${IMPL_HEADER_FILES})

# TODO: Add tests and install targets if needed.
