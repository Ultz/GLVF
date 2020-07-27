#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#include "GlfwPlatform.h"
#include "GlfwInstance.h"
#include <GLFW/glfw3.h>

Instance* instance;

bool GlfwPlatform::allowMultiInstance()
{
    return false;
}

GLVFResult GlfwPlatform::createInstance(Instance** output)
{
    if (instance != nullptr)
    {
        return GLVF_ERROR_DUPLICATE;
    }

    if (!glfwInit())
    {
        return GLVF_ERROR_FAILED_TO_BOOTSTRAP;
    }
    
    *output = instance = new GlfwInstance();
    instance->platform = this;
    return GLVF_OK;
}

void GlfwPlatform::destroyInstance(Instance* input)
{
    if (instance != input)
    {
        // bad handle
        return;
    }

    ((GlfwInstance*)input)->destroying();
    delete input;
    glfwTerminate();
}
#endif