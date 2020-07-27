#pragma once
#ifndef GLVF_ENHANCED_DEBUGGING_H
#define GLVF_ENHANCED_DEBUGGING_H

#include "glvf_core.h"
#include <cstdint>


struct GLVFError {
	// seeing as this is a struct that never flows in, it doesn't have an sType
	GLVFResult errorCode;
	const char* pErrorMessage;
	const char* pFunctionName;
};

typedef struct GLVFErrorPumpHandle* GLVFErrorPump;

GLVFResult glvfCreateErrorPump(GLVFInstance instance, GLVFErrorPump* result);
GLVFResult glvfEnumerateErrors(GLVFErrorPump pump, uint32_t* pCount, GLVFError* pErrors);
void glvfDestroyErrorPump(GLVFErrorPump pump);

#endif