#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#pragma once
#ifndef _GLFWINSTANCE_H
#define _GLFWINSTANCE_H
#include "../Instance.h"

Instance* instance;
GLVFResult mapGlfwErrorCode(int errorCode);

class GlfwInstance : public Instance
{
public:
	GlfwInstance();
	GLVFResult createErrorPump() override;
	void destroyErrorPump() override;
	GLVFResult createView(const GLVFViewCreateInfo* input, class View** output) override;
	void destroyView(class View* view) override;
	void destroying();
	virtual GLVFResult getViewForCurrentContext(View** output) override;
	virtual GLVFResult clearCurrentContext() override;
};
#endif
#endif