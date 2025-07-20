//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef QSDLGAMEPADSENSOREVENT_H
#define QSDLGAMEPADSENSOREVENT_H

#include "qsdlevent.h" // Base class for custom SDL events in Qt

namespace QtSDL {

/**
 * @brief The QSDLGamepadSensorEvent class encapsulates an SDL gamepad sensor event.
 *
 * This class specifically wraps the `SDL_GamepadSensorEvent` structure, providing
 * a Qt-friendly interface for handling sensor data from gamepads (e.g., gyroscope,
 * accelerometer). It inherits from `QSDLEvent`, enabling its seamless integration
 * into Qt's event system.
 *
 * @section sdl_doc_section From SDL Documentation:
 * "Gamepad sensor event structure (event.gsensor.*)"
 * This event is generated when a gamepad's built-in sensor (like an accelerometer
 * or gyroscope) reports new data. It provides information about which gamepad
 * generated the event, the type of sensor, and the sensor's current data values.
 */
class QTSDL_EXPORT QSDLGamepadSensorEvent: public QSDLEvent
{
public:
    /**
     * @brief Default constructs a QSDLGamepadSensorEvent object.
     *
     * Initializes a new, empty `QSDLGamepadSensorEvent`. Note that for a meaningful
     * event, the constructor taking an `SDL_Event` should be used.
     */
    QSDLGamepadSensorEvent();

    /**
     * @brief Constructs a QSDLGamepadSensorEvent object from an SDL event.
     * @param event The raw `SDL_Event` structure containing the gamepad sensor data.
     * This event's type must be `SDL_EVENT_GAMEPAD_SENSOR_UPDATE`.
     * @param type The specific `SDL_EventType`, which should be
     * `SDL_EVENT_GAMEPAD_SENSOR_UPDATE` for this event.
     *
     * @note The `event` parameter's `gsensor` member will be used to populate
     * the specific sensor data accessible via `sdlEvent()`.
     */
    explicit QSDLGamepadSensorEvent(SDL_Event event, SDL_EventType type);

    /**
     * @brief Provides direct access to the native `SDL_GamepadSensorEvent` data.
     *
     * This method acts as a specialized wrapper for the inherited `data()` method,
     * casting the generic `SDL_Event` to the more specific `SDL_GamepadSensorEvent` type.
     * This allows direct access to sensor-specific fields like `sensor`, `data`,
     * and `timestamp` without needing explicit casting.
     * @return A constant reference to the underlying `SDL_GamepadSensorEvent` structure.
     * Access its members (e.g., `sdlEvent().sensor`, `sdlEvent().data[0]`) to get
     * details about the sensor reading.
     */
    const SDL_GamepadSensorEvent &sdlEvent() const;
};

} // namespace QtSDL
#endif // QSDLGAMEPADSENSOREVENT_H
