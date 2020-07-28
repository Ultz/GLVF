#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#include <GLFW/glfw3.h>
#include <map>
#include "GlfwView.h"
GLVFResult GlfwView::initialize(const GLVFViewCreateInfo* info)
{
	for (size_t i = 0; i < info->numFeatureConfigs; i++)
	{
		switch (info->featureConfigs[i]->kind)
		{
		case GLVF_FEATURE_CONFIG_KIND_PROPERTY:
			const GLVFPropertyFeatureConfig* config = (const GLVFPropertyFeatureConfig*)info->featureConfigs[i];
			switch (config->key)
			{

			}
		default:
			if (instance->errorPump)
			{
				instance->errorPump->reportError
				(
					GLVF_ERROR_BAD_PARAMETER,
					"Contained an unsupported feature config. GLFW only supports GLVF_FEATURE_CONFIG_KIND_PROPERTY"
				);
			}
			return GLVF_ERROR_BAD_PARAMETER;
		}
	}
}
void GlfwView::destroying()
{
	View::destroying();
}
GLVFViewStatus GlfwView::getState()
{
	return glfwWindowShouldClose(window) ? GLVF_VIEW_STATE_CLOSE_REQUESTED : GLVF_VIEW_STATE_ACTIVE;
}
GLVFResult GlfwView::bootstrap(GLVFMainFunction fn)
{
	return GLVFResult();
}
GLVFResult GlfwView::getVisibility(GLVFBool* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::getPosition(int32_t* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::getSize(int32_t* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::getTitle(int8_t** result)
{
	return GLVFResult();
}
GLVFResult GlfwView::getUI(GLVFUserInterface* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::getWindowState(GLVFWindowState* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::getVideoMode(GLVFVideoMode* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::setVisibility(GLVFBool* value)
{
	return GLVFResult();
}
GLVFResult GlfwView::setPosition(int32_t* value)
{
	return GLVFResult();
}
GLVFResult GlfwView::setSize(int32_t* value)
{
	return GLVFResult();
}
GLVFResult GlfwView::setTitle(int8_t** value)
{
	return GLVFResult();
}
GLVFResult GlfwView::setUI(GLVFUserInterface* value)
{
	return GLVFResult();
}
GLVFResult GlfwView::setWindowState(GLVFWindowState* value)
{
	return GLVFResult();
}
GLVFResult GlfwView::setVideoMode(GLVFVideoMode* value)
{
	return GLVFResult();
}
GLVFResult GlfwView::makeCurrent()
{
	return GLVFResult();
}
GLVFResult GlfwView::swapBuffers()
{
	return GLVFResult();
}
GLVFResult GlfwView::swapInterval(int32_t interval)
{
	return GLVFResult();
}
GLVFResult GlfwView::getPhysicalDevicePresentationSupport(GLVFVulkanHandle instance, GLVFVulkanHandle physicalDevice, uint32_t queueFamily, GLVFBool* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::createSurface(GLVFVulkanHandle instance, const GLVFVkAllocationCallbacks allocator, uint32_t* vkResult, GLVFVulkanHandle* output)
{
	return GLVFResult();
}
GLVFResult GlfwView::getProcAddress(int8_t* name, GLVFVoidFunction* result)
{
	return GLVFResult();
}
GLVFResult GlfwView::getInputDevices(uint32_t* num, GLVFInputDeviceInfo* result)
{
	return GLVFResult();
}
#endif