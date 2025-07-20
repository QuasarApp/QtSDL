//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLEVENT_H
#define QSDLEVENT_H

#include <QEvent>      // Base class for Qt events
#include <SDL3/SDL.h> // Include SDL3 header for SDL_Event and SDL_EventType
#include "global.h"

namespace QtSDL {

/**
 * @brief The QSDLEvent class provides a custom Qt event for encapsulating SDL events.
 *
 * This class serves as a crucial bridge between SDL's low-level event system
 * and Qt's high-level event loop. It allows raw SDL events to be wrapped
 * into a QEvent object, enabling them to be seamlessly posted and processed
 * within Qt's standard event handling mechanism. This integration is vital
 * for incorporating specific low-level input (such as game controllers,
 * advanced keyboard/mouse events, or custom SDL events) from SDL into a
 * Qt-based application in a robust and thread-safe manner.
 *
 * Instances of this class are typically created by a dedicated SDL event polling thread
 * (e.g., `SDLEventManager`) and then safely posted to the main Qt application thread
 * using `QCoreApplication::postEvent()`. This ensures that all SDL event processing
 * occurs on the main GUI thread, adhering to Qt's threading model.
 */
class QTSDL_EXPORT QSDLEvent : public QEvent
{
public:
    /**
     * @brief Custom event type for QSDLEvent instances.
     *
     * This unique type allows Qt's event system to specifically identify
     * and dispatch instances of QSDLEvent among other QEvent types.
     * It's derived from `QEvent::Type::User` to signify that it is a
     * custom, application-specific event.
     */
    enum Type {
        SDLType = QEvent::Type::User ///< The custom QEvent type for all QSDLEvent instances.
    };

    /**
     * @brief Constructs a QSDLEvent object, encapsulating an SDL event.
     * @param event The raw `SDL_Event` structure to encapsulate. This structure
     * contains all the specific data relevant to the SDL event
     * (e.g., key codes for keyboard events, mouse coordinates,
     * gamepad button states).
     * @param type  The specific `SDL_EventType` of the encapsulated event.
     * While often redundant with `event.type`, providing it explicitly
     * can be useful for clarity and direct type access.
     *
     * @note The `event` parameter is copied into the internal `_data` member
     * upon construction. The `type` parameter is also stored in `_sdlType`.
     */
    explicit QSDLEvent(SDL_Event event, SDL_EventType type);


    /**
     * @brief Sets the accepted status of the event.
     *
     * This method is part of the `QEvent` interface. For custom events
     * posted via `QCoreApplication::postEvent()`, the accepted status
     * is often not directly used by Qt's event loop after delivery to
     * event handlers. It can, however, be used by custom event filters
     * or handlers to signal whether the event has been consumed.
     * @param accepted `true` if the event has been handled and should
     * stop propagation, `false` otherwise.
     */
    void setAccepted(bool accepted) override;

    /**
     * @brief Creates a deep copy of the event.
     *
     * This method is a required part of the `QEvent` interface and is crucial
     * for proper event handling within Qt's framework, especially if events
     * are copied internally (e.g., when queued or dispatched).
     * @return A pointer to a newly allocated `QSDLEvent` object that is a
     * deep clone of the current instance. The caller is responsible
     * for deleting the returned object to prevent memory leaks.
     */
    QEvent *clone() const override;

    /**
     * @brief Retrieves the encapsulated raw `SDL_Event` data.
     * @return A constant reference to the internal `SDL_Event` structure.
     * Use this to access specific details of the SDL event, such as
     * `data().key` for keyboard events, `data().motion` for mouse
     * motion, or `data().cbutton` for gamepad button states.
     */
    const SDL_Event &data() const;

    /**
     * @brief Sets the encapsulated raw `SDL_Event` data.
     * @param newData The new `SDL_Event` structure to encapsulate.
     * This will overwrite the currently stored SDL event data.
     */
    void setData(const SDL_Event &newData);

    /**
     * @brief Retrieves the specific `SDL_EventType` of the encapsulated event.
     * @return The `SDL_EventType` enumeration value, indicating what kind of
     * SDL event this `QSDLEvent` instance represents (e.g., `SDL_EVENT_KEY_DOWN`,
     * `SDL_EVENT_MOUSE_MOTION`).
     */
    SDL_EventType sdlType() const;

    /**
     * @brief Converts the encapsulated `SDL_EventType` into a human-readable string.
     *
     * This utility method is useful for debugging, logging, or displaying
     * the type of the underlying SDL event in a user-friendly format.
     * @return A `QString` containing the human-readable name of the `SDL_EventType`.
     * Returns an empty string or "Unknown SDL Event Type" if the type is unrecognized.
     */
    QString sdlEventTypeName() const;

    /**
     * @brief Sets the specific `SDL_EventType` for the encapsulated event.
     * @param newSdlType The new `SDL_EventType` to associate with this event.
     * This should typically match the type within the `_data`
     * `SDL_Event` union for consistency.
     */
    void setSdlType(SDL_EventType newSdlType);

private:
    /**
     * @brief The raw `SDL_Event` structure containing event-specific data.
     *
     * This member holds the complete data payload of the original SDL event,
     * which can vary greatly depending on the event type (e.g., keyboard data,
     * mouse coordinates, joystick states, touch events, etc.).
     */
    SDL_Event _data;

    /**
     * @brief The specific `SDL_EventType` of the encapsulated event.
     *
     * This field explicitly stores the type of the SDL event, allowing for
     * quick and direct identification without needing to access the `_data` union
     * and inspect its `type` member. It serves as a convenient cached value.
     */
    SDL_EventType _sdlType;
};
} // namespace QtSDL
#endif // QSDLEVENT_H
