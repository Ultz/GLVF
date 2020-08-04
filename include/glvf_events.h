#pragma once
#ifndef GLVF_EVENTS_H
#define GLVF_EVENTS_H

#include "glvf_core.h"
#include "glvf_input_enums.h"
#include "glvf_view.h"
#include <cstdint>

enum GLVFEventPumpPName {
	GLVF_EVENT_PUMP_PNAME_BOOL_EVENT_DRIVEN,
	GLVF_EVENT_PUMP_PNAME_FORCE_32_BIT = 2147483647
};

struct GLVFEventPumpCreateInfo {
	GLVFBool isEventDriven;
};

enum GLVFEventKind {
	GLVF_EVENT_KIND_EMPTY,
	GLVF_EVENT_KIND_USER_QUIT,
	GLVF_EVENT_KIND_OS_QUIT,
	GLVF_EVENT_KIND_LOW_MEMORY,
	GLVF_EVENT_KIND_STATE_CHANGE,
    GLVF_EVENT_KIND_RESIZE,
    GLVF_EVENT_KIND_MOVE,
	GLVF_EVENT_KIND_KEYBOARD_KEY_DOWN,
	GLVF_EVENT_KIND_KEYBOARD_KEY_UP,
    GLVF_EVENT_KIND_KEYBOARD_KEY_REPEAT,
	GLVF_EVENT_KIND_KEYBOARD_KEY_CHAR,
	GLVF_EVENT_KIND_MOUSE_BUTTON_DOWN,
	GLVF_EVENT_KIND_MOUSE_BUTTON_UP,
	GLVF_EVENT_KIND_MOUSE_MOVE,
	GLVF_EVENT_KIND_MOUSE_SCROLL,
	GLVF_EVENT_KIND_JOYSTICK_BUTTON_DOWN,
	GLVF_EVENT_KIND_JOYSTICK_BUTTON_UP,
	GLVF_EVENT_KIND_JOYSTICK_AXIS_MOVE,
	GLVF_EVENT_KIND_JOYSTICK_HAT_MOVE,
	GLVF_EVENT_KIND_GAMEPAD_BUTTON_DOWN,
	GLVF_EVENT_KIND_GAMEPAD_BUTTON_UP,
	GLVF_EVENT_KIND_GAMEPAD_THUMBSTICK_MOVE,
	GLVF_EVENT_KIND_GAMEPAD_TRIGGER_MOVE,
	GLVF_EVENT_KIND_DEVICE_CONNECTION_CHANGE,
	GLVF_EVENT_KIND_FORCE_32_BIT = 2147483647
};

enum GLVFEventSubject {
	GLVF_EVENT_SUBJECT_VIEW,
	GLVF_EVENT_SUBJECT_KEYBOARD,
	GLVF_EVENT_SUBJECT_MOUSE,
	GLVF_EVENT_SUBJECT_JOYSTICK,
	GLVF_EVENT_SUBJECT_GAMEPAD,
	GLVF_EVENT_SUBJECT_FORCE_32_BIT = 2147483647
};

struct GLVFEvent {
	GLVFEventKind kind; // kind is the sType
	uint64_t timestamp;
	int8_t padding1[32];
	intptr_t padding2[3];
};

struct GLVFFileDropEvent {
	GLVFEventKind kind;
	uint64_t timestamp;
	uint32_t numFiles;
	int8_t padding1[28];
	const int8_t** files;
	intptr_t padding2[2];
};

struct GLVFKeyEvent {
	GLVFEventKind kind;
	uint64_t timestamp;
	GLVFKey key;
	GLVFBool pressed;
	int8_t padding1[27];
	intptr_t padding2[3];
};

struct GLVFCharEvent {
	GLVFEventKind kind;
	uint64_t timestamp;
	uint32_t receivedCharacter;
	int8_t padding1[28];
	intptr_t padding2[3];
};

struct GLVFButtonEvent {
	GLVFEventKind kind;
	uint64_t timestamp;
	uint32_t subject;
	GLVFEventSubject subjectKind;
    union {
        uint32_t index;
        GLVFButtonName name;
    } button;
	int8_t padding1[20];
	intptr_t padding2[3];
};

struct GLVFConnectionEvent {
	GLVFEventKind kind;
	uint64_t timestamp;
	uint32_t subject;
	GLVFEventSubject subjectKind;
	GLVFBool isConnected;
	int8_t padding1[23];
	intptr_t padding2[3];
};

struct GLVFAxisEvent {
	GLVFEventKind kind;
	uint64_t timestamp;
	uint32_t subject;
	GLVFEventSubject subjectKind;
	GLVFAxisKind axisKind;
	uint32_t axisIndex;
	float xyState[2];
	int8_t padding1[8];
	intptr_t padding2[3];
};

struct GLVFWindowStateEvent {
	GLVFEventKind kind;
	uint64_t timestamp;
	GLVFWindowState newState;
	int8_t padding1[28];
	intptr_t padding2[3];
};

typedef struct GLVFEventPumpHandle* GLVFEventPump;

GLVFResult glvfCreateEventPump(GLVFView view, const GLVFEventPumpCreateInfo* info, GLVFEventPump* result);
GLVFResult glvfGetEventPumpProperty(GLVFEventPump pump, GLVFEventPumpPName name, void* value);
GLVFResult glvfSetEventPumpProperty(GLVFEventPump pump, GLVFEventPumpPName name, void* value);
GLVFResult glvfEnumerateEvents(GLVFEventPump pump, uint32_t* pCount, GLVFEvent* pEvents);
void glvfDestroyEventPump(GLVFEventPump pump);
#endif