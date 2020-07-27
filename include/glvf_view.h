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

typedef enum {
	GLVF_VIEW_PNAME_BOOL_VISIBILITY,
	GLVF_VIEW_PNAME_VEC2I_POSITION,
	GLVF_VIEW_PNAME_VEC2I_SIZE,
	GLVF_VIEW_PNAME_STRING_TITLE,
	GLVF_VIEW_PNAME_ENUM_UI, // GLVFUserInterface
	GLVF_VIEW_PNAME_ENUM_WINDOW_STATE, // GLVFWindowState
	GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE, // GLVFVideoMode
	// GLVF_VIEW_PNAME_HANDLE_SCREEN,
	GLVF_VIEW_PNAME_FORCE_32_BIT = 2147483647
} GLVFViewPName;

struct GLVFRenderingApi {
	// no sType as it flows out
	GLVFApiKind kind;
	int8_t version[2];
};

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

struct GLVFBufferBits {
	GLVFBufferKind buffer;
	GLVFBits preferredBits;
};

typedef enum {
	GLVF_FEATURE_CONFIG_KIND_PROPERTY,
	GLVF_FEATURE_CONFIG_KIND_FORCE_32_BIT = 2147483647
} GLVFFeatureConfigKind;

struct GLVFPropertyFeatureConfig {
	GLVFFeatureConfigKind kind;
	GLVFViewPName key;
	void* value;
};

struct GLVFEmptyFeatureConfig {
	GLVFFeatureConfigKind kind;
};

struct GLVFViewCreateInfo {
	GLVFRenderingApi api;
	int32_t numBufferBitPreferences;
	const GLVFBufferBits* pBufferBitPreferences;
	GLVFFeatureFlags enabledFeatures;
	int32_t numFeatureConfigs;
	const GLVFEmptyFeatureConfig** featureConfigs;
};

typedef enum {
	GLVF_VIEW_STATE_ACTIVE,
	GLVF_VIEW_STATE_PAUSED,
	GLVF_VIEW_STATE_CLOSE_REQUESTED,
	GLVF_VIEW_STATE_FORCE_32_BIT = 2147483647
} GLVFViewStatus;

struct GLVFVideoMode {
	int32_t refreshRate;
	int32_t resolution[2];
};

typedef enum {
	GLVF_USER_INTERFACE_NONE,
	GLVF_USER_INTERFACE_MOBILE_NAVIGATION,
	GLVF_USER_INTERFACE_MOBILE_STATUS_BAR,
	GLVF_USER_INTERFACE_DESKTOP_RESIZABLE,
	GLVF_USER_INTERFACE_DESKTOP_FIXED,
	GLVF_USER_INTERFACE_FORCE_32_BIT = 2147483647
} GLVFUserInterface;

typedef enum {
	GLVF_WINDOW_STATE_NORMAL,
	GLVF_WINDOW_STATE_MINIMIZED,
	GLVF_WINDOW_STATE_MAXIMIZED,
	GLVF_WINDOW_STATE_FULLSCREEN,
	GLVF_WINDOW_STATE_FORCE_32_BIT = 2147483647
} GLVFWindowState;

GLVFResult glvfGetViewProperty(GLVFView view, GLVFViewPName name, void* value);
GLVFResult glvfSetViewProperty(GLVFView view, GLVFViewPName name, void* value);
GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result);
GLVFResult glvfQueryViewStatus(GLVFView view, GLVFViewStatus* state);
GLVFResult glvfBootstrapView(GLVFView view, GLVFMainFunction fn);
void glvfDestroyView(GLVFView view);
#endif