#pragma once
#ifndef GLVF_VULKAN_H
#define GLVF_VULKAN_H
#include "glvf_view.h"
typedef void* GLVFVulkanHandle;
typedef void GLVFVkAllocationCallbacks;
GLVFResult glvfEnumerateRequiredInstanceExtensions(GLVFView view, uint32_t* pCount, int8_t** pExtensions);
GLVFResult glvfGetPhysicalDevicePresentationSupport(GLVFView view,
	GLVFVulkanHandle instance,
	GLVFVulkanHandle physicalDevice,
	uint32_t queueFamily,
	GLVFBool* output);
GLVFResult glvfCreateSurface(GLVFView view,
	GLVFVulkanHandle instance,
	const GLVFVkAllocationCallbacks* allocator,
	uint32_t* vkResult,
	GLVFVulkanHandle* output);
#endif