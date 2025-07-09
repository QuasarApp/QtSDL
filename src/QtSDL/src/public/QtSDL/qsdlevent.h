//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLEVENT_H
#define QSDLEVENT_H

#include <QEvent>     // Base class for Qt events
#include <SDL3/SDL.h> // Include SDL3 header for SDL_Event and SDL_EventType

/**
 * @brief The QSDLEvent class provides a custom Qt event for encapsulating SDL events.
 *
 * This class serves as a bridge between SDL's event system and Qt's event loop.
 * It allows raw SDL events to be wrapped into a QEvent object, enabling them
 * to be posted and processed within Qt's standard event handling mechanism.
 * This is crucial for integrating low-level input (like game controllers,
 * specific keyboard/mouse events) from SDL into a Qt-based application
 * in a thread-safe manner.
 *
 * Instances of this class are typically created by a dedicated SDL event polling thread
 * (like `SDLEventManager`) and then posted to the main Qt application thread
 * using `QCoreApplication::postEvent()`.
 */
class QSDLEvent : public QEvent
{
public:
    /**
     * @brief Custom event type for QSDLEvent.
     *
     * This unique type allows Qt's event system to identify instances
     * of QSDLEvent among other QEvent types. It's set to `QEvent::Type::User`
     * to indicate that it's a custom application-specific event.
     */
    enum Type {
        SDLType = QEvent::Type::User ///< The custom QEvent type for all QSDLEvent instances.
    };

    /**
     * @brief Constructs a QSDLEvent object from an SDL event.
     * @param event The raw SDL_Event structure to encapsulate. This structure
     * contains all the specific data for the SDL event (e.g., key codes,
     * mouse coordinates, gamepad button states).
     * @param type The specific SDL_EventType of the encapsulated event.
     * This is often redundantly provided from `event.type` but can
     * be useful for explicit type casting.
     *
     * @note The `event` parameter is copied into the internal `_data` member.
     */
    explicit QSDLEvent(SDL_Event event, SDL_EventType type);

    // QEvent interface overrides
    /// @cond Doxygen_Ignored
    // QEvent's setAccepted() and clone() are typically handled by Qt's
    // internal mechanisms for custom events posted via QCoreApplication::postEvent.
    // However, they are required to be implemented if you inherit QEvent directly.
    // For posted events, accepted status is usually not relevant after delivery.
    /// @endcond
    /**
     * @brief Sets the accepted status of the event.
     *
     * This method is part of the QEvent interface. For posted events,
     * the accepted status is often not used by Qt's event loop after delivery.
     * @param accepted True if the event has been handled, false otherwise.
     */
    void setAccepted(bool accepted) override;

    /**
     * @brief Creates a deep copy of the event.
     *
     * This method is part of the QEvent interface and is required for proper
     * event handling, especially if events are copied internally by Qt.
     * @return A pointer to a new QSDLEvent object that is a clone of the current one.
     * The caller is responsible for deleting the returned object.
     */
    QEvent *clone() const override;

    /**
     * @brief Retrieves the encapsulated raw SDL_Event data.
     * @return A copy of the SDL_Event structure. Use this to access specific
     * details of the SDL event (e.g., `data().key`, `data().motion`, `data().cbutton`).
     */
    SDL_Event data() const;

    /**
     * @brief Sets the encapsulated raw SDL_Event data.
     * @param newData The new SDL_Event structure to encapsulate.
     */
    void setData(const SDL_Event &newData);

    /**
     * @brief Retrieves the specific SDL_EventType of the encapsulated event.
     * @return The SDL_EventType indicating what kind of SDL event this represents.
     */
    SDL_EventType sdlType() const;

    /**
     * @brief Sets the specific SDL_EventType for the encapsulated event.
     * @param newSdlType The new SDL_EventType.
     */
    void setSdlType(SDL_EventType newSdlType);

private:
    /**
     * @brief The raw SDL_Event structure containing event-specific data.
     */
    SDL_Event _data;

    /**
     * @brief The specific SDL_EventType of the encapsulated event.
     *
     * This field stores the type of the SDL event, allowing for easy identification
     * without needing to access the `_data` union.
     */
    SDL_EventType _sdlType;
};

#endif // QSDLEVENT_H
