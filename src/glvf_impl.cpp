#include <glvf.h>
#include "..\include\glvf_events.h"

// Core

GLVFResult glvfCreateInstance(GLVFInstance* output)
{
	return GLVFResult();
}

GLVFBool glvfIsMultiInstanceSupported()
{
	return GLVFBool();
}

void glvfDestroyInstance(GLVFInstance instance)
{
}

// Debugging

GLVFResult glvfCreateErrorPump(GLVFInstance instance, GLVFErrorPump* result)
{
	return GLVFResult();
}

GLVFResult glvfEnumerateErrors(GLVFErrorPump pump, uint32_t index, uint32_t* pCount, GLVFError* pErrors)
{
	return GLVFResult();
}

GLVFResult glvfClearErrors(GLVFErrorPump pump)
{
	return GLVFResult();
}

GLVFResult glvfDestroyErrorPump(GLVFErrorPump pump)
{
	return GLVFResult();
}

// Events

GLVFResult glvfCreateEventPump(GLVFInstance instance, GLVFEventPump* result)
{
	return GLVFResult();
}

GLVFResult glvfEnumerateEvents(GLVFEventPump pump, uint32_t index, uint32_t* pCount, GLVFEvent* pEvents)
{
	return GLVFResult();
}

GLVFResult glvfClearEvents(GLVFEventPump pump)
{
	return GLVFResult();
}

GLVFResult glvfDestroyEventPump(GLVFEventPump pump)
{
	return GLVFResult();
}

// Features

GLVFResult glvfQueryInstanceFeatureSupport(GLVFInstance instance, GLVFFeatureFlags* result)
{
	return GLVFResult();
}

// Rendering APIs

GLVFResult glvfEnumerateInstanceRenderingApis(GLVFInstance instance, uint32_t index, uint32_t* pCount, GLVFRenderingApi* pApis)
{
	return GLVFResult();
}

// Views

GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result)
{
	return GLVFResult();
}

GLVFBool glvfIsViewActive(GLVFView view)
{
	return GLVFBool();
}

GLVFResult glvfBootstrapView(GLVFView view, GLVFMainFunction fn)
{
	return GLVFResult();
}

GLVFResult glvfDestroyView(GLVFView view)
{
	return GLVFResult();
}
