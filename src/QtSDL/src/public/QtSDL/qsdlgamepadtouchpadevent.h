//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLGAMEPADTOUCHPADEVENT_H
#define QSDLGAMEPADTOUCHPADEVENT_H
#include "qsdlevent.h" // Base class for custom SDL events in Qt

namespace QtSDL {

/**
 * @brief The QSDLGamepadTouchpadEvent class encapsulates an SDL gamepad touchpad event.
 *
 * This class specifically wraps the `SDL_GamepadTouchpadEvent` structure, providing
 * a Qt-friendly interface for handling input from a gamepad's integrated touchpad.
 * It inherits from `QSDLEvent`, enabling its seamless integration into Qt's event system.
 *
 * @section sdl_doc_section From SDL Documentation:
 * "Gamepad touchpad event structure (event.gtouchpad.*)"
 * This event is generated when a touchpad on a gamepad is touched, moved, or released.
 * It provides information about which gamepad generated the event, which touchpad
 * was affected, the finger index, and the X/Y coordinates of the touch.
 */
class QTSDL_EXPORT QSDLGamepadTouchpadEvent: public QSDLEvent
{
public:
    /**
     * @brief Constructs a QSDLGamepadTouchpadEvent object from an SDL event.
     * @param event The raw `SDL_Event` structure containing the gamepad touchpad data.
     * This event's type must be `SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN`,
     * `SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION`, or `SDL_EVENT_GAMEPAD_TOUCHPAD_UP`.
     * @param type The specific `SDL_EventType`, which should correspond to a
     * gamepad touchpad event.
     *
     * @note The `event` parameter's `gtouchpad` member will be used to populate
     * the specific touchpad data accessible via `sdlEvent()`.
     */
    explicit QSDLGamepadTouchpadEvent(SDL_Event event, SDL_EventType type);

    /**
     * @brief Provides direct access to the native `SDL_GamepadTouchpadEvent` data.
     *
     * This method acts as a specialized wrapper for the inherited `data()` method,
     * casting the generic `SDL_Event` to the more specific `SDL_GamepadTouchpadEvent` type.
     * This allows direct access to touchpad-specific fields like `touchpad`, `finger`,
     * `x`, `y`, and `pressure` without needing explicit casting.
     * @return A constant reference to the underlying `SDL_GamepadTouchpadEvent` structure.
     * Access its members (e.g., `sdlEvent().x`, `sdlEvent().finger`) to get
     * details about the touchpad event.
     */
    const SDL_GamepadTouchpadEvent &sdlEvent() const;
};
} // namespace QtSDL
#endif // QSDLGAMEPADTOUCHPADEVENT_H
