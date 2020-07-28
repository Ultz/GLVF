#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#include <GLFW/glfw3.h>
#include <map>
#include "GlfwView.h"
GLVFResult GlfwView::initialize(const GLVFViewCreateInfo* info)
{
	int width;
	int height;
	char* title;
	bool uiSpecified;
	for (size_t i = 0; i < info->numFeatureConfigs; i++)
	{
		switch (info->featureConfigs[i]->kind)
		{
		case GLVF_FEATURE_CONFIG_KIND_PROPERTY:
			const GLVFPropertyFeatureConfig* config = (const GLVFPropertyFeatureConfig*)info->featureConfigs[i];
			switch (config->key)
			{
				case GLVF_VIEW_PNAME_BOOL_VISIBILITY:
					glfwWindowHint(GLFW_VISIBLE, *(GLVFBool*)config->value);
					break;
				case GLVF_VIEW_PNAME_VEC2I_POSITION:
					break;
				case GLVF_VIEW_PNAME_VEC2I_SIZE:
					width = ((int32_t*)config->value)[0];
					height = ((int32_t*)config->value)[1];
					break;
				case GLVF_VIEW_PNAME_STRING_TITLE:
					title = (char*)config->value;
					break;
				case GLVF_VIEW_PNAME_ENUM_UI:
					switch (*(GLVFUserInterface*)config->value)
					{
						case GLVF_USER_INTERFACE_NONE:
							glfwWindowHint(GLFW_DECORATED, 0);
							glfwWindowHint(GLFW_RESIZABLE, 0);
							break;
						case GLVF_USER_INTERFACE_DESKTOP_RESIZABLE:
							glfwWindowHint(GLFW_DECORATED, 1);
							glfwWindowHint(GLFW_RESIZABLE, 1);
							break;
						case GLVF_USER_INTERFACE_DESKTOP_FIXED:
							glfwWindowHint(GLFW_DECORATED, 1);
							glfwWindowHint(GLFW_RESIZABLE, 0);
							break;
						case GLVF_USER_INTERFACE_MOBILE_NAVIGATION:
							if (instance->errorPump)
							{
								instance->errorPump->reportError
								(
									GLVF_WARN_BAD_PARAMETER,
									"GLVF_USER_INTERFACE_MOBILE_NAVIGATION is not supported with GLFW. Assumed GLVF_USER_INTERFACE_DESKTOP_RESIZABLE."
								);
							}
							glfwWindowHint(GLFW_DECORATED, 1);
							glfwWindowHint(GLFW_RESIZABLE, 1);
							break;
						case GLVF_USER_INTERFACE_MOBILE_STATUS_BAR:
							if (instance->errorPump)
							{
								instance->errorPump->reportError
								(
									GLVF_WARN_BAD_PARAMETER,
									"GLVF_USER_INTERFACE_MOBILE_STATUS_BAR is not supported with GLFW. Assumed GLVF_USER_INTERFACE_DESKTOP_FIXED."
								);
							}
							glfwWindowHint(GLFW_DECORATED, 1);
							glfwWindowHint(GLFW_RESIZABLE, 0);
							break;
						default:
							if (instance->errorPump)
							{
								instance->errorPump->reportError
								(
									GLVF_ERROR_BAD_PARAMETER,
									"Unknown user interface option."
								);
							}
							return GLVF_ERROR_BAD_PARAMETER;
					}
					uiSpecified = true;
					break;
				case GLVF_VIEW_PNAME_ENUM_WINDOW_STATE:
					break;
				case GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE:
					break;
				default:
					if (instance->errorPump)
					{
						instance->errorPump->reportError
						(
							GLVF_ERROR_BAD_PARAMETER,
							"Unknown key for GLVFPropertyFeatureConfig"
						);
					}
					return GLVF_ERROR_BAD_PARAMETER;
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