//#
//# Copyright (C) 2025-2026 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef SDLEVENTMANAGER_H
#define SDLEVENTMANAGER_H

#include <QHash>   // Required for QHash to manage gamepad pointers
#include <QSet>
#include <QThread> // QThread is included for thread management
#include <SDL3/SDL.h> // SDL3 header for SDL event handling and gamepad management
#include "QtSDL/qsdlgamepadinputevent.h"
#include "global.h"
#include "qsdlgamepadaxisevent.h"
#include "qsdlgamepadbuttonevent.h"


namespace QtSDL {

/**
 * @brief The SDLEventManager class manages SDL events by redirecting them to Qt's event loop.
 *
 * This class inherits from QThread and runs its own dedicated event loop to continuously
 * poll for SDL events. Upon receiving an SDL event, it intelligently wraps it into
 * a custom `QSDLEvent` (or one of its specialized derived classes) and posts it
 * to the main Qt application's event queue.
 *
 * It also handles the lifecycle of connected gamepads.
 *
 * @note This manager should be initialized and started early in your application's lifecycle.
 * **Crucially, ensure `QtSDL::init()` has been successfully invoked before using this class.**
 * Call `stop()` and `wait()` during application shutdown.
 */
class QTSDL_EXPORT SDLEventManager: public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an SDLEventManager instance.
     * @param parent The parent QObject for memory management.
     */
    SDLEventManager(QObject* parent = nullptr);

    /**
     * @brief Destroys the SDLEventManager instance.
     *
     * Ensures the polling thread is stopped and any open SDL gamepad handles are closed.
     */
    ~SDLEventManager() override;

    /**
     * @brief Requests the event manager thread to stop its polling loop.
     *
     * Call `wait()` afterwards to ensure thread termination.
     */
    void stop();

    /**
     * @brief Returns the current delay (in milliseconds) applied after each SDL event polling cycle.
     * @return The delay in milliseconds.
     */
    int eventDelay() const;

    /**
     * @brief Sets the delay (in milliseconds) to be applied after each SDL event polling cycle.
     * @param newEventDelay The desired delay in milliseconds.
     */
    void setEventDelay(int newEventDelay);

protected:
    /**
     * @brief The main entry point for the event manager thread.
     *
     * Continuously polls for SDL events and posts them to Qt's event queue.
     * Handles gamepad device lifecycle.
     */
    void run() override;

private:

    /**
     * @brief scanModifiers this method changed the moddiifiers of the event.
     *  This method collect all pressed button every time, and set the modifiers of the event.
     * @note This implementation will not push to the _pressedButNotReleasedModifiers all presed buttons.
     * @param event is a event for generate modifiers.
     */
    void scanModifiers(QSDLGamepadInputEvent &event);

    /**
     * @brief scanModifiers this implementation will push to the _pressedButNotReleasedModifiers all presed buttons.
     *  And remove from the list all released buttons. Rest of the buttons will be added to the modifiers.
     * @param event is a button event for generate modifiers.
     */
    void scanModifiers(QSDLGamepadButtonEvent &event);

    /**
     * @brief scanModifiers this implementation will push to the _pressedButNotReleasedModifiers all presed asix buttons like a triggers.
     * @param event is a axis event for generate modifiers.
     */
    void scanModifiers(QSDLGamepadAxisEvent &event);

    /**
     * @brief Flag to control the execution loop of the thread.
     */
    volatile bool m_quitFlag = false;

    /**
     * @brief The delay in milliseconds applied after each SDL event polling cycle.
     */
    int m_eventDelay = 10;

    /**
     * @brief A hash map storing pointers to currently opened `SDL_Gamepad` objects.
     */
    QHash<int, SDL_Gamepad*> m_gamepads;

    /**
     * @brief Calculates and sets the modifier flags for a gamepad input event.
     *
     * This method inspects the set of currently pressed buttons (`_pressedButNotReleasedModifiers`)
     * and constructs a bitmask of active modifiers (L1, R1, etc.). This bitmask is then
     * applied to the given `event`.
     * @param event The event to which the modifiers will be applied.
     */
    QSet<int> _pressedButNotReleasedModifiers;
};
} // namespace QtSDL

#endif // SDLEVENTMANAGER_H
