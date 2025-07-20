//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLGAMEPADBUTTONEVENT_H
#define QSDLGAMEPADBUTTONEVENT_H

#include "QtSDL/qsdlevent.h" // Base class for custom SDL events in Qt

namespace QtSDL {

/**
 * @brief The QSDLGamepadButtonEvent class encapsulates an SDL gamepad button event.
 *
 * This class specifically wraps the `SDL_GamepadButtonEvent` structure, providing
 * a Qt-friendly interface for handling gamepad button presses and releases.
 * It inherits from `QSDLEvent`, enabling its seamless integration into Qt's event system.
 *
 * From SDL documentation:
 * "Gamepad button event structure (event.gbutton.*)"
 * This event is generated when a button on a gamepad is pressed down or released.
 * It provides information about which gamepad generated the event, which button
 * was affected, and the current state (pressed or released) of that button.
 */
class QTSDL_EXPORT QSDLGamepadButtonEvent: public QSDLEvent
{
public:
    /**
     * @brief Constructs a QSDLGamepadButtonEvent object.
     * @param event The raw `SDL_Event` structure containing the gamepad button data.
     * This event's type must be either `SDL_EVENT_GAMEPAD_BUTTON_DOWN`
     * or `SDL_EVENT_GAMEPAD_BUTTON_UP`.
     * @param type The specific `SDL_EventType`, which should be
     * `SDL_EVENT_GAMEPAD_BUTTON_DOWN` or `SDL_EVENT_GAMEPAD_BUTTON_UP` for this event.
     *
     * @note The `event` parameter's `gbutton` member will be used to populate
     * the specific button data accessible via `sdlEvent()`.
     */
    QSDLGamepadButtonEvent(SDL_Event event, SDL_EventType type);


    /**
     * @brief Provides direct access to the native `SDL_GamepadButtonEvent` data.
     *
     * This method acts as a specialized wrapper for the inherited `data()` method,
     * casting the generic `SDL_Event` to the more specific `SDL_GamepadButtonEvent` type.
     * This allows direct access to the button-specific fields like `button`, `state`,
     * and `which` without needing explicit casting.
     * @return A constant reference to the underlying `SDL_GamepadButtonEvent` structure.
     * Access its members (e.g., `sdlEvent().button`, `sdlEvent().state`) to get
     * details about the button event.
     */
    const SDL_GamepadButtonEvent &sdlEvent() const;
};
} // namespace QtSDL
#endif // QSDLGAMEPADBUTTONEVENT_H
