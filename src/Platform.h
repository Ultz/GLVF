#pragma once
#ifndef _PLATFORM_H
#define _PLATFORM_H
#include "Instance.h"

class Platform {
public:
	virtual bool allowMultiInstance() = 0;
	virtual GLVFResult createInstance(Instance** output) = 0;
	virtual void destroyInstance(Instance* input) = 0;
};
#endif