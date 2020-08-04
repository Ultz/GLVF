#pragma once
#ifndef GLVF_VIEW_H
#define GLVF_VIEW_H
#include "glvf_core.h"
#include "glvf_features.h"

enum GLVFApiKind {
	GLVF_API_KIND_NONE,
	GLVF_API_KIND_OPENGL,
	GLVF_API_KIND_OPENGLES,
	GLVF_API_KIND_VULKAN,
	GLVF_API_KIND_METAL,
	GLVF_API_KIND_FORCE_32_BIT = 2147483647
};

enum GLVFViewPName {
	GLVF_VIEW_PNAME_BOOL_VISIBILITY,
	GLVF_VIEW_PNAME_VEC2I_POSITION,
	GLVF_VIEW_PNAME_VEC2I_SIZE,
    GLVF_VIEW_PNAME_VEC2I_FRAMEBUFFER_SIZE,
	GLVF_VIEW_PNAME_STRING_TITLE,
	GLVF_VIEW_PNAME_ENUM_UI, // GLVFUserInterface
	GLVF_VIEW_PNAME_ENUM_WINDOW_STATE, // GLVFWindowState
	GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE, // GLVFVideoMode
	// GLVF_VIEW_PNAME_HANDLE_SCREEN,
	GLVF_VIEW_PNAME_FORCE_32_BIT = 2147483647
};

struct GLVFRenderingApi {
	// no sType as it flows out
	GLVFApiKind kind;
	int8_t version[2];
};

enum GLVFBufferKind {
    GLVF_BUFFER_KIND_COLOR,
	GLVF_BUFFER_KIND_DEPTH,
	GLVF_BUFFER_KIND_STENCIL,
	GLVF_BUFFER_KIND_FORCE_32_BIT = 2147483647
};

enum GLVFBits {
	GLVF_BITS_DONT_CARE,
	GLVF_BITS_NONE,
	GLVF_BITS_COLOR_R8_G8_B8_A8,
	GLVF_BITS_COLOR_R5_G6_B5,
	GLVF_BITS_DEPTH_R16,
	GLVF_BITS_DEPTH_R24,
	GLVF_BITS_STENCIL_R8,
	GLVF_BITS_FORCE_32_BIT = 2147483647
};

struct GLVFBufferBits {
	GLVFBufferKind buffer;
	GLVFBits preferredBits;
};

enum GLVFFeatureConfigKind {
	GLVF_FEATURE_CONFIG_KIND_PROPERTY,
	GLVF_FEATURE_CONFIG_KIND_FORCE_32_BIT = 2147483647
};

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

enum GLVFViewStatus {
	GLVF_VIEW_STATE_ACTIVE,
	GLVF_VIEW_STATE_PAUSED,
	GLVF_VIEW_STATE_CLOSE_REQUESTED,
	GLVF_VIEW_STATE_FORCE_32_BIT = 2147483647
};

struct GLVFVideoMode {
	int32_t refreshRate;
	int32_t resolution[2];
};

enum GLVFUserInterface {
	GLVF_USER_INTERFACE_NONE,
	GLVF_USER_INTERFACE_MOBILE_NAVIGATION,
	GLVF_USER_INTERFACE_MOBILE_STATUS_BAR,
	GLVF_USER_INTERFACE_DESKTOP_RESIZABLE,
	GLVF_USER_INTERFACE_DESKTOP_FIXED,
	GLVF_USER_INTERFACE_FORCE_32_BIT = 2147483647
};

enum GLVFWindowState {
	GLVF_WINDOW_STATE_NORMAL,
	GLVF_WINDOW_STATE_MINIMIZED,
	GLVF_WINDOW_STATE_MAXIMIZED,
	GLVF_WINDOW_STATE_FULLSCREEN,
	GLVF_WINDOW_STATE_FORCE_32_BIT = 2147483647
};

typedef void (*GLVFMainLoopFunction)(double deltaTime);

GLVFResult glvfGetViewProperty(GLVFView view, GLVFViewPName name, void* value);
GLVFResult glvfSetViewProperty(GLVFView view, GLVFViewPName name, void* value);
GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result);
GLVFResult glvfQueryViewStatus(GLVFView view, GLVFViewStatus* state);
GLVFResult glvfBootstrapView(GLVFView view, GLVFMainLoopFunction fn);
void glvfDestroyView(GLVFView view);
#endif