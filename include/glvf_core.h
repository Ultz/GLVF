#pragma once
#ifndef GLVF_CORE_H
#define GLVF_CORE_H
#define GLVF_DEFINE_HANDLE(object) typedef struct object##Handle* object;
#ifdef __cplusplus
extern "C" {
#endif
#include <cstdint>

// One of these will be defined:
// GLVF_PLATFORM_IOS - iOS
// GLVF_PLATFORM_ANDROID - Android
// GLVF_PLATFORM_GLFW - Desktop (GLVF emulation over GLFW)

#if defined(__ANDROID__)
#define GLVF_PLATFORM_ANDROID
//#elif defined(__EMSCRIPTEN__)
//#define GLVF_PLATFORM_EMSCRIPTEN // FUTURE TODO: Emscripten?
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IOS
#define GLVF_PLATFORM_IOS
//#elif TARGET_OS_TV
//#define GLVF_PLATFORM_TVOS // FUTURE TODO: tvOS?
#else
#define GLVF_PLATFORM_GLFW // probably MacOS
#endif
#else
#define GLVF_PLATFORM_GLFW // probably desktop
#endif

typedef enum {
	GLVF_OK, // Operation was successful
	GLVF_INCOMPLETE, // Used by enumerate functions, indicates that the operation was successful but there are still more items to be enumerated.
	GLVF_NEEDS_BOOSTRAP, // Used by CreateView, indicates that the operation was successful but GLVF needs control of the main function.
	GLVF_ERROR_INVALID_PLATFORM, // The operation can't be completed on this platform.
	GLVF_ERROR_FEATURE_NOT_AVAILABLE, // Attempted to access or enable an unavailable feature
	GLVF_ERROR_DUPLICATE, // Attempted to create duplicate object. For example, attempting to create another event pump for a view (there can only be one).
	GLVF_ERROR_NO_PLATFORM,
	GLVF_ERROR_BAD_PARAMETER,
	GLVF_ERROR_FAILED_TO_BOOTSTRAP,
	GLVF_RESULT_FORCE_32_BIT = 2147483647
} GLVFResult;

GLVF_DEFINE_HANDLE(GLVFInstance);
GLVF_DEFINE_HANDLE(GLVFView);

typedef void (*GLVFMainFunction)(GLVFInstance instance, GLVFView view);
typedef void (*GLVFVoidFunction)(void);
typedef int8_t GLVFBool;

const GLVFBool GLVF_TRUE = 1;
const GLVFBool GLVF_FALSE = 0;

GLVFResult glvfCreateInstance(GLVFInstance* output);
GLVFBool glvfIsMultiInstanceSupported();
void glvfDestroyInstance(GLVFInstance instance);
#ifdef __cplusplus
}
#endif
#endif