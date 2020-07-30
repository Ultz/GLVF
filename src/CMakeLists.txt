# CMakeList.txt : CMake project for glvf, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

# Add source to this project's executable.
add_library (glvf "ErrorPump.cpp"
                  "EventPump.cpp"
                  "Instance.cpp"
                  "View.cpp"
                  "GlfwInstance.cpp"
                  "GlfwPlatform.cpp"
                  "GlfwView.cpp"
                  "glvf_impl.cpp" "Glfw.h")
target_compile_features(glvf PUBLIC cxx_std_17)
target_link_libraries(glvf glfw sndfile-static)
target_include_directories(glvf 
 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_include_directories(glvf 
 PUBLIC
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>)

# TODO: Add tests and install targets if needed.
