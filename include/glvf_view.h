#pragma once
#ifndef GLVF_VIEW_H
#define GLVF_VIEW_H
#include "glvf_core.h"
#include "glvf_features.h"

typedef enum {
	GLVF_API_KIND_NONE,
	GLVF_API_KIND_OPENGL,
	GLVF_API_KIND_OPENGLES,
	GLVF_API_KIND_VULKAN,
	GLVF_API_KIND_METAL,
	GLVF_API_KIND_FORCE_32_BIT = 2147483647
} GLVFApiKind;

typedef struct {
	// no sType as it flows out
	GLVFApiKind kind;
	int8_t version[2];
} GLVFRenderingApi;

typedef enum {
	GLVF_BUFFER_KIND_DEPTH,
	GLVF_BUFFER_KIND_STENCIL,
	GLVF_BUFFER_KIND_FORCE_32_BIT = 2147483647
} GLVFBufferKind;

typedef enum {
	GLVF_DONT_CARE,
	GLVF_NONE,
	GLVF_COLOR_R8_G8_B8_A8,
	GLVF_COLOR_R5_G6_B5,
	GLVF_DEPTH_R16,
	GLVF_DEPTH_R24,
	GLVF_STENCIL_R8,
	GLVF_BITS_FORCE_32_BIT = 2147483647
} GLVFBits;

typedef struct {
	GLVFBufferKind buffer;
	GLVFBits preferredBits;
} GLVFBufferBits;

typedef enum {
	GLVF_FEATURE_CONFIG_KIND_FORCE_32_BIT = 2147483647
} GLVFFeatureConfigKind;

typedef struct {
	GLVFFeatureConfigKind kind;
} GLVFEmptyFeatureConfig;

typedef struct {
	GLVFRenderingApi api;
	int32_t numBufferBitPreferences;
	const GLVFBufferBits* pBufferBitPreferences;
	GLVFFeatureFlags enabledFeatures;
	int32_t numFeatureConfigs;
	const GLVFEmptyFeatureConfig** featureConfigs;
} GLVFViewCreateInfo;

typedef enum {
	GLVF_VIEW_STATE_ACTIVE,
	GLVF_VIEW_STATE_PAUSED,
	GLVF_VIEW_STATE_CLOSE_REQUESTED,
	GLVF_VIEW_STATE_FORCE_32_BIT = 2147483647
} GLVFViewState;

GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result);
GLVFResult glvfQueryViewState(GLVFView view, GLVFViewState* state);
GLVFResult glvfBootstrapView(GLVFView view, GLVFMainFunction fn);
void glvfDestroyView(GLVFView view);

#endif