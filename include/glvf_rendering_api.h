#pragma once
#ifndef GLVF_RENDERING_API_H
#define GLVF_RENDERING_API_H
#include "glvf_core.h"
#include <cstdint>

typedef enum {
	GLVF_API_KIND_NONE,
	GLVF_API_KIND_OPENGL,
	GLVF_API_KIND_OPENGLES,
	GLVF_API_KIND_VULKAN,
	GLVF_API_KIND_METAL,
	GLVF_FORCE_32_BIT = 2147483647
} GLVFApiKind;

typedef struct {
	// no sType as it flows out
	GLVFApiKind kind;
	int8_t version[2];
} GLVFRenderingApi;

GLVFResult glvfEnumerateInstanceRenderingApis(GLVFInstance instance, uint32_t index, uint32_t* pCount, GLVFRenderingApi* pApis);
#endif