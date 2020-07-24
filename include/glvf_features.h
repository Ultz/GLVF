#pragma once
#ifndef GLVF_FEATURES_H
#define GLVF_FEATURES_H
#include "glvf_core.h"

typedef enum {
	GLVF_FEATURE_OPENGL_SUPPORT = 1, // Allows use of OpenGL in conjunction with GLVF.
	GLVF_FEATURE_VULKAN_SUPPORT = 2, // Allows use of Vulkan in conjunction with GLVF.
	GLVF_FEATURE_METAL_SUPPORT = 4, // Allows use of Metal in conjunction with GLVF.
	GLVF_FEATURE_MULTIVIEW_SUPPORT = 8, // Allows the creation of multiple views, instead of just one (i.e. desktop windowing)
	GLVF_FEATURE_MULTISCREEN_SUPPORT = 16,
	GLVF_FEATURE_CONTROLLABLE_SIZE = 32, // Allows the user to change the size of the view. This being disabled doesn't stop the OS from resizing the view.
	GLVF_FEATURE_CONTROLLABLE_POSITION = 64,// Allows the user to change the position of the view. This being disabled doesn't stop the OS from moving it.
	GLVF_FEATURE_CONTROLLABLE_STATE = 128, // Allows the user to control the view state. This being disabled doesn't stop the OS from changing it.
	GLVF_FEATURE_CONTROLLABLE_TITLE = 256,
	GLVF_FEATURE_CONTROLLABLE_UI = 512,
	GLVF_FEATURE_FILE_DROP = 1024, // Allows the user to drag and drop files onto the view. If disabled, file drop events won't be reported.
	GLVF_FEATURE_KEYBOARD_INPUT = 2048, // Enables the receipt of keyboard input.
	GLVF_FEATURE_MOUSE_INPUT = 4096, // Enables the receipt of mouse input.
	GLVF_FEATURE_JOYSTICK_INPUT = 8192, // Enables the receipt of joystick input.
	GLVF_FEATURE_GAMEPAD_INPUT = 16384, // Enables the receipt of gamepad input.
	GLVF_FEATURE_EVENT_DRIVEN_PUMP = 32768,
	GLVF_FEATURE_ENHANCED_DEBUGGING = 65536, // Allows the creation and usage of GLVF error pumps.
	GLVF_FEATURE_FORCE_32_BIT = 2147483647,
} GLVFFeatureFlags;

GLVFResult glvfQueryInstanceFeatureSupport(GLVFInstance instance, GLVFFeatureFlags* result);
#endif