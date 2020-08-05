#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#include "GlfwPlatform.h"
#include "GlfwInstance.h"
#include "Glfw.h"

Instance* currentInstance;

bool GlfwPlatform::allowMultiInstance()
{
    return false;
}

GLVFResult GlfwPlatform::createInstance(Instance** output)
{
    if (currentInstance != nullptr)
    {
        return GLVF_ERROR_DUPLICATE;
    }

    if (!glfwInit())
    {
        return GLVF_ERROR_FAILED_TO_BOOTSTRAP;
    }
    
    *output = currentInstance = new GlfwInstance();
    currentInstance->platform = this;
    return GLVF_OK;
}

void GlfwPlatform::destroyInstance(Instance* input)
{
    if (currentInstance != input)
    {
        // bad handle
        return;
    }

    ((GlfwInstance*)input)->destroying();
    delete input;
}
#endif