#pragma once
#ifndef GLVF_INPUT_ENUMS_H
#define GLVF_INPUT_ENUMS_H
typedef enum GLVFKey {
    GLVF_KEY_UNKNOWN = 0,
    GLVF_KEY_SHIFT_LEFT,
    GLVF_KEY_LSHIFT = GLVF_KEY_SHIFT_LEFT,
    GLVF_KEY_SHIFT_RIGHT,
    GLVF_KEY_RSHIFT = GLVF_KEY_SHIFT_RIGHT,
    GLVF_KEY_CONTROL_LEFT,
    GLVF_KEY_L_CONTROL = GLVF_KEY_CONTROL_LEFT,
    GLVF_KEY_CONTROL_RIGHT,
    GLVF_KEY_R_CONTROL = GLVF_KEY_CONTROL_RIGHT,
    GLVF_KEY_ALT_LEFT,
    GLVF_KEY_L_ALT = GLVF_KEY_ALT_LEFT,
    GLVF_KEY_ALT_RIGHT,
    GLVF_KEY_R_ALT = GLVF_KEY_ALT_RIGHT,
    GLVF_KEY_WIN_LEFT,
    GLVF_KEY_L_WIN = GLVF_KEY_WIN_LEFT,
    GLVF_KEY_WIN_RIGHT,
    GLVF_KEY_R_WIN = GLVF_KEY_WIN_RIGHT,
    GLVF_KEY_MENU,
    GLVF_KEY_F1,
    GLVF_KEY_F2,
    GLVF_KEY_F3,
    GLVF_KEY_F4,
    GLVF_KEY_F5,
    GLVF_KEY_F6,
    GLVF_KEY_F7,
    GLVF_KEY_F8,
    GLVF_KEY_F9,
    GLVF_KEY_F10,
    GLVF_KEY_F11,
    GLVF_KEY_F12,
    GLVF_KEY_F13,
    GLVF_KEY_F14,
    GLVF_KEY_F15,
    GLVF_KEY_F16,
    GLVF_KEY_F17,
    GLVF_KEY_F18,
    GLVF_KEY_F19,
    GLVF_KEY_F20,
    GLVF_KEY_F21,
    GLVF_KEY_F22,
    GLVF_KEY_F23,
    GLVF_KEY_F24,
    GLVF_KEY_F25,
    GLVF_KEY_F26,
    GLVF_KEY_F27,
    GLVF_KEY_F28,
    GLVF_KEY_F29,
    GLVF_KEY_F30,
    GLVF_KEY_F31,
    GLVF_KEY_F32,
    GLVF_KEY_F33,
    GLVF_KEY_F34,
    GLVF_KEY_F35,
    GLVF_KEY_UP,
    GLVF_KEY_DOWN,
    GLVF_KEY_LEFT,
    GLVF_KEY_RIGHT,
    GLVF_KEY_ENTER,
    GLVF_KEY_ESCAPE,
    GLVF_KEY_SPACE,
    GLVF_KEY_TAB,
    GLVF_KEY_BACKSPACE,
    GLVF_KEY_BACK = GLVF_KEY_BACKSPACE,
    GLVF_KEY_INSERT,
    GLVF_KEY_DELETE,
    GLVF_KEY_PAGE_UP,
    GLVF_KEY_PAGE_DOWN,
    GLVF_KEY_HOME,
    GLVF_KEY_END,
    GLVF_KEY_CAPS_LOCK,
    GLVF_KEY_SCROLL_LOCK,
    GLVF_KEY_PRINT_SCREEN,
    GLVF_KEY_PAUSE,
    GLVF_KEY_NUM_LOCK,
    GLVF_KEY_CLEAR,
    GLVF_KEY_SLEEP,
    GLVF_KEY_KEYPAD0,
    GLVF_KEY_KEYPAD1,
    GLVF_KEY_KEYPAD2,
    GLVF_KEY_KEYPAD3,
    GLVF_KEY_KEYPAD4,
    GLVF_KEY_KEYPAD5,
    GLVF_KEY_KEYPAD6,
    GLVF_KEY_KEYPAD7,
    GLVF_KEY_KEYPAD8,
    GLVF_KEY_KEYPAD9,
    GLVF_KEY_KEYPAD_DIVIDE,
    GLVF_KEY_KEYPAD_MULTIPLY,
    GLVF_KEY_KEYPAD_SUBTRACT,
    GLVF_KEY_KEYPAD_MINUS = GLVF_KEY_KEYPAD_SUBTRACT,
    GLVF_KEY_KEYPAD_ADD,
    GLVF_KEY_KEYPAD_PLUS = GLVF_KEY_KEYPAD_ADD,
    GLVF_KEY_KEYPAD_DECIMAL,
    GLVF_KEY_KEYPAD_PERIOD = GLVF_KEY_KEYPAD_DECIMAL,
    GLVF_KEY_KEYPAD_ENTER,
    GLVF_KEY_A,
    GLVF_KEY_B,
    GLVF_KEY_C,
    GLVF_KEY_D,
    GLVF_KEY_E,
    GLVF_KEY_F,
    GLVF_KEY_G,
    GLVF_KEY_H,
    GLVF_KEY_I,
    GLVF_KEY_J,
    GLVF_KEY_K,
    GLVF_KEY_L,
    GLVF_KEY_M,
    GLVF_KEY_N,
    GLVF_KEY_O,
    GLVF_KEY_P,
    GLVF_KEY_Q,
    GLVF_KEY_R,
    GLVF_KEY_S,
    GLVF_KEY_T,
    GLVF_KEY_U,
    GLVF_KEY_V,
    GLVF_KEY_W,
    GLVF_KEY_X,
    GLVF_KEY_Y,
    GLVF_KEY_Z,
    GLVF_KEY_NUMBER0,
    GLVF_KEY_NUMBER1,
    GLVF_KEY_NUMBER2,
    GLVF_KEY_NUMBER3,
    GLVF_KEY_NUMBER4,
    GLVF_KEY_NUMBER5,
    GLVF_KEY_NUMBER6,
    GLVF_KEY_NUMBER7,
    GLVF_KEY_NUMBER8,
    GLVF_KEY_NUMBER9,
    GLVF_KEY_TILDE,
    GLVF_KEY_GRAVE = GLVF_KEY_TILDE,
    GLVF_KEY_MINUS,
    GLVF_KEY_PLUS,
    GLVF_KEY_BRACKET_LEFT,
    GLVF_KEY_L_BRACKET = GLVF_KEY_BRACKET_LEFT,
    GLVF_KEY_BRACKET_RIGHT,
    GLVF_KEY_R_BRACKET = GLVF_KEY_BRACKET_RIGHT,
    GLVF_KEY_SEMICOLON,
    GLVF_KEY_QUOTE,
    GLVF_KEY_COMMA,
    GLVF_KEY_PERIOD,
    GLVF_KEY_SLASH,
    GLVF_KEY_BACKSLASH,
    GLVF_KEY_NON_US_BACKSLASH,
    GLVF_KEY_FORCE_32_BIT = 2147483647
};

typedef enum {
    GLVF_BUTTON_NAME_MOUSE_LEFT,
    GLVF_BUTTON_NAME_MOUSE_MIDDLE,
    GLVF_BUTTON_NAME_MOUSE_RIGHT,
    GLVF_BUTTON_NAME_MOUSE_BUTTON4,
    GLVF_BUTTON_NAME_MOUSE_BUTTON5,
    GLVF_BUTTON_NAME_MOUSE_BUTTON6,
    GLVF_BUTTON_NAME_MOUSE_BUTTON7,
    GLVF_BUTTON_NAME_MOUSE_BUTTON8,
    GLVF_BUTTON_NAME_MOUSE_BUTTON9,
    GLVF_BUTTON_NAME_MOUSE_BUTTON10,
    GLVF_BUTTON_NAME_MOUSE_BUTTON11,
    GLVF_BUTTON_NAME_MOUSE_BUTTON12,
    GLVF_BUTTON_NAME_JOYSTICK_A,
    GLVF_BUTTON_NAME_JOYSTICK_B,
    GLVF_BUTTON_NAME_JOYSTICK_X,
    GLVF_BUTTON_NAME_JOYSTICK_Y,
    GLVF_BUTTON_NAME_JOYSTICK_BACK,
    GLVF_BUTTON_NAME_JOYSTICK_HOME,
    GLVF_BUTTON_NAME_JOYSTICK_DPAD_UP,
    GLVF_BUTTON_NAME_JOYSTICK_DPAD_DOWN,
    GLVF_BUTTON_NAME_JOYSTICK_DPAD_LEFT,
    GLVF_BUTTON_NAME_JOYSTICK_DPAD_RIGHT,
    GLVF_BUTTON_NAME_JOYSTICK_LEFT_BUMPER,
    GLVF_BUTTON_NAME_JOYSTICK_LEFT_STICK,
    GLVF_BUTTON_NAME_JOYSTICK_RIGHT_BUMPER,
    GLVF_BUTTON_NAME_JOYSTICK_RIGHT_STICK,
    GLVF_BUTTON_NAME_JOYSTICK_START,
    GLVF_BUTTON_NAME_FORCE_32_BIT = 2147483647
} GLVFButtonName;
#endif