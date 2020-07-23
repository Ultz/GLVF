#include <glvf.h>
#include "Platform.h"
#ifdef GLVF_PLATFORM_GLFW
#include "GlfwPlatform.h"
#endif

// Implementation Internals
Platform* currentPlatform;

bool _glvfEnsurePlatformCreated()
{
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

	return currentPlatform->createInstance((Instance**)output);
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
    	case GLVF_EVENT_PUMP_PNAME_EVENT_DRIVEN:
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
	    case GLVF_EVENT_PUMP_PNAME_EVENT_DRIVEN:
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

// Views

GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result)
{
	return ((Instance*)instance)->createView(info, (View**)result);
}

GLVFResult glvfQueryViewState(GLVFView view, GLVFViewState* state)
{
	*state = ((View*)view)->getState();
	return GLVF_OK;
}

GLVFResult glvfBootstrapView(GLVFView view, GLVFMainFunction fn)
{
	return ((View*)view)->bootstrap(fn);
}

void glvfDestroyView(GLVFView view)
{
	((View*)view)->instance->destroyView((View*)view);
}
