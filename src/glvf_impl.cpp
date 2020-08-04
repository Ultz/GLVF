#include <glvf.h>
#include "Platform.h"
#ifdef GLVF_PLATFORM_GLFW
#include "glfw/GlfwPlatform.h"
#endif

// Implementation Internals
Platform* currentPlatform;

bool _glvfEnsurePlatformCreated()
{
    if (CHAR_BIT * sizeof(float) != 32)
    {
        return false;
    }

	if (currentPlatform != nullptr)
	{
		return true;
	}

#ifdef GLVF_PLATFORM_GLFW
	currentPlatform = new GlfwPlatform();
	return true;
#endif

	return false;
}

// Core

GLVFResult glvfCreateInstance(GLVFInstance* output)
{
	if (!_glvfEnsurePlatformCreated())
	{
		return GLVF_ERROR_NO_PLATFORM;
	}

	return currentPlatform->createInstance(reinterpret_cast<Instance**>(output));
}

GLVFBool glvfIsMultiInstanceSupported()
{
	if (!_glvfEnsurePlatformCreated())
	{
		return false;
	}

	return currentPlatform->allowMultiInstance();
}

void glvfDestroyInstance(GLVFInstance instance)
{
	if (!_glvfEnsurePlatformCreated())
	{
		return;
	}

	currentPlatform->destroyInstance((Instance*)instance);
}

// Debugging

GLVFResult glvfCreateErrorPump(GLVFInstance instance, GLVFErrorPump* result)
{
	GLVFResult ret = ((Instance*)instance)->createErrorPump();
	if (ret == GLVF_OK)
	{
		*result = (GLVFErrorPump)((Instance*)instance)->errorPump;
	}

	return ret;
}

GLVFResult glvfEnumerateErrors(GLVFErrorPump pump, uint32_t* pCount, GLVFError* pErrors)
{
	ErrorPump* actualPump = (ErrorPump*)pump;
	if (pErrors == nullptr)
	{
		*pCount = actualPump->getCount();
		return GLVF_OK;
	}

	*pCount = actualPump->get(*pCount, pErrors);
	if (actualPump->getCount() != 0)
	{
		return GLVF_INCOMPLETE;
	}

	return GLVF_OK;
}

void glvfDestroyErrorPump(GLVFErrorPump pump)
{
	((ErrorPump*)pump)->instance->destroyErrorPump();
}

// Events

GLVFResult glvfCreateEventPump(GLVFView view, const GLVFEventPumpCreateInfo* info, GLVFEventPump* result)
{
	View* actualView = (View*)view;
	GLVFResult ret = actualView->createEventPump(info);
	if (ret == GLVF_OK)
	{
		*result = (GLVFEventPump)actualView->eventPump;
	}

	return ret;
}

GLVFResult glvfGetEventPumpProperty(GLVFEventPump pump, GLVFEventPumpPName name, void* value)
{
	EventPump* actualEventPump = (EventPump*)pump;
	switch (name)
	{
	case GLVF_EVENT_PUMP_PNAME_BOOL_EVENT_DRIVEN:
		*((GLVFBool*)value) = actualEventPump->waitEvents;
		return GLVF_OK;
	default:
		return GLVF_ERROR_BAD_PARAMETER;
	}
}

GLVFResult glvfSetEventPumpProperty(GLVFEventPump pump, GLVFEventPumpPName name, void* value)
{
	EventPump* actualEventPump = (EventPump*)pump;
	switch (name)
	{
	case GLVF_EVENT_PUMP_PNAME_BOOL_EVENT_DRIVEN:
		actualEventPump->waitEvents = *((GLVFBool*)value);
		return GLVF_OK;
	default:
		return GLVF_ERROR_BAD_PARAMETER;
	}
}

GLVFResult glvfEnumerateEvents(GLVFEventPump pump, uint32_t* pCount, GLVFEvent* pEvents)
{
	EventPump* actualPump = (EventPump*)pump;
	if (pEvents == nullptr)
	{
		*pCount = actualPump->getCount();
		return GLVF_OK;
	}

	*pCount = actualPump->get(*pCount, pEvents);
	if (actualPump->getCount() != 0)
	{
		return GLVF_INCOMPLETE;
	}

	return GLVF_OK;
}

void glvfDestroyEventPump(GLVFEventPump pump)
{
	((EventPump*)pump)->view->destroyEventPump();
}

// Features

GLVFResult glvfQueryInstanceFeatureSupport(GLVFInstance instance, GLVFFeatureFlags* result)
{
	*result = ((Instance*)instance)->supportedFeatures;
	return GLVF_OK;
}

GLVFResult glvfQueryEnabledFeatures(GLVFView view, GLVFFeatureFlags* result)
{
	*result = ((View*)view)->enabledFeatures;
	return GLVF_OK;
}

// Views

GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result)
{
	return ((Instance*)instance)->createView(info, (View**)result);
}

GLVFResult glvfQueryViewStatus(GLVFView view, GLVFViewStatus* state)
{
	*state = ((View*)view)->getState();
	return GLVF_OK;
}

GLVFResult glvfBootstrapView(GLVFView view, GLVFMainLoopFunction fn)
{
	return ((View*)view)->bootstrap(fn);
}

void glvfDestroyView(GLVFView view)
{
	((View*)view)->instance->destroyView((View*)view);
}

// View Extras
GLVFResult glvfGetViewProperty(GLVFView view, GLVFViewPName name, void* value)
{
	switch (name)
	{
	case GLVF_VIEW_PNAME_BOOL_VISIBILITY:
		return ((View*)view)->getVisibility((GLVFBool*)value);
	case GLVF_VIEW_PNAME_VEC2I_POSITION:
		return ((View*)view)->getPosition((int32_t*)value);
	case GLVF_VIEW_PNAME_VEC2I_SIZE:
		return ((View*)view)->getSize((int32_t*)value);
	case GLVF_VIEW_PNAME_STRING_TITLE:
		return ((View*)view)->getTitle((int8_t**)value);
	case GLVF_VIEW_PNAME_ENUM_UI:
		return ((View*)view)->getUI((GLVFUserInterface*)value);
	case GLVF_VIEW_PNAME_ENUM_WINDOW_STATE:
		return ((View*)view)->getWindowState((GLVFWindowState*)value);
	case GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE:
		return ((View*)view)->getVideoMode((GLVFVideoMode*)value);
	default:
		return GLVF_ERROR_BAD_PARAMETER;
	}
}

GLVFResult glvfSetViewProperty(GLVFView view, GLVFViewPName name, void* value)
{
	switch (name)
	{
	case GLVF_VIEW_PNAME_BOOL_VISIBILITY:
		return ((View*)view)->setVisibility((GLVFBool*)value);
	case GLVF_VIEW_PNAME_VEC2I_POSITION:
		return ((View*)view)->setPosition((int32_t*)value);
	case GLVF_VIEW_PNAME_VEC2I_SIZE:
		return ((View*)view)->setSize((int32_t*)value);
	case GLVF_VIEW_PNAME_STRING_TITLE:
		return ((View*)view)->setTitle((int8_t**)value);
	case GLVF_VIEW_PNAME_ENUM_UI:
		return ((View*)view)->setUI((GLVFUserInterface*)value);
	case GLVF_VIEW_PNAME_ENUM_WINDOW_STATE:
		return ((View*)view)->setWindowState((GLVFWindowState*)value);
	case GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE:
		return ((View*)view)->setVideoMode((GLVFVideoMode*)value);
	default:
		return GLVF_ERROR_BAD_PARAMETER;
	}
}

// OpenGL support

GLVFResult glvfQueryCurrentContext(GLVFInstance instance, GLVFView* result)
{
	return ((Instance*)instance)->getViewForCurrentContext((View**)result);
}

GLVFResult glvfMakeContextCurrent(GLVFView view)
{
	return ((View*)view)->makeCurrent();
}

GLVFResult glvfClearCurrentContext(GLVFInstance instance)
{
	return ((Instance*)instance)->clearCurrentContext();
}

GLVFResult glvfSwapBuffers(GLVFView view)
{
	return ((View*)view)->swapBuffers();
}

GLVFResult glvfSwapInterval(GLVFView view, int32_t interval)
{
	return ((View*)view)->swapInterval(interval);
}

GLVFResult glvfGetContextProcAddr(GLVFView view, int8_t* pName, GLVFVoidFunction* pResult)
{
	return ((View*)view)->getProcAddress(pName, pResult);
}

// Vulkan support

GLVFResult glvfEnumerateRequiredInstanceExtensions(GLVFView view, uint32_t* pCount, int8_t** pExtensions)
{
	size_t i;
	std::vector<std::string> vec = ((View*)view)->vulkanExtensions;
	if (pExtensions == nullptr)
	{
		*pCount = vec.size();
		return GLVF_OK;
	}

	for (i = 0; i < *pCount && i < vec.size(); i++)
	{
		pExtensions[i] = (int8_t*)&vec[i][0];
	}

	if (vec.size() > *pCount)
	{
		return GLVF_INCOMPLETE;
	}

	*pCount = i;
	return GLVF_OK;
}

GLVFResult glvfGetPhysicalDevicePresentationSupport(GLVFView view,
	GLVFVulkanHandle instance,
	GLVFVulkanHandle physicalDevice,
	uint32_t queueFamily,
	GLVFBool* result)
{
	return ((View*)view)->getPhysicalDevicePresentationSupport(instance, physicalDevice, queueFamily, result);
}

GLVFResult glvfCreateSurface(GLVFView view,
	GLVFVulkanHandle instance,
	const GLVFVkAllocationCallbacks* allocator,
	uint32_t* vkResult,
	GLVFVulkanHandle* output)
{
	return ((View*)view)->createSurface(instance, allocator, vkResult, output);
}

// Input

GLVFResult glvfEnumerateInputDevices(GLVFView view, uint32_t* pCount, GLVFInputDeviceInfo* pDevices)
{
	return ((View*)view)->getInputDevices(pCount, pDevices);
}