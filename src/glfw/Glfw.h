#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#ifndef _GLVF_GLFW_H
#define _GLVF_GLFW_H
#include <glvf_input_enums.h>
GLVFKey _glvfKeyCast(int key);
#endif
#endif