#pragma once
#ifndef _GLFWINSTANCE_H
#define _GLFWINSTANCE_H
#include "Instance.h"

class GlfwInstance : public Instance
{
public:
	GlfwInstance();
	GLVFResult createView(const GLVFViewCreateInfo* input, class View** output) override;
	void destroyView(class View* view) override;
	void destroying();
	virtual GLVFResult getViewForCurrentContext(View** output) override;
	virtual GLVFResult clearCurrentContext() override;
};
#endif