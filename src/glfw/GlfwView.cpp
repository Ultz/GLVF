#include <glvf_core.h>
#ifdef GLVF_PLATFORM_GLFW
#include "Glfw.h"
#include <map>
#include <ctime>
#include "GlfwView.h"
#include "GlfwInstance.h"
GLVFResult GlfwView::initialize(const GLVFViewCreateInfo* info)
{
    int width = 480;
    int height = 360;
    char* title;
    int32_t* pos;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLVFWindowState stateToSet = GLVF_WINDOW_STATE_FULLSCREEN;
    for (size_t i = 0; i < info->numBufferBitPreferences; i++)
    {
        switch (info->pBufferBitPreferences[i].buffer)
        {
        case GLVF_BUFFER_KIND_COLOR:
            switch (info->pBufferBitPreferences[i].preferredBits)
            {
            case GLVF_BITS_DONT_CARE:
                break; // do nothing i guess
            case GLVF_BITS_NONE:
                glfwWindowHint(GLFW_RED_BITS, 0);
                glfwWindowHint(GLFW_BLUE_BITS, 0);
                glfwWindowHint(GLFW_GREEN_BITS, 0);
                glfwWindowHint(GLFW_ALPHA_BITS, 0);
                break;
            case GLVF_BITS_COLOR_R8_G8_B8_A8:
                glfwWindowHint(GLFW_RED_BITS, 8);
                glfwWindowHint(GLFW_BLUE_BITS, 8);
                glfwWindowHint(GLFW_GREEN_BITS, 8);
                glfwWindowHint(GLFW_ALPHA_BITS, 8);
                break;
            case GLVF_BITS_COLOR_R5_G6_B5:
                glfwWindowHint(GLFW_RED_BITS, 5);
                glfwWindowHint(GLFW_BLUE_BITS, 6);
                glfwWindowHint(GLFW_GREEN_BITS, 5);
                glfwWindowHint(GLFW_ALPHA_BITS, 0);
                break;
            case GLVF_BITS_DEPTH_R16:
            case GLVF_BITS_DEPTH_R24:
            case GLVF_BITS_STENCIL_R8:
            default:
                if (instance->errorPump)
                {
                    instance->errorPump->reportError
                    (
                        GLVF_ERROR_BAD_PARAMETER,
                        "Incorrect value for color buffer bits."
                    );
                }
                return GLVF_ERROR_BAD_PARAMETER;
            }
            break;
        case GLVF_BUFFER_KIND_DEPTH:
            switch (info->pBufferBitPreferences[i].preferredBits)
            {
            case GLVF_BITS_DONT_CARE:
                break; // do nothing i guess
            case GLVF_BITS_NONE:
                glfwWindowHint(GLFW_DEPTH_BITS, 0);
            case GLVF_BITS_DEPTH_R16:
                glfwWindowHint(GLFW_DEPTH_BITS, 16);
                break;
            case GLVF_BITS_DEPTH_R24:
                glfwWindowHint(GLFW_DEPTH_BITS, 24);
                break;
            case GLVF_BITS_COLOR_R8_G8_B8_A8:
            case GLVF_BITS_COLOR_R5_G6_B5:
            case GLVF_BITS_STENCIL_R8:
            default:
                if (instance->errorPump)
                {
                    instance->errorPump->reportError
                    (
                        GLVF_ERROR_BAD_PARAMETER,
                        "Incorrect value for depth buffer bits."
                    );
                }
                return GLVF_ERROR_BAD_PARAMETER;
            }
            break;
        case GLVF_BUFFER_KIND_STENCIL:
            switch (info->pBufferBitPreferences[i].preferredBits)
            {
            case GLVF_BITS_DONT_CARE:
                break; // do nothing i guess
            case GLVF_BITS_NONE:
                glfwWindowHint(GLFW_STENCIL_BITS, 0);
                break;
            case GLVF_BITS_STENCIL_R8:
                glfwWindowHint(GLFW_STENCIL_BITS, 8);
                break;
            case GLVF_BITS_DEPTH_R16:
            case GLVF_BITS_DEPTH_R24:
            case GLVF_BITS_COLOR_R8_G8_B8_A8:
            case GLVF_BITS_COLOR_R5_G6_B5:
            default:
                if (instance->errorPump)
                {
                    instance->errorPump->reportError
                    (
                        GLVF_ERROR_BAD_PARAMETER,
                        "Incorrect value for stencil buffer bits."
                    );
                }
                return GLVF_ERROR_BAD_PARAMETER;
            }
            break;
        default:
            if (instance->errorPump)
            {
                instance->errorPump->reportError
                (
                    GLVF_ERROR_BAD_PARAMETER,
                    "Unknown buffer."
                );
            }
            return GLVF_ERROR_BAD_PARAMETER;
        }
    }

    for (size_t i = 0; i < info->numFeatureConfigs; i++)
    {
        const GLVFPropertyFeatureConfig* config = (const GLVFPropertyFeatureConfig*)info->featureConfigs[i];
        switch (info->featureConfigs[i]->kind)
        {
        case GLVF_FEATURE_CONFIG_KIND_PROPERTY:
            switch (config->key)
            {
            case GLVF_VIEW_PNAME_BOOL_VISIBILITY:
                glfwWindowHint(GLFW_VISIBLE, *(GLVFBool*)config->value);
                break;
            case GLVF_VIEW_PNAME_VEC2I_POSITION:
                pos = reinterpret_cast<int32_t*>(config->value);
                break;
            case GLVF_VIEW_PNAME_VEC2I_SIZE:
                width = ((int32_t*)config->value)[0];
                height = ((int32_t*)config->value)[1];
                break;
            case GLVF_VIEW_PNAME_STRING_TITLE:
                title = (char*)config->value;
                break;
            case GLVF_VIEW_PNAME_ENUM_UI:
                switch (*(GLVFUserInterface*)config->value)
                {
                case GLVF_USER_INTERFACE_NONE:
                    glfwWindowHint(GLFW_DECORATED, 0);
                    glfwWindowHint(GLFW_RESIZABLE, 0);
                    break;
                case GLVF_USER_INTERFACE_DESKTOP_RESIZABLE:
                    glfwWindowHint(GLFW_DECORATED, 1);
                    glfwWindowHint(GLFW_RESIZABLE, 1);
                    break;
                case GLVF_USER_INTERFACE_DESKTOP_FIXED:
                    glfwWindowHint(GLFW_DECORATED, 1);
                    glfwWindowHint(GLFW_RESIZABLE, 0);
                    break;
                case GLVF_USER_INTERFACE_MOBILE_NAVIGATION:
                    if (instance->errorPump)
                    {
                        instance->errorPump->reportError
                        (
                            GLVF_WARN_BAD_PARAMETER,
                            "GLVF_USER_INTERFACE_MOBILE_NAVIGATION is not supported with GLFW. Assumed GLVF_USER_INTERFACE_DESKTOP_RESIZABLE."
                        );
                    }
                    glfwWindowHint(GLFW_DECORATED, 1);
                    glfwWindowHint(GLFW_RESIZABLE, 1);
                    break;
                case GLVF_USER_INTERFACE_MOBILE_STATUS_BAR:
                    if (instance->errorPump)
                    {
                        instance->errorPump->reportError
                        (
                            GLVF_WARN_BAD_PARAMETER,
                            "GLVF_USER_INTERFACE_MOBILE_STATUS_BAR is not supported with GLFW. Assumed GLVF_USER_INTERFACE_DESKTOP_FIXED."
                        );
                    }
                    glfwWindowHint(GLFW_DECORATED, 1);
                    glfwWindowHint(GLFW_RESIZABLE, 0);
                    break;
                default:
                    if (instance->errorPump)
                    {
                        instance->errorPump->reportError
                        (
                            GLVF_ERROR_BAD_PARAMETER,
                            "Unknown user interface option."
                        );
                    }
                    return GLVF_ERROR_BAD_PARAMETER;
                }
                break;
            case GLVF_VIEW_PNAME_ENUM_WINDOW_STATE:
                stateToSet = *reinterpret_cast<GLVFWindowState*>(config->value);
                if (stateToSet != GLVF_WINDOW_STATE_FULLSCREEN &&
                    stateToSet != GLVF_WINDOW_STATE_MINIMIZED &&
                    stateToSet != GLVF_WINDOW_STATE_MAXIMIZED &&
                    stateToSet != GLVF_WINDOW_STATE_NORMAL)
                {
                    if (instance->errorPump)
                    {
                        instance->errorPump->reportError
                        (
                            GLVF_ERROR_BAD_PARAMETER,
                            "Unknown window state option."
                        );
                    }
                    return GLVF_ERROR_BAD_PARAMETER;
                }
                break;
            case GLVF_VIEW_PNAME_STRUCT_VIDEO_MODE:
                GLVFVideoMode videoMode = *reinterpret_cast<GLVFVideoMode*>(config->value);
                glfwWindowHint(GLFW_REFRESH_RATE, videoMode.refreshRate);
                break;
            default:
                if (instance->errorPump)
                {
                    instance->errorPump->reportError
                    (
                        GLVF_ERROR_BAD_PARAMETER,
                        "Unknown key for GLVFPropertyFeatureConfig"
                    );
                }
                return GLVF_ERROR_BAD_PARAMETER;
            }
        default:
            if (instance->errorPump)
            {
                instance->errorPump->reportError
                (
                    GLVF_WARN_BAD_PARAMETER,
                    "Contained an unsupported feature config. GLFW only supports GLVF_FEATURE_CONFIG_KIND_PROPERTY. Silently discarding..."
                );
            }
            break;
        }
    }

    fullscreen = true;

    if (stateToSet != GLVF_WINDOW_STATE_FULLSCREEN)
    {
        monitor = nullptr;
        fullscreen = false;
    }

    window = glfwCreateWindow(width, height, title, monitor, nullptr);
    if (!window)
    {
        return mapGlfwErrorCode(glfwGetError(nullptr));
    }

    GLVFResult postResult;
    if (stateToSet != GLVF_WINDOW_STATE_FULLSCREEN)
    {
        postResult = setWindowState(&stateToSet);
        if (postResult != GLVF_OK)
        {
            return postResult;
        }
    }

    if (!pos)
    {
        postResult = setPosition(pos);
        if (postResult != GLVF_OK)
        {
            return postResult;
        }
    }

    for (size_t i = 0; i < joysticks.size(); i++)
    {
        joysticks[i] = GlfwJoystick(i);
    }

    glfwSetWindowUserPointer(window, this);
    cachedTitle = reinterpret_cast<int8_t*>(title);
    return GLVF_OK;
}
void GlfwView::destroying()
{
    View::destroying();
    glfwDestroyWindow(window);
}
GLVFViewStatus GlfwView::getState()
{
    return glfwWindowShouldClose(window) ? GLVF_VIEW_STATE_CLOSE_REQUESTED : GLVF_VIEW_STATE_ACTIVE;
}
GLVFResult GlfwView::bootstrap(GLVFMainLoopFunction fn)
{
    // it's not required on the GLFW platform, but they asked for it so /shrug
    double lastFrameTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double thisFrameTime = glfwGetTime();
        fn(thisFrameTime - lastFrameTime);
        lastFrameTime = thisFrameTime;
    }

    return GLVF_OK;
}
GLVFResult GlfwView::getVisibility(GLVFBool* result)
{
    *result = glfwGetWindowAttrib(window, GLFW_VISIBLE);
    return GLVF_OK;
}
GLVFResult GlfwView::getPosition(int32_t* result)
{
    glfwGetWindowPos(window, result, &result[1]);
    return GLVF_OK;
}
GLVFResult GlfwView::getSize(int32_t* result)
{
    glfwGetWindowSize(window, result, &result[1]);
    return GLVF_OK;
}
GLVFResult GlfwView::getFramebufferSize(int32_t* result)
{
    glfwGetFramebufferSize(window, result, &result[1]);
    return GLVF_OK;
}
GLVFResult GlfwView::getTitle(int8_t** result)
{
    *result = cachedTitle;
    return GLVF_OK;
}
GLVFResult GlfwView::getUI(GLVFUserInterface* result)
{
    int decorated = glfwGetWindowAttrib(window, GLFW_DECORATED);
    int resizable = glfwGetWindowAttrib(window, GLFW_RESIZABLE);
    if (decorated == 0 && resizable == 0)
    {
        *result = GLVF_USER_INTERFACE_NONE;
    }
    else if (decorated == 1 && resizable == 0)
    {
        *result = GLVF_USER_INTERFACE_DESKTOP_FIXED;
    }
    else
    {
        *result = GLVF_USER_INTERFACE_DESKTOP_RESIZABLE;
    }

    return GLVF_OK;
}
GLVFResult GlfwView::getWindowState(GLVFWindowState* result)
{
    if (glfwGetWindowAttrib(window, GLFW_ICONIFIED))
    {
        *result = GLVF_WINDOW_STATE_MINIMIZED;
    }
    else if (glfwGetWindowAttrib(window, GLFW_MAXIMIZED))
    {
        *result = GLVF_WINDOW_STATE_MAXIMIZED;
    }
    else if (glfwGetWindowMonitor(window))
    {
        *result = GLVF_WINDOW_STATE_FULLSCREEN;
    }
    else
    {
        *result = GLVF_WINDOW_STATE_NORMAL;
    }

    return GLVF_OK;
}
GLFWmonitor* getMonitorOfWindowedWindow(GLFWwindow* window)
{
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    int wx, wy, ww, wh;
    glfwGetWindowPos(window, &wx, &wy);
    glfwGetWindowSize(window, &ww, &wh);

    GLFWmonitor* currentCandidate;
    int currentCandidateStrength = 0; // the closer to the top left point the better
    for (size_t i = 0; i < monitorCount; i++)
    {
        GLFWmonitor* monitor = monitors[i];
        int x, y, w, h;
        glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
        if (x <= wx && wx < x + w && y <= wy && wy < y + h) // checks if this monitor contains the top left point
        {
            if (currentCandidateStrength < 3)
            {
                currentCandidate = monitor;
                currentCandidateStrength = 3;
                break;
            }
        }
        else if (x <= (wx + ww) && (wx + ww) < x + w && y <= wy && wy < y + h) // checks if this monitor contains the top right point
        {
            if (currentCandidateStrength < 2)
            {
                currentCandidate = monitor;
                currentCandidateStrength = 2;
            }
        }
        else if (x <= wx && wx < x + w && y <= (wy + wh) && (wy + wh) < y + h) // checks if this monitor contains the btm left point
        {
            if (currentCandidateStrength < 2)
            {
                currentCandidate = monitor;
                currentCandidateStrength = 2;
            }
        }
        else if (x <= (wx + ww) && (wx + ww) < x + w && y <= (wy + wh) && (wy + wh) < y + h)  // checks if this monitor contains the btm right point
        {
            if (currentCandidateStrength < 1)
            {
                currentCandidate = monitor;
                currentCandidateStrength = 1;
            }
        }
    }

    // apparently we couldn't find any monitor that contained this window even a little bit. wat.
    if (currentCandidateStrength == 0)
    {
        currentCandidate = glfwGetPrimaryMonitor();
    }

    return currentCandidate;
}
GLVFResult GlfwView::getVideoMode(GLVFVideoMode* result)
{
    GLFWmonitor* monitor = glfwGetWindowMonitor(window);
    if (!monitor)
    {
        monitor = getMonitorOfWindowedWindow(window);
        if (!monitor)
        {
            return GLVF_ERROR_UNKNOWN;
        }
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    result->refreshRate = mode->refreshRate;
    result->resolution[0] = mode->width;
    result->resolution[1] = mode->height;
    return GLVF_OK;
}
GLVFResult GlfwView::setVisibility(GLVFBool* value)
{
    if (*value)
    {
        glfwShowWindow(window);
    }
    else
    {
        glfwHideWindow(window);
    }

    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::setPosition(int32_t* value)
{
    glfwSetWindowPos(window, value[0], value[1]);
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::setSize(int32_t* value)
{
    glfwSetWindowSize(window, value[0], value[1]);
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::setTitle(int8_t** value)
{
    glfwSetWindowTitle(window, reinterpret_cast<char*>(*value));
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::setUI(GLVFUserInterface* value)
{
    switch (*value)
    {
    case GLVF_USER_INTERFACE_NONE:
        glfwSetWindowAttrib(window, GLFW_DECORATED, 0);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, 0);
        break;
    case GLVF_USER_INTERFACE_DESKTOP_RESIZABLE:
        glfwSetWindowAttrib(window, GLFW_DECORATED, 1);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, 1);
        break;
    case GLVF_USER_INTERFACE_DESKTOP_FIXED:
        glfwSetWindowAttrib(window, GLFW_DECORATED, 1);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, 0);
        break;
    case GLVF_USER_INTERFACE_MOBILE_NAVIGATION:
        if (instance->errorPump)
        {
            instance->errorPump->reportError
            (
                GLVF_WARN_BAD_PARAMETER,
                "GLVF_USER_INTERFACE_MOBILE_NAVIGATION is not supported with GLFW. Assumed GLVF_USER_INTERFACE_DESKTOP_RESIZABLE."
            );
        }
        glfwSetWindowAttrib(window, GLFW_DECORATED, 1);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, 1);
        break;
    case GLVF_USER_INTERFACE_MOBILE_STATUS_BAR:
        if (instance->errorPump)
        {
            instance->errorPump->reportError
            (
                GLVF_WARN_BAD_PARAMETER,
                "GLVF_USER_INTERFACE_MOBILE_STATUS_BAR is not supported with GLFW. Assumed GLVF_USER_INTERFACE_DESKTOP_FIXED."
            );
        }
        glfwSetWindowAttrib(window, GLFW_DECORATED, 1);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, 0);
        break;
    default:
        if (instance->errorPump)
        {
            instance->errorPump->reportError
            (
                GLVF_ERROR_BAD_PARAMETER,
                "Unknown user interface option."
            );
        }
        return GLVF_ERROR_BAD_PARAMETER;
    }
}
GLVFResult GlfwView::setWindowState(GLVFWindowState* value)
{
    if (*value != GLVF_WINDOW_STATE_FULLSCREEN && fullscreen)
    {
        int mx, my, mw, mh;
        glfwGetMonitorWorkarea(glfwGetWindowMonitor(window), &mx, &my, &mw, &mh);
        glfwSetWindowMonitor
        (
            window,
            nullptr,
            mx,
            my,
            mw,
            mh,
            0
        );
        fullscreen = false;
    }

    GLFWmonitor* monitor;
    const GLFWvidmode* mode;
    switch (*value)
    {
    case GLVF_WINDOW_STATE_NORMAL:
        glfwRestoreWindow(window);
        break;
    case GLVF_WINDOW_STATE_MINIMIZED:
        glfwIconifyWindow(window);
        break;
    case GLVF_WINDOW_STATE_MAXIMIZED:
        glfwMaximizeWindow(window);
        break;
    case GLVF_WINDOW_STATE_FULLSCREEN:
        monitor = glfwGetWindowMonitor(window);
        if (!monitor)
        {
            monitor = getMonitorOfWindowedWindow(window);
            if (!monitor)
            {
                return GLVF_ERROR_UNKNOWN;
            }
        }

        mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor
        (
            window,
            monitor,
            0,
            0,
            mode->width,
            mode->height,
            mode->refreshRate
        );
        break;
    default:
        break;
    }
}
GLVFResult GlfwView::setVideoMode(GLVFVideoMode* value)
{
    GLFWmonitor* monitor = glfwGetWindowMonitor(window);
    if (!monitor)
    {
        monitor = getMonitorOfWindowedWindow(window);
        if (!monitor)
        {
            return GLVF_ERROR_UNKNOWN;
        }
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor
    (
        window,
        monitor,
        0,
        0,
        value->resolution[0],
        value->resolution[1],
        value->refreshRate
    );
}
GLVFResult GlfwView::makeCurrent()
{
    glfwMakeContextCurrent(window);
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::swapBuffers()
{
    glfwSwapBuffers(window);
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::swapInterval(int32_t interval)
{
    glfwSwapInterval(interval);
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::getPhysicalDevicePresentationSupport(GLVFVulkanHandle instance, GLVFVulkanHandle physicalDevice, uint32_t queueFamily, GLVFBool* result)
{
    if (!glfwVulkanSupported() || (enabledFeatures & GLVF_FEATURE_VULKAN_SUPPORT) == 0)
    {
        return GLVF_ERROR_FEATURE_NOT_AVAILABLE;
    }
    
    *result = glfwGetPhysicalDevicePresentationSupport(reinterpret_cast<VkInstance>(instance), reinterpret_cast<VkPhysicalDevice>(physicalDevice), queueFamily);
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::createSurface(GLVFVulkanHandle instance, const GLVFVkAllocationCallbacks* allocator, uint32_t* vkResult, GLVFVulkanHandle* output)
{
    if (!glfwVulkanSupported() || (enabledFeatures & GLVF_FEATURE_VULKAN_SUPPORT) == 0)
    {
        return GLVF_ERROR_FEATURE_NOT_AVAILABLE;
    }

    VkResult result = glfwCreateWindowSurface
    (
        reinterpret_cast<VkInstance>(instance),
        window,
        reinterpret_cast<const VkAllocationCallbacks*>(allocator),
        reinterpret_cast<VkSurfaceKHR*>(output)
    );

    if (result != VK_SUCCESS)
    {
        if (this->instance->errorPump)
        {
            this->instance->errorPump->reportError
            (
                GLVF_ERROR_UNDERLYING_API_ERROR,
                "Vulkan surface creation call failed with VkResult " + std::to_string(result)
            );
        }

        return GLVF_ERROR_UNDERLYING_API_ERROR;
    }

    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::getProcAddress(int8_t* name, GLVFVoidFunction* result)
{
    *result = glfwGetProcAddress(reinterpret_cast<char*>(name));
    return mapGlfwErrorCode(glfwGetError(nullptr));
}
GLVFResult GlfwView::getInputDevices(uint32_t* num, GLVFInputDeviceInfo* result)
{
    uint32_t max = GLFW_JOYSTICK_LAST + 1 + 2; // 16 joysticks/gamepads, 1 mouse, 1 keyboard
    if (!result)
    {
        *num = max;
        return GLVF_OK;
    }

    int i;
    for (i = 0; i < joysticks.size() && i < *num; i++)
    {
        GlfwJoystick* joystick = &joysticks[i];
        GLVFInputDeviceInfo info;
        info.isConnected = joystick->joystickKind != GlfwJoystickKind::Disconnected;
        info.numButtons = joystick->buttonStates.size();
        info.numHats = joystick->joystickHats.size();
        info.numScalarAxes = joystick->joystickAxes.size();
        info.numThumbsticks = joystick->gamepadThumbsticks.size();
        info.numTriggers = joystick->gamepadTriggers.size();
        info.subject = joystick->index;
        info.subjectKind = mapSubject(joystick->joystickKind);
        result[i] = info;
    }

    if ((*num - i) >= 1)
    {
        GLVFInputDeviceInfo info;
        info.isConnected = true;
        info.numButtons = GLFW_KEY_LAST + 1;
        info.subject = 0;
        info.subjectKind = GLVF_EVENT_SUBJECT_KEYBOARD;
        i++;
    }

    if ((*num - i) >= 1)
    {
        GLVFInputDeviceInfo info;
        info.isConnected = true;
        info.numButtons = GLFW_MOUSE_BUTTON_LAST + 1;
        info.subject = 0;
        info.subjectKind = GLVF_EVENT_SUBJECT_MOUSE;
        i++;
    }

    *num = i;
    return i < max ? GLVF_INCOMPLETE : GLVF_OK;
}
void GlfwView::preEnumerateEvents()
{
    if (eventPump)
    {
        if (eventPump->waitEvents)
        {
            glfwWaitEvents();
        }
        else
        {
            glfwPollEvents();
        }
    }

    for (size_t i = 0; i < joysticks.size(); i++)
    {
        joysticks[i].update(this);
    }
}
void charCallback(GLFWwindow* window, unsigned int character)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFCharEvent event;
    event.kind = GLVF_EVENT_KIND_KEYBOARD_KEY_CHAR;
    event.receivedCharacter = character;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFKeyEvent event;
    event.kind = action == GLFW_PRESS ? GLVF_EVENT_KIND_KEYBOARD_KEY_DOWN
        : action == GLFW_RELEASE ? GLVF_EVENT_KIND_KEYBOARD_KEY_UP
        : GLVF_EVENT_KIND_KEYBOARD_KEY_REPEAT;
    event.key = _glvfKeyCast(key);
    event.pressed = action == GLFW_PRESS || action == GLFW_REPEAT;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFAxisEvent event;
    event.kind = GLVF_EVENT_KIND_MOUSE_MOVE;
    event.axisIndex = 0;
    event.axisKind = GLVF_AXIS_KIND_MOUSE_POSITION;
    event.subject = 0;
    event.subjectKind = GLVF_EVENT_SUBJECT_MOUSE;
    event.xyState[0] = xpos;
    event.xyState[1] = ypos;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFAxisEvent event;
    event.kind = GLVF_EVENT_KIND_RESIZE;
    event.axisIndex = 0;
    event.axisKind = GLVF_AXIS_KIND_VIEW_FRAMEBUFFER_SIZE;
    event.subject = 0;
    event.subjectKind = GLVF_EVENT_SUBJECT_VIEW;
    event.xyState[0] = width;
    event.xyState[1] = height;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFAxisEvent event;
    event.kind = GLVF_EVENT_KIND_MOUSE_MOVE;
    event.axisIndex = 0;
    event.axisKind = GLVF_AXIS_KIND_MOUSE_SCROLL_OFFSET;
    event.subject = 0;
    event.subjectKind = GLVF_EVENT_SUBJECT_MOUSE;
    event.xyState[0] = xoffset;
    event.xyState[1] = yoffset;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void windowCloseCallback(GLFWwindow* window)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFEvent event;
    event.kind = GLVF_EVENT_KIND_USER_QUIT;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void windowIconifyCallback(GLFWwindow* window, int iconified)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFWindowStateEvent event;
    event.kind = GLVF_EVENT_KIND_STATE_CHANGE;
    event.newState == iconified ? GLVF_WINDOW_STATE_MINIMIZED : GLVF_WINDOW_STATE_NORMAL;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void windowMaximizeCallback(GLFWwindow* window, int maximized)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFWindowStateEvent event;
    event.kind = GLVF_EVENT_KIND_STATE_CHANGE;
    event.newState == maximized ? GLVF_WINDOW_STATE_MAXIMIZED : GLVF_WINDOW_STATE_NORMAL;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void windowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFAxisEvent event;
    event.kind = GLVF_EVENT_KIND_MOVE;
    event.axisIndex = 0;
    event.axisKind = GLVF_AXIS_KIND_VIEW_POSITION;
    event.subject = 0;
    event.subjectKind = GLVF_EVENT_SUBJECT_VIEW;
    event.xyState[0] = xpos;
    event.xyState[1] = ypos;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    GlfwView* view = reinterpret_cast<GlfwView*>(glfwGetWindowUserPointer(window));
    GLVFAxisEvent event;
    event.kind = GLVF_EVENT_KIND_RESIZE;
    event.axisIndex = 0;
    event.axisKind = GLVF_AXIS_KIND_VIEW_SIZE;
    event.subject = 0;
    event.subjectKind = GLVF_EVENT_SUBJECT_VIEW;
    event.xyState[0] = width;
    event.xyState[1] = height;
    event.timestamp = std::time(nullptr);
    view->eventPump->enqueue(*reinterpret_cast<GLVFEvent*>(&event));
}
GLVFResult GlfwView::createEventPump(const GLVFEventPumpCreateInfo* info)
{
    View::createEventPump(info);
    glfwSetCharCallback(window, &charCallback);
    glfwSetKeyCallback(window, &keyCallback);
    glfwSetCursorPosCallback(window, &cursorPosCallback);
    glfwSetFramebufferSizeCallback(window, &framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, &mouseButtonCallback);
    glfwSetScrollCallback(window, &scrollCallback);
    glfwSetWindowCloseCallback(window, &windowCloseCallback);
    glfwSetWindowIconifyCallback(window, &windowIconifyCallback);
    glfwSetWindowMaximizeCallback(window, &windowMaximizeCallback);
    glfwSetWindowPosCallback(window, &windowPosCallback);
    glfwSetWindowSizeCallback(window, &windowSizeCallback);
}
void GlfwView::destroyEventPump()
{
    glfwSetCharCallback(window, nullptr);
    glfwSetKeyCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);
    glfwSetFramebufferSizeCallback(window, nullptr);
    glfwSetMouseButtonCallback(window, nullptr);
    glfwSetScrollCallback(window, nullptr);
    glfwSetWindowCloseCallback(window, nullptr);
    glfwSetWindowIconifyCallback(window, nullptr);
    glfwSetWindowMaximizeCallback(window, nullptr);
    glfwSetWindowPosCallback(window, nullptr);
    glfwSetWindowSizeCallback(window, nullptr);
    View::destroyEventPump();
}
#endif