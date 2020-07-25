#pragma once
#ifndef GLVF_OPENGL_H
#define GLVF_OPENGL_H
#include "glvf_view.h"
GLVFResult glvfQueryCurrentContext(GLVFInstance instance, GLVFView* result);
GLVFResult glvfMakeContextCurrent(GLVFView view);
GLVFResult glvfClearCurrentContext(GLVFInstance instance);
GLVFResult glvfSwapBuffers(GLVFView view);
GLVFResult glvfSwapInterval(GLVFView view, int32_t interval);
GLVFResult glvfGetContextProcAddr(GLVFView view, int8_t* pName, GLVFVoidFunction* pResult);
#endif