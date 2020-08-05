#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#pragma once
#ifndef _GLFWJOYSTICK_H
#define _GLFWJOYSTICK_H
#include "Glfw.h"
#include <cstdint>
#include <tuple>
#include <map>
#include <array>
#include "../Instance.h"

const int32_t _GLVF_JOYSTICK_COUNT = GLFW_JOYSTICK_LAST + 1;
const int32_t _GLVF_GAMEPAD_BUTTON_COUNT = GLFW_GAMEPAD_BUTTON_LAST + 1;
const int32_t _GLVF_GAMEPAD_THUMBSTICK_COUNT = 2;
const int32_t _GLVF_GAMEPAD_TRIGGER_COUNT = 2;

enum class GlfwJoystickKind {
    Disconnected,
    Joystick,
    Gamepad
};

GLVFEventSubject mapSubject(GlfwJoystickKind kind);

enum class GlfwPosition2D {
    Centered = 0,
    Up = 1,
    Down = 2,
    Left = 4,
    Right = 8,
    UpLeft = Up | Left,
    UpRight = Up | Right,
    DownLeft = Down | Left,
    DownRight = Down | Right
};

class GlfwJoystick {
public:
    GlfwJoystick();
    uint32_t index;
    std::map<uint32_t, bool> buttonStates;
    std::vector<float> joystickAxes;
    std::vector<GlfwPosition2D> joystickHats;
    GlfwJoystickKind joystickKind;
    GlfwPosition2D gamepadDPad;
    std::array<std::tuple<float, float>, _GLVF_GAMEPAD_THUMBSTICK_COUNT> gamepadThumbsticks;
    std::array<float, _GLVF_GAMEPAD_TRIGGER_COUNT> gamepadTriggers;
    GlfwJoystick(uint32_t index);
    void update(const View* view);
};
#endif
#endif