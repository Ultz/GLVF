#pragma once
#ifndef _GLFWINSTANCE_H
#define _GLFWINSTANCE_H
#include "Instance.h"

class GlfwInstance : public Instance
{
public:
	GlfwInstance();
	GLVFResult createView(const GLVFViewCreateInfo* input, class View** output);
	void destroyView(class View* view);
	void destroying();
};
#endif