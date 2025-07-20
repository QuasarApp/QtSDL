//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "qsdlevent.h"
#include <SDL3/SDL_events.h>
namespace QtSDL {

QSDLEvent::QSDLEvent(SDL_Event event, SDL_EventType type):
    QEvent(static_cast<QEvent::Type>(SDLType)) {
    _data = event;
    _sdlType = type;
}

void QSDLEvent::setAccepted(bool accepted) {
    QEvent::setAccepted(accepted);
}

QEvent *QSDLEvent::clone() const {
    return new QSDLEvent(data(), sdlType());
}

const SDL_Event& QSDLEvent::data() const {
    return _data;
}

void QSDLEvent::setData(const SDL_Event &newData) {
    _data = newData;
}

SDL_EventType QSDLEvent::sdlType() const
{
    return _sdlType;
}

QString QSDLEvent::sdlEventTypeName() const {
    switch (_sdlType) {
    // English comment: Application events
    case SDL_EVENT_QUIT: return "SDL_EVENT_QUIT";
    case SDL_EVENT_TERMINATING: return "SDL_EVENT_APP_TERMINATING";
    case SDL_EVENT_LOW_MEMORY: return "SDL_EVENT_APP_LOWMEMORY";
    case SDL_EVENT_WILL_ENTER_BACKGROUND: return "SDL_EVENT_APP_WILLENTERBACKGROUND";
    case SDL_EVENT_DID_ENTER_BACKGROUND: return "SDL_EVENT_APP_DIDENTERBACKGROUND";
    case SDL_EVENT_WILL_ENTER_FOREGROUND: return "SDL_EVENT_APP_WILLENTERFOREGROUND";
    case SDL_EVENT_DID_ENTER_FOREGROUND: return "SDL_EVENT_APP_DIDENTERFOREGROUND";

    // English comment: Display events
    case SDL_EVENT_DISPLAY_ORIENTATION: return "SDL_EVENT_DISPLAY_ORIENTATION";
    case SDL_EVENT_DISPLAY_ADDED: return "SDL_EVENT_DISPLAY_ADDED";
    case SDL_EVENT_DISPLAY_REMOVED: return "SDL_EVENT_DISPLAY_REMOVED";
    case SDL_EVENT_DISPLAY_MOVED: return "SDL_EVENT_DISPLAY_MOVED";
    case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED: return "SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED";

    // English comment: Window events
    case SDL_EVENT_WINDOW_SHOWN: return "SDL_EVENT_WINDOW_SHOWN";
    case SDL_EVENT_WINDOW_HIDDEN: return "SDL_EVENT_WINDOW_HIDDEN";
    case SDL_EVENT_WINDOW_EXPOSED: return "SDL_EVENT_WINDOW_EXPOSED";
    case SDL_EVENT_WINDOW_MOVED: return "SDL_EVENT_WINDOW_MOVED";
    case SDL_EVENT_WINDOW_RESIZED: return "SDL_EVENT_WINDOW_RESIZED";
    case SDL_EVENT_WINDOW_MINIMIZED: return "SDL_EVENT_WINDOW_MINIMIZED";
    case SDL_EVENT_WINDOW_MAXIMIZED: return "SDL_EVENT_WINDOW_MAXIMIZED";
    case SDL_EVENT_WINDOW_RESTORED: return "SDL_EVENT_WINDOW_RESTORED";
    case SDL_EVENT_WINDOW_LAST: return "SDL_EVENT_WINDOW_LEAVE";
    case SDL_EVENT_WINDOW_FOCUS_GAINED: return "SDL_EVENT_WINDOW_FOCUS_GAINED";
    case SDL_EVENT_WINDOW_FOCUS_LOST: return "SDL_EVENT_WINDOW_FOCUS_LOST";
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED: return "SDL_EVENT_WINDOW_CLOSE_REQUESTED";
    case SDL_EVENT_WINDOW_HIT_TEST: return "SDL_EVENT_WINDOW_HIT_TEST";
    case SDL_EVENT_WINDOW_ICCPROF_CHANGED: return "SDL_EVENT_WINDOW_ICCPROF_CHANGED";
    case SDL_EVENT_WINDOW_DISPLAY_CHANGED: return "SDL_EVENT_WINDOW_DISPLAY_CHANGED";

    // English comment: Keyboard events
    case SDL_EVENT_KEY_DOWN: return "SDL_EVENT_KEY_DOWN";
    case SDL_EVENT_KEY_UP: return "SDL_EVENT_KEY_UP";
    case SDL_EVENT_TEXT_EDITING: return "SDL_EVENT_TEXT_EDITING";
    case SDL_EVENT_TEXT_INPUT: return "SDL_EVENT_TEXT_INPUT";
    case SDL_EVENT_KEYMAP_CHANGED: return "SDL_EVENT_KEYMAP_CHANGED";

    // English comment: Mouse events
    case SDL_EVENT_MOUSE_MOTION: return "SDL_EVENT_MOUSE_MOTION";
    case SDL_EVENT_MOUSE_BUTTON_DOWN: return "SDL_EVENT_MOUSE_BUTTON_DOWN";
    case SDL_EVENT_MOUSE_BUTTON_UP: return "SDL_EVENT_MOUSE_BUTTON_UP";
    case SDL_EVENT_MOUSE_WHEEL: return "SDL_EVENT_MOUSE_WHEEL";
    case SDL_EVENT_MOUSE_ADDED: return "SDL_EVENT_MOUSE_CAP_SET";

    // English comment: Joystick events
    case SDL_EVENT_JOYSTICK_AXIS_MOTION: return "SDL_EVENT_JOYSTICK_AXIS_MOTION";
    case SDL_EVENT_JOYSTICK_BALL_MOTION: return "SDL_EVENT_JOYSTICK_BALL_MOTION";
    case SDL_EVENT_JOYSTICK_HAT_MOTION: return "SDL_EVENT_JOYSTICK_HAT_MOTION";
    case SDL_EVENT_JOYSTICK_BUTTON_DOWN: return "SDL_EVENT_JOYSTICK_BUTTON_DOWN";
    case SDL_EVENT_JOYSTICK_BUTTON_UP: return "SDL_EVENT_JOYSTICK_BUTTON_UP";
    case SDL_EVENT_JOYSTICK_ADDED: return "SDL_EVENT_JOYSTICK_ADDED";
    case SDL_EVENT_JOYSTICK_REMOVED: return "SDL_EVENT_JOYSTICK_REMOVED";
    case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE: return "SDL_EVENT_JOYSTICK_UPDATE_COMPLETE";

    // English comment: Game Controller events
    case SDL_EVENT_GAMEPAD_AXIS_MOTION: return "SDL_EVENT_GAME_CONTROLLER_AXIS_MOTION";
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN: return "SDL_EVENT_GAME_CONTROLLER_BUTTON_DOWN";
    case SDL_EVENT_GAMEPAD_BUTTON_UP: return "SDL_EVENT_GAME_CONTROLLER_BUTTON_UP";
    case SDL_EVENT_GAMEPAD_ADDED: return "SDL_EVENT_GAMEPAD_ADDED";
    case SDL_EVENT_GAMEPAD_REMOVED: return "SDL_EVENT_GAMEPAD_REMOVED";
    case SDL_EVENT_GAMEPAD_REMAPPED: return "SDL_EVENT_GAME_CONTROLLER_REMAPPED";
    case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN: return "SDL_EVENT_GAME_CONTROLLER_TOUCHPAD_DOWN";
    case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION: return "SDL_EVENT_GAME_CONTROLLER_TOUCHPAD_MOTION";
    case SDL_EVENT_GAMEPAD_TOUCHPAD_UP: return "SDL_EVENT_GAME_CONTROLLER_TOUCHPAD_UP";
    case SDL_EVENT_GAMEPAD_SENSOR_UPDATE: return "SDL_EVENT_GAME_CONTROLLER_SENSOR_UPDATE";
    case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED: return "SDL_EVENT_GAME_CONTROLLER_STEAM_HANDLE_UPDATED";

    // English comment: Audio hotplug events
    case SDL_EVENT_AUDIO_DEVICE_ADDED: return "SDL_EVENT_AUDIO_DEVICE_ADDED";
    case SDL_EVENT_AUDIO_DEVICE_REMOVED: return "SDL_EVENT_AUDIO_DEVICE_REMOVED";

    // English comment: Touch events
    case SDL_EVENT_FINGER_DOWN: return "SDL_EVENT_FINGER_DOWN";
    case SDL_EVENT_FINGER_UP: return "SDL_EVENT_FINGER_UP";
    case SDL_EVENT_FINGER_MOTION: return "SDL_EVENT_FINGER_MOTION";

    // English comment: Gesture events
    case SDL_EVENT_POLL_SENTINEL: return "SDL_EVENT_DOLLAR_GESTURE";

    // English comment: Clipboard events
    case SDL_EVENT_CLIPBOARD_UPDATE: return "SDL_EVENT_CLIPBOARD_UPDATE";

    // English comment: Drag and Drop events
    case SDL_EVENT_DROP_FILE: return "SDL_EVENT_DROP_FILE";
    case SDL_EVENT_DROP_TEXT: return "SDL_EVENT_DROP_TEXT";
    case SDL_EVENT_DROP_BEGIN: return "SDL_EVENT_DROP_BEGIN";
    case SDL_EVENT_DROP_COMPLETE: return "SDL_EVENT_DROP_COMPLETE";

    // English comment: Sensor events
    case SDL_EVENT_SENSOR_UPDATE: return "SDL_EVENT_SENSOR_UPDATE";

    // English comment: Render events
    case SDL_EVENT_RENDER_TARGETS_RESET: return "SDL_EVENT_RENDER_TARGETS_RESET";
    case SDL_EVENT_RENDER_DEVICE_RESET: return "SDL_EVENT_RENDER_DEVICE_RESET";


    // English comment: User defined events
    case SDL_EVENT_USER: return "SDL_EVENT_USER"; // You might want to append event.user.code here for more detail

    // English comment: Default case for unknown event types
    default: return QString("UNKNOWN_SDL_EVENT_TYPE_") + QString::number(_sdlType);
    }
}

void QSDLEvent::setSdlType(SDL_EventType newSdlType)
{
    _sdlType = newSdlType;
}
}
