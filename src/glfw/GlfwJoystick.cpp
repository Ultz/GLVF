#include "GlfwJoystick.h"
#include <ctime>

GlfwJoystickKind queryJoystickKind(uint32_t index)
{
    return glfwJoystickIsGamepad(index) ? GlfwJoystickKind::Gamepad : glfwJoystickPresent(index)
        ? GlfwJoystickKind::Joystick
        : GlfwJoystickKind::Disconnected;
}

GlfwJoystick::GlfwJoystick()
{
}

GlfwJoystick::GlfwJoystick(uint32_t index)
{
    this->index = index;
    gamepadDPad = GlfwPosition2D::Centered;
    gamepadTriggers = std::array<float, _GLVF_GAMEPAD_TRIGGER_COUNT>();
    joystickKind = queryJoystickKind(index);
}

GLVFEventSubject mapSubject(GlfwJoystickKind kind)
{
    switch (kind)
    {
    case GlfwJoystickKind::Gamepad:
        return GLVF_EVENT_SUBJECT_GAMEPAD;
    case GlfwJoystickKind::Disconnected:
    case GlfwJoystickKind::Joystick:
    default:
        return GLVF_EVENT_SUBJECT_JOYSTICK;
    }
}

GlfwPosition2D getPosition2D(unsigned char val)
{
    switch (val)
    {
    case GLFW_HAT_RIGHT:
        return GlfwPosition2D::Right;
    case GLFW_HAT_LEFT:
        return GlfwPosition2D::Left;
    case GLFW_HAT_UP:
        return GlfwPosition2D::Up;
    case GLFW_HAT_LEFT_UP:
        return GlfwPosition2D::UpLeft;
    case GLFW_HAT_RIGHT_UP:
        return GlfwPosition2D::UpRight;
    case GLFW_HAT_DOWN:
        return GlfwPosition2D::Down;
    case GLFW_HAT_LEFT_DOWN:
        return GlfwPosition2D::DownLeft;
    case GLFW_HAT_RIGHT_DOWN:
        return GlfwPosition2D::DownRight;
    case GLFW_HAT_CENTERED:
    default:
        return GlfwPosition2D::Centered;
    }
}

void setAxes(GlfwPosition2D val, float* axes)
{
    switch (val)
    {
    case GlfwPosition2D::Right:
        axes[0] = 1;
        axes[1] = 0;
        break;
    case GlfwPosition2D::Left:
        axes[0] = -1;
        axes[1] = 0;
        break;
    case GlfwPosition2D::Up:
        axes[0] = 0;
        axes[1] = 1;
        break;
    case GlfwPosition2D::UpLeft:
        axes[0] = -1;
        axes[1] = 1;
        break;
    case GlfwPosition2D::UpRight:
        axes[0] = 1;
        axes[1] = 1;
        break;
    case GlfwPosition2D::Down:
        axes[0] = 0;
        axes[1] = -1;
        break;
    case GlfwPosition2D::DownLeft:
        axes[0] = -1;
        axes[1] = -1;
        break;
    case GlfwPosition2D::DownRight:
        axes[0] = 1;
        axes[1] = -1;
        break;
    case GlfwPosition2D::Centered:
    default:
        axes[0] = 0;
        axes[1] = 0;
        break;
    }
}

void reportButtonUpdates(const View* view,
    const unsigned char* newButtons,
    std::map<uint32_t, bool>& buttonStates,
    size_t newButtonsCount,
    GlfwJoystickKind joystickKind,
    int32_t index)
{
    for (size_t i = 0; i < newButtonsCount; i++)
    {
        if (newButtons[i] != buttonStates[i])
        {
            if (view->eventPump)
            {
                GLVFButtonEvent event = {};
                event.button.index = GLVF_BUTTON_NAME_JOYSTICK_A - 1 - i;
                event.kind = joystickKind == GlfwJoystickKind::Gamepad
                    ? (newButtons[i] ? GLVF_EVENT_KIND_GAMEPAD_BUTTON_DOWN : GLVF_EVENT_KIND_GAMEPAD_BUTTON_UP)
                    : (newButtons[i] ? GLVF_EVENT_KIND_JOYSTICK_BUTTON_DOWN : GLVF_EVENT_KIND_JOYSTICK_BUTTON_UP);
                event.subjectKind = mapSubject(joystickKind);
                event.subject = index;
                event.timestamp = std::time(nullptr);
                view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
            }
            buttonStates[i] = newButtons[i];
        }
    }
}

void GlfwJoystick::update(const View* view)
{
    GlfwJoystickKind newJoystickKind = queryJoystickKind(index);
    if (newJoystickKind != joystickKind)
    {
        if (view->eventPump)
        {
            GLVFConnectionEvent event = {};
            if (joystickKind == GlfwJoystickKind::Disconnected)
            {
                event.isConnected = true;
                event.kind = GLVF_EVENT_KIND_DEVICE_CONNECTION_CHANGE;
                event.subject = index;
                event.subjectKind = mapSubject(newJoystickKind);
                event.timestamp = std::time(nullptr);
                view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
            }
            else if (newJoystickKind == GlfwJoystickKind::Disconnected)
            {
                event.isConnected = false;
                event.kind = GLVF_EVENT_KIND_DEVICE_CONNECTION_CHANGE;
                event.subject = index;
                event.subjectKind = mapSubject(joystickKind);
                event.timestamp = std::time(nullptr);
                view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
            }
            else
            {
                event.isConnected = false;
                event.kind = GLVF_EVENT_KIND_DEVICE_CONNECTION_CHANGE;
                event.subject = index;
                event.subjectKind = mapSubject(joystickKind);
                event.timestamp = std::time(nullptr);
                view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
                event.isConnected = true;
                event.subjectKind = mapSubject(newJoystickKind);
                view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
            }
        }

        // Reset state
        buttonStates.clear();
        joystickAxes.clear();
        joystickHats.clear();
        gamepadThumbsticks.fill(std::tuple<float, float>(0, 0));
        gamepadTriggers.fill(0);
        gamepadDPad = GlfwPosition2D::Centered;
        joystickKind = newJoystickKind;
    }

    GLFWgamepadstate state;
    if (joystickKind == GlfwJoystickKind::Gamepad && glfwGetGamepadState(index, &state))
    {
        // loop through buttons
        reportButtonUpdates(view, &state.buttons[0], buttonStates, _GLVF_GAMEPAD_BUTTON_COUNT, joystickKind, index);
        for (size_t i = 0; i < 2; i++) // loop through thumbsticks
        {
            bool thumbstickChanged = false;
            int axes[2];
            for (uint64_t j = 0; j < 2; j++) // loop through x and y
            {
                float axis = j == 0 ? std::get<0>(gamepadThumbsticks[i]) : std::get<1>(gamepadThumbsticks[i]);
                if (state.axes[(i * 2) + j] != axis)
                {
                    thumbstickChanged = true;
                    axes[j] = state.axes[(i * 2) + j];
                }
            }

            if (thumbstickChanged)
            {
                if (view->eventPump)
                {
                    GLVFAxisEvent event = {};
                    event.axisIndex = i;
                    event.axisKind = GLVF_AXIS_KIND_GAMEPAD_THUMBSTICK;
                    event.kind = GLVF_EVENT_KIND_GAMEPAD_THUMBSTICK_MOVE;
                    event.subject = index;
                    event.subjectKind = GLVF_EVENT_SUBJECT_GAMEPAD;
                    event.timestamp = std::time(nullptr);
                    event.xyState[0] = axes[0];
                    event.xyState[1] = axes[1];
                    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
                }
                gamepadThumbsticks[i] = std::tuple<float, float>(axes[0], axes[1]);
            }
        }

        for (size_t i = 0; i < 2; i++) // loop through triggers
        {
            if (gamepadTriggers[i] != state.axes[4 + i])
            {
                if (view->eventPump)
                {
                    GLVFAxisEvent event = {};
                    event.axisIndex = i;
                    event.axisKind = GLVF_AXIS_KIND_GAMEPAD_TRIGGER;
                    event.kind = GLVF_EVENT_KIND_GAMEPAD_TRIGGER_MOVE;
                    event.subject = index;
                    event.subjectKind = GLVF_EVENT_SUBJECT_GAMEPAD;
                    event.timestamp = std::time(nullptr);
                    event.xyState[0] = state.axes[4 + i];
                    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
                }
                gamepadTriggers[i] = state.axes[4 + i];
            }
        }
    }

    if (joystickKind == GlfwJoystickKind::Joystick)
    {
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(index, &count);
        reportButtonUpdates(view, buttons, buttonStates, count, joystickKind, index);
        const float* axes = glfwGetJoystickAxes(index, &count);
        if (joystickAxes.size() < count)
        {
            joystickAxes.resize(count);
        }
        
        for (size_t i = 0; i < count; i++)
        {
            if (joystickAxes[i] != axes[i])
            {
                if (view->eventPump)
                {
                    GLVFAxisEvent event = {};
                    event.axisIndex = i;
                    event.axisKind = GLVF_AXIS_KIND_JOYSTICK;
                    event.kind = GLVF_EVENT_KIND_JOYSTICK_AXIS_MOVE;
                    event.subject = index;
                    event.subjectKind = GLVF_EVENT_SUBJECT_JOYSTICK;
                    event.timestamp = std::time(nullptr);
                    event.xyState[0] = axes[i];
                    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
                }
                joystickAxes[i] = axes[i];
            }
        }

        const unsigned char* hats = glfwGetJoystickHats(index, &count);
        if (joystickHats.size() < count)
        {
            joystickHats.resize(count);
        }

        for (size_t i = 0; i < count; i++)
        {
            GlfwPosition2D pos2D = getPosition2D(hats[i]);
            if (joystickHats[i] != pos2D)
            {
                if (view->eventPump)
                {
                    GLVFAxisEvent event = {};
                    event.axisIndex = i;
                    event.axisKind = GLVF_AXIS_KIND_JOYSTICK_HAT;
                    event.kind = GLVF_EVENT_KIND_JOYSTICK_HAT_MOVE;
                    event.subject = index;
                    event.subjectKind = GLVF_EVENT_SUBJECT_JOYSTICK;
                    event.timestamp = std::time(nullptr);
                    setAxes(pos2D, &event.xyState[0]);
                    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
                }
                joystickHats[i] = pos2D;
            }
        }
    }
}