#include "GlfwPlatform.h"

bool GlfwPlatform::allowMultiInstance()
{
    return false;
}

GLVFResult GlfwPlatform::createInstance(Instance** output)
{
    return GLVFResult();
}

void GlfwPlatform::destroyInstance(Instance* input)
{
    delete input;
}
