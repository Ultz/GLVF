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

	currentPlatform->destroyInstance(reinterpret_cast<Instance*>(instance));
}

// Debugging

GLVFResult glvfCreateErrorPump(GLVFInstance instance, GLVFErrorPump* result)
{
	GLVFResult ret = reinterpret_cast<Instance*>(instance)->createErrorPump();
	if (ret == GLVF_OK)
	{
		*result = (GLVFErrorPump)reinterpret_cast<Instance*>(instance)->errorPump;
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
	((ErrorPump*)pump)->parentInstance->destroyErrorPump();
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
	EventPump* actualPump = reinterpret_cast<EventPump*>(pump);
    actualPump->view->preEnumerateEvents();
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
	*result = reinterpret_cast<Instance*>(instance)->supportedFeatures;
	return GLVF_OK;
}

GLVFResult glvfQueryEnabledFeatures(GLVFView view, GLVFFeatureFlags* result)
{
	*result = reinterpret_cast<View*>(view)->enabledFeatures;
	return GLVF_OK;
}

// Views

GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result)
{
	return reinterpret_cast<Instance*>(instance)->createView(info, (View**)result);
}

GLVFResult glvfQueryViewStatus(GLVFView view, GLVFViewStatus* state)
{
	*state = reinterpret_cast<View*>(view)->getState();
	return GLVF_OK;
}

GLVFResult glvfBootstrapView(GLVFView view, GLVFMainLoopFunction fn)
{
	return reinterpret_cast<View*>(view)->bootstrap(fn);
}

void glvfDestroyView(GLVFView view)
{
	reinterpret_cast<View*>(view)->instance->destroyView(reinterpret_cast<View*>(view));
}

// View Extras
GLVFResult glvfGetViewProperty(GLVFView view, GLVFViewPName name, void* value)
{
    View* aview = reinterpret_cast<View*>(view);
	switch (name)
	{
	case GLVF_VIEW_PNAME_BOOL_VISIBILITY:
		return aview->getVisibility(reinterpret_cast<GLVFBool*>(value));
	case GLVF_VIEW_PNAME_VEC2I_POSITION:
		return aview->getPosition(reinterpret_cast<int32_t*>(value));
	case GLVF_VIEW_PNAME_VEC2I_SIZE:
		return aview->getSize(reinterpret_cast<int32_t*>(value));
	case GLVF_VIEW_PNAME_STRING_TITLE:
		return aview->getTitle(reinterpret_cast<int8_t**>(value));
	case GLVF_VIEW_PNAME_ENUM_UI:
		return aview->getUI(reinterpret_cast<GLVFUserInterface*>(value));
	case GLVF_VIEW_PNAME_ENUM_WINDOW_STATE:
		return aview->getWindowState(reinterpret_cast<GLVFWindowState*>(value));
	case GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE:
		return aview->getVideoMode(reinterpret_cast<GLVFVideoMode*>(value));
    case GLVF_VIEW_PNAME_VEC2I_FRAMEBUFFER_SIZE:
        return aview->getFramebufferSize(reinterpret_cast<int32_t*>(value));
	default:
		return GLVF_ERROR_BAD_PARAMETER;
	}
}

GLVFResult glvfSetViewProperty(GLVFView view, GLVFViewPName name, void* value)
{
    View* aview = reinterpret_cast<View*>(view);
    switch (name)
    {
    case GLVF_VIEW_PNAME_BOOL_VISIBILITY:
        return aview->setVisibility(reinterpret_cast<GLVFBool*>(value));
    case GLVF_VIEW_PNAME_VEC2I_POSITION:
        return aview->setPosition(reinterpret_cast<int32_t*>(value));
    case GLVF_VIEW_PNAME_VEC2I_SIZE:
        return aview->setSize(reinterpret_cast<int32_t*>(value));
    case GLVF_VIEW_PNAME_STRING_TITLE:
        return aview->setTitle(reinterpret_cast<int8_t**>(value));
    case GLVF_VIEW_PNAME_ENUM_UI:
        return aview->setUI(reinterpret_cast<GLVFUserInterface*>(value));
    case GLVF_VIEW_PNAME_ENUM_WINDOW_STATE:
        return aview->setWindowState(reinterpret_cast<GLVFWindowState*>(value));
    case GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE:
        return aview->setVideoMode(reinterpret_cast<GLVFVideoMode*>(value));
    case GLVF_VIEW_PNAME_VEC2I_FRAMEBUFFER_SIZE:
        return GLVF_ERROR_READ_ONLY;
    default:
        return GLVF_ERROR_BAD_PARAMETER;
    }
}

// OpenGL support

GLVFResult glvfQueryCurrentContext(GLVFInstance instance, GLVFView* result)
{
	return reinterpret_cast<Instance*>(instance)->getViewForCurrentContext((View**)result);
}

GLVFResult glvfMakeContextCurrent(GLVFView view)
{
	return reinterpret_cast<View*>(view)->makeCurrent();
}

GLVFResult glvfClearCurrentContext(GLVFInstance instance)
{
	return reinterpret_cast<Instance*>(instance)->clearCurrentContext();
}

GLVFResult glvfSwapBuffers(GLVFView view)
{
	return reinterpret_cast<View*>(view)->swapBuffers();
}

GLVFResult glvfSwapInterval(GLVFView view, int32_t interval)
{
	return reinterpret_cast<View*>(view)->swapInterval(interval);
}

GLVFResult glvfGetContextProcAddr(GLVFView view, int8_t* pName, GLVFVoidFunction* pResult)
{
	return reinterpret_cast<View*>(view)->getProcAddress(pName, pResult);
}

// Vulkan support

GLVFResult glvfEnumerateRequiredInstanceExtensions(GLVFView view, uint32_t* pCount, int8_t** pExtensions)
{
	size_t i;
	std::vector<std::string> vec = reinterpret_cast<View*>(view)->vulkanExtensions;
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
	return reinterpret_cast<View*>(view)->getPhysicalDevicePresentationSupport(instance, physicalDevice, queueFamily, result);
}

GLVFResult glvfCreateSurface(GLVFView view,
	GLVFVulkanHandle instance,
	const GLVFVkAllocationCallbacks* allocator,
	uint32_t* vkResult,
	GLVFVulkanHandle* output)
{
	return reinterpret_cast<View*>(view)->createSurface(instance, allocator, vkResult, output);
}

// Input

GLVFResult glvfEnumerateInputDevices(GLVFView view, uint32_t* pCount, GLVFInputDeviceInfo* pDevices)
{
	return reinterpret_cast<View*>(view)->getInputDevices(pCount, pDevices);
}