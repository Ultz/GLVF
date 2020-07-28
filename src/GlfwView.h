#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#pragma once
#ifndef _GLFWVIEW_H
#define _GLFWVIEW_H
#include <glvf.h>
#include "View.h"
class GlfwView : public View {
private:
	GLFWwindow* window;
public:
	GLVFResult initialize(const GLVFViewCreateInfo* info);
	void destroying() override;
	GLVFViewStatus getState() override;
	GLVFResult bootstrap(GLVFMainFunction fn) override;
	GLVFResult getVisibility(GLVFBool* result) override;
	GLVFResult getPosition(int32_t* result) override;
	GLVFResult getSize(int32_t* result) override;
	GLVFResult getTitle(int8_t** result) override;
	GLVFResult getUI(GLVFUserInterface* result) override;
	GLVFResult getWindowState(GLVFWindowState* result) override;
	GLVFResult getVideoMode(GLVFVideoMode* result) override;
	GLVFResult setVisibility(GLVFBool* value) override;
	GLVFResult setPosition(int32_t* value) override;
	GLVFResult setSize(int32_t* value) override;
	GLVFResult setTitle(int8_t** value) override;
	GLVFResult setUI(GLVFUserInterface* value) override;
	GLVFResult setWindowState(GLVFWindowState* value) override;
	GLVFResult setVideoMode(GLVFVideoMode* value) override;
	GLVFResult makeCurrent() override;
	GLVFResult swapBuffers() override;
	GLVFResult swapInterval(int32_t interval) override;
	GLVFResult getPhysicalDevicePresentationSupport(GLVFVulkanHandle instance,
		GLVFVulkanHandle physicalDevice,
		uint32_t queueFamily,
		GLVFBool* result) override;
	GLVFResult createSurface(GLVFVulkanHandle instance,
		const GLVFVkAllocationCallbacks allocator,
		uint32_t* vkResult,
		GLVFVulkanHandle* output) override;
	GLVFResult getProcAddress(int8_t* name, GLVFVoidFunction* result) override;
	GLVFResult getInputDevices(uint32_t* num, GLVFInputDeviceInfo* result) override;
};
#endif
#endif