# CMakeList.txt : CMake project for glvf, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(glfw3 CONFIG REQUIRED)

include_directories("../include")

# Add source to this project's executable.
add_library (glvf "../include/glvf.h"
                  "../include/glvf_core.h" 
                  "../include/glvf_enhanced_debugging.h"
                  "../include/glvf_events.h"
                  "../include/glvf_features.h"
                  "../include/glvf_input.h"
                  "../include/glvf_input_enums.h"
                  "../include/glvf_opengl.h"
                  "../include/glvf_view.h"
                  "../include/glvf_vulkan.h"
                  "ErrorPump.h"
                  "ErrorPump.cpp"
                  "EventPump.h"
                  "EventPump.cpp"
                  "Instance.h"
                  "Instance.cpp"
                  "View.h"
                  "View.cpp"
                  "Platform.h"
                  "GlfwInstance.h"
                  "GlfwInstance.cpp"
                  "GlfwPlatform.h"
                  "GlfwPlatform.cpp"
                  "GlfwView.h"
                  "GlfwView.cpp"
                  "glvf_impl.cpp")
target_link_libraries(glvf glfw sndfile-static)

# TODO: Add tests and install targets if needed.
