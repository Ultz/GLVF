# CMakeList.txt : CMake project for glvf, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable(example "main.cpp")
target_compile_features(example PUBLIC cxx_std_17)
target_link_libraries(example glvf)

# TODO: Add tests and install targets if needed.
