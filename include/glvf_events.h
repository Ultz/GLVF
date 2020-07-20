#include "glvf_core.h"
#include "glvf_view.h"
#include <cstdint>

typedef struct {
	GLVFEventKind kind; // kind is the sType
	uint32_t timestamp;
	int8_t padding[56];
} GLVFEvent;

typedef enum {
	GLVF_EVENT_KIND_EMPTY,
	GLVF_EVENT_KIND_USER_QUIT,
	GLVF_EVENT_KIND_OS_QUIT,
	GLVF_EVENT_KIND_LOW_MEMORY,
	GLVF_EVENT_KIND_STATE_CHANGE,
	GLVF_EVENT_KIND_KEYBOARD_KEY_DOWN,
	GLVF_EVENT_KIND_KEYBOARD_KEY_UP,
	GLVF_EVENT_KIND_KEYBOARD_KEY_CHAR,
	GLVF_EVENT_KIND_KEYBOARD_KEY_CHAR_REPEAT,
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
	GLVF_FORCE_32_BIT = 2147483647
} GLVFEventKind;

// TODO GLVFKeyEvent
// TODO GLVFCharEvent
// TODO GLVFButtonEvent
// TODO GLVFAxisEvent
// TODO GLVFViewStateEvent

GLVF_DEFINE_HANDLE(GLVFEventPump);

GLVFResult glvfCreateEventPump(GLVFInstance instance, GLVFEventPump* result);
GLVFResult glvfEnumerateEvents(GLVFEventPump pump, uint32_t index, uint32_t* pCount, GLVFEvent* pEvents);
GLVFResult glvfClearEvents(GLVFEventPump pump);
GLVFResult glvfDestroyEventPump(GLVFEventPump pump);