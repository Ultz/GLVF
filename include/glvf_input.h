#pragma once
#ifndef GLVF_INPUT_H
#define GLVF_INPUT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "glvf_events.h"
#include "glvf_input_enums.h"
struct GLVFInputDeviceInfo {
	GLVFEventSubject subjectKind;
	uint32_t subject;
	GLVFBool isConnected;
	uint32_t numThumbsticks;
	uint32_t numTriggers;
	uint32_t numScalarAxes;
	uint32_t numButtons;
    uint32_t numHats;
};

GLVFResult glvfEnumerateInputDevices(GLVFView view, uint32_t* pCount, GLVFInputDeviceInfo* pDevices);
#ifdef __cplusplus
}
#endif
#endif