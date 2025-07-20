//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLGAMEPADAXISEVENT_H
#define QSDLGAMEPADAXISEVENT_H
#include "qsdlevent.h" // Base class for custom SDL events in Qt

namespace QtSDL {

/**
 * @brief The QSDLGamepadAxisEvent class encapsulates an SDL gamepad axis motion event.
 *
 * This class specifically wraps the `SDL_GamepadAxisEvent` structure, providing
 * a Qt-friendly interface for handling gamepad axis movements (e.g., analog sticks,
 * triggers). It inherits from `QSDLEvent`, allowing it to be seamlessly integrated
 * into Qt's event system.
 *
 * From SDL documentation:
 * "Gamepad axis motion event structure (event.gaxis.*)"
 * This event is generated when a gamepad axis moves, typically indicating
 * a change in the position of an analog stick or the pressure on a trigger.
 * It provides information about which gamepad generated the event, which axis
 * moved, and the current value of that axis.
 */
class QTSDL_EXPORT QSDLGamepadAxisEvent: public QSDLEvent
{
public:
    /**
     * @brief Constructs a QSDLGamepadAxisEvent object.
     * @param event The raw `SDL_Event` structure containing the gamepad axis data.
     * This event's type must be `SDL_EVENT_GAMEPAD_AXIS_MOTION`.
     * @param type The specific `SDL_EventType`, which should be
     * `SDL_EVENT_GAMEPAD_AXIS_MOTION` for this event.
     *
     * @note The `event` parameter's `gaxis` member will be used to populate
     * the specific axis data accessible via `sdlEvent()`.
     */
    QSDLGamepadAxisEvent(SDL_Event event, SDL_EventType type);


    /**
     * @brief Provides direct access to the native `SDL_GamepadAxisEvent` data.
     *
     * This method acts as a specialized wrapper for the inherited `data()` method,
     * casting the generic `SDL_Event` to the more specific `SDL_GamepadAxisEvent` type.
     * This allows direct access to the axis-specific fields like `axis`, `value`,
     * and `which` without needing explicit casting.
     * @return A constant reference to the underlying `SDL_GamepadAxisEvent` structure.
     * Access its members (e.g., `sdlEvent().axis`, `sdlEvent().value`) to get
     * details about the axis motion.
     */
    const SDL_GamepadAxisEvent &sdlEvent() const;
};
} // namespace QtSDL
#endif // QSDLGAMEPADAXISEVENT_H
