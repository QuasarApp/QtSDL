//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef SDLEVENTMANAGER_H
#define SDLEVENTMANAGER_H

#include <QThread> // Включаем QThread для работы с потоками
#include <SDL3/SDL.h>

namespace QtSDL {

/**
 * @brief The SDLEventManager class manages SDL events by redirecting them to Qt's event loop.
 *
 * This class inherits from QThread and runs its own event loop to poll for SDL events.
 * Upon receiving an SDL event, it wraps it into a custom QSDLEvent and posts it
 * to the main Qt application's event queue. This allows SDL events to be processed
 * within the Qt event handling mechanism, ensuring thread safety and proper integration
 * of low-level SDL input with Qt's GUI.
 *
 * @note This manager should be initialized and started early in your application's lifecycle.
 * Ensure SDL is properly initialized (e.g., SDL_Init(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER))
 * before starting this thread.
 * Remember to call `stop()` and `wait()` on this manager during application shutdown
 * to gracefully terminate the SDL event polling thread.
 */
class SDLEventManager : public QThread
{
    Q_OBJECT // Required for Qt's meta-object system (signals/slots, Q_PROPERTY etc.)

public:
    /**
     * @brief Constructs an SDLEventManager instance.
     * @param parent The parent QObject for memory management.
     *
     * @note SDL initialization is not performed by this constructor.
     * Ensure SDL is initialized globally before starting this manager.
     */
    SDLEventManager(QObject* parent = nullptr);
    ~SDLEventManager() override;

    /**
     * @brief Requests the event manager thread to stop its polling loop.
     *
     * This method sets an internal flag to signal the `run()` method to exit its loop.
     * After calling this, you should typically call `wait()` on the QThread
     * object to ensure the thread has finished execution before proceeding
     * with application shutdown or resource cleanup.
     */
    void stop();

    /**
     * @brief Returns the current delay (in milliseconds) applied after each SDL event polling cycle.
     *
     * This delay helps to reduce CPU usage when no SDL events are pending.
     * A value of 0 means no delay (continuous polling).
     * @return The delay in milliseconds.
     */
    int eventDelay() const;

    /**
     * @brief Sets the delay (in milliseconds) to be applied after each SDL event polling cycle.
     *
     * This method allows you to adjust the pause duration between successive
     * checks for new SDL events, influencing CPU usage.
     * A value of 0 means no delay (continuous polling, potentially higher CPU usage).
     * @param newEventDelay The desired delay in milliseconds.
     */
    void setEventDelay(int newEventDelay);

protected:
    /**
     * @brief The main entry point for the event manager thread.
     *
     * This method contains the infinite loop that continuously polls for SDL events
     * using `SDL_PollEvent()`. Each received SDL event is then encapsulated
     * into a `QSDLEvent` and posted to the `QCoreApplication`'s event queue
     * for asynchronous processing in the main Qt thread.
     * A delay specified by `eventDelay()` is applied after processing all
     * available events in a cycle to reduce CPU load.
     *
     * @note This method is called automatically when `start()` is invoked on the thread object.
     * It exits when the `stop()` method is called and the internal `quit` flag is set.
     */
    void run() override;

private:
    /**
     * @brief Flag to control the execution loop of the thread.
     *
     * Set to `true` by the `stop()` method to signal the `run()` method to exit.
     * Marked as `volatile` to ensure correct behavior in multi-threaded contexts.
     */
    volatile bool m_quitFlag = false; // Renamed 'quit' to 'm_quitFlag' for clarity and convention.
    // Made volatile to ensure changes are seen across threads.
    /**
     * @brief The delay in milliseconds applied after each SDL event polling cycle.
     *
     * This value determines how long the thread pauses if no events are found
     * in a polling cycle. Default is 10 milliseconds.
     */
    int m_eventDelay = 10; // Renamed to m_eventDelay for consistency.
};
} // namespace QtSDL

#endif // SDLEVENTMANAGER_H
