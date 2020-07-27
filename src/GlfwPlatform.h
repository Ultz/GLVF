#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#pragma once
#ifndef _GLFWPLATFORM_H
#define _GLFWPLATFORM_H
#include <glvf.h>
#include "Platform.h"

class GlfwPlatform : public Platform {
public:
	bool allowMultiInstance() override;
	GLVFResult createInstance(Instance** output) override;
	virtual void destroyInstance(Instance* input) override;
};
#endif
#endif