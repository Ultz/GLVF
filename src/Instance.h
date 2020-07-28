#pragma once
#ifndef _INSTANCE_H
#define _INSTANCE_H
#include <glvf.h>
#include "ErrorPump.h"
#include "View.h"
class Instance {
public:
	class Platform* platform;
	class ErrorPump* errorPump;
	GLVFFeatureFlags supportedFeatures;
	bool isUnderlyingApiBootstrapped;
	virtual GLVFResult createErrorPump();
	virtual void destroyErrorPump();
	virtual GLVFResult createView(const GLVFViewCreateInfo* input, class View** output) = 0;
	virtual void destroyView(class View* view) = 0;
	virtual GLVFResult getViewForCurrentContext(class View** output) = 0;
	virtual GLVFResult clearCurrentContext() = 0;
};
#endif