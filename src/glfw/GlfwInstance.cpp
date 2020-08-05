#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#include "GlfwInstance.h"
#include "Glfw.h"
#include "GlfwView.h"

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
    errorPump = nullptr;
}

void errorCallback(int error_code, const char* description)
{
    if (currentInstance->errorPump)
    {
        currentInstance->errorPump->reportError(mapGlfwErrorCode(error_code), std::to_string(error_code) + ": " + std::string(description));
    }
}

GLVFResult GlfwInstance::createErrorPump()
{
	GLVFResult result = Instance::createErrorPump();
    if (result == GLVF_OK)
    {
        glfwSetErrorCallback(&errorCallback);
    }

    return result;
}

void GlfwInstance::destroyErrorPump()
{
	Instance::destroyErrorPump();
	glfwSetErrorCallback(NULL);
}

GLVFResult mapGlfwErrorCode(int errorCode)
{
	switch (errorCode)
	{
	case GLFW_NO_ERROR:
		return GLVF_OK;
	case GLFW_NOT_INITIALIZED:
		return GLVF_ERROR_INSTANCE_INVALID;
	case GLFW_NO_CURRENT_CONTEXT:
		return GLVF_ERROR_NO_CURRENT_CONTEXT;
	case GLFW_INVALID_ENUM:
	case GLFW_INVALID_VALUE:
		return GLVF_ERROR_BAD_PARAMETER;
	case GLFW_API_UNAVAILABLE:
	case GLFW_NO_WINDOW_CONTEXT:
		return GLVF_ERROR_FEATURE_NOT_AVAILABLE;
	case GLFW_VERSION_UNAVAILABLE:
		return GLVF_ERROR_VERSION_NOT_SUPPORTED;
	case GLFW_FORMAT_UNAVAILABLE:
		return GLVF_ERROR_UNSUPPORTED_FORMAT;
	case GLFW_PLATFORM_ERROR:
	default:
		return GLVF_ERROR_UNDERLYING_API_ERROR;
	}
}

GLVFResult GlfwInstance::createView(const GLVFViewCreateInfo* input, View** output)
{
	GlfwView* view = new GlfwView();
    view->instance = this;
	GLVFResult ret = view->initialize(input);
	if (ret != GLVF_OK)
	{
		delete view;
		return ret;
	}

	*output = view;
	return ret;
}

void GlfwInstance::destroyView(View* view)
{
	view->destroying();
	delete view;
}

void GlfwInstance::destroying()
{
	glfwTerminate();
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