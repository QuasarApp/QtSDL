//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLGAMEPADEVENT_H
#define QSDLGAMEPADEVENT_H

#include "QtSDL/qsdlevent.h" // Base class for custom SDL events in Qt

namespace QtSDL {

/**
 * @brief The QSDLGamepadEvent class encapsulates an SDL gamepad device event.
 *
 * This class specifically wraps the `SDL_GamepadDeviceEvent` structure, providing
 * a Qt-friendly interface for managing gamepad connection and disconnection events.
 * It inherits from `QSDLEvent`, enabling its seamless integration into Qt's event system.
 *
 * @section sdl_doc_section From SDL Documentation:
 * "Gamepad device event structure (event.gdevice.*)"
 *
 * Gamepads that are also supported as joysticks will receive both an
 * `SDL_JoyDeviceEvent` and an `SDL_GamepadDeviceEvent`.
 *
 * SDL will send `SDL_EVENT_GAMEPAD_ADDED` events for gamepads that are already
 * plugged in during `SDL_Init()` and are recognized as gamepads. It will also
 * send these events for joysticks that acquire gamepad mappings at runtime.
 *
 * @since This struct is available since SDL 3.2.0.
 *
 * @sa SDL_JoyDeviceEvent
 */
class QTSDL_EXPORT QSDLGamepadEvent: public QSDLEvent
{
public:
    /**
     * @brief Constructs a QSDLGamepadEvent object.
     * @param event The raw `SDL_Event` structure containing the gamepad device data.
     * This event's type must be either `SDL_EVENT_GAMEPAD_ADDED` or
     * `SDL_EVENT_GAMEPAD_REMOVED`.
     * @param type The specific `SDL_EventType`, which should correspond to a
     * gamepad device event (e.g., `SDL_EVENT_GAMEPAD_ADDED`).
     *
     * @note The `event` parameter's `gdevice` member will be used to populate
     * the specific device data accessible via `sdlEvent()`.
     */
    explicit QSDLGamepadEvent(SDL_Event event, SDL_EventType type);

    /**
     * @brief Provides direct access to the native `SDL_GamepadDeviceEvent` data.
     *
     * This method acts as a specialized wrapper for the inherited `data()` method,
     * casting the generic `SDL_Event` to the more specific `SDL_GamepadDeviceEvent` type.
     * This allows direct access to device-specific fields like `which` (device instance ID)
     * without needing explicit casting.
     * @return A constant reference to the underlying `SDL_GamepadDeviceEvent` structure.
     * Access its members (e.g., `sdlEvent().which`) to get details about the
     * gamepad device event.
     */
    const SDL_GamepadDeviceEvent &sdlEvent() const;
};
} // namespace QtSDL
#endif // QSDLGAMEPADEVENT_H
