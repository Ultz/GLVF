#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#include "GlfwInstance.h"
#include <GLFW/glfw3.h>

GlfwInstance::GlfwInstance()
{
	isUnderlyingApiBootstrapped = true;
	supportedFeatures = GLVFFeatureFlags(GLVF_FEATURE_CONTROLLABLE_POSITION |
		GLVF_FEATURE_CONTROLLABLE_STATE |
		GLVF_FEATURE_CONTROLLABLE_SIZE |
		GLVF_FEATURE_CONTROLLABLE_UI |
		GLVF_FEATURE_CONTROLLABLE_TITLE |
		GLVF_FEATURE_ENHANCED_DEBUGGING |
		GLVF_FEATURE_EVENT_DRIVEN_PUMP |
		GLVF_FEATURE_FILE_DROP |
		GLVF_FEATURE_GAMEPAD_INPUT |
		GLVF_FEATURE_JOYSTICK_INPUT |
		GLVF_FEATURE_KEYBOARD_INPUT |
		GLVF_FEATURE_MOUSE_INPUT |
		GLVF_FEATURE_MULTIVIEW_SUPPORT |
		GLVF_FEATURE_OPENGL_SUPPORT |
	    (glfwVulkanSupported() ? GLVF_FEATURE_VULKAN_SUPPORT : 0));
}

GLVFResult GlfwInstance::createView(const GLVFViewCreateInfo* input, View** output)
{
	return GLVF_OK;
}

void GlfwInstance::destroyView(View* view)
{
}

void GlfwInstance::destroying()
{
}

GLVFResult GlfwInstance::getViewForCurrentContext(View** output)
{
	*output = (View*)glfwGetWindowUserPointer(glfwGetCurrentContext());
	return GLVF_OK;
}

GLVFResult GlfwInstance::clearCurrentContext()
{
	glfwMakeContextCurrent(NULL);
	return GLVF_OK;
}
#endif