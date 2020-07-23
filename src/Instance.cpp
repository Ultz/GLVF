#include "Instance.h"

GLVFResult Instance::createErrorPump()
{
	if (errorPump != nullptr)
	{
		return GLVF_ERROR_DUPLICATE;
	}

	errorPump = new ErrorPump();
	errorPump->instance = this;
	return GLVF_OK;
}

void Instance::destroyErrorPump()
{
	delete errorPump;
	errorPump = nullptr;
}
