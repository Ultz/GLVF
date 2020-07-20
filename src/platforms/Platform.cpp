#include <glvf.h>
#include "Platform.h"
#ifdef GLVF_PLATFORM_GLFW
#include "glfw/GlfwPlatform.h"
#endif
Platform* CurrentPlatform;

void _glvfEnsurePlatformCreated() {
	if (CurrentPlatform != nullptr) {
		return;
	}

#ifdef GLVF_PLATFORM_GLFW
	CurrentPlatform = new GlfwPlatform();
#endif
}

GLVFResult glvfCreateInstance(GLVFInstance* output)
{
	_glvfEnsurePlatformCreated();
}

GLVFBool glvfIsMultiInstanceSupported()
{
	_glvfEnsurePlatformCreated();
	return CurrentPlatform->isMultiInstance() ? GLVF_TRUE : GLVF_FALSE;
}

void glvfDestroyInstance(GLVFInstance instance)
{
	_glvfEnsurePlatformCreated();
}
