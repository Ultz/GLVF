# CMakeList.txt : CMake project for glvf, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (IOS)
elseif(ANDROID)
else()
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
endif()

# Add source to this project's executable.
add_library (glvf "ErrorPump.cpp"
                  "EventPump.cpp"
                  "Instance.cpp"
                  "View.cpp"
                  "glfw/GlfwInstance.cpp"
                  "glfw/GlfwPlatform.cpp"
                  "glfw/GlfwView.cpp"
                  "glvf_impl.cpp"
				  "glfw/GlfwJoystick.cpp"
				  "glfw/GlfwEnumCast.cpp")
target_compile_features(glvf PUBLIC cxx_std_17)
target_include_directories(glvf 
 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

if (IOS)
elseif (ANDROID)
else()
target_link_libraries(glvf PRIVATE glfw)
target_include_directories(glvf 
 PUBLIC
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>)
endif()

# TODO: Add tests and install targets if needed.
