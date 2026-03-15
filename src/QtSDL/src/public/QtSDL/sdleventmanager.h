//#
//# Copyright (C) 2025-2026 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef SDLEVENTMANAGER_H
#define SDLEVENTMANAGER_H

#include <QCoreApplication>
#include <QHash>
#include <QSet>
#include <QThread>
#include <bitset>
#include <SDL3/SDL.h>
#include "QtSDL/qsdlgamepadinputevent.h"
#include "global.h"
#include "qsdlgamepadaxisevent.h"
#include "qsdlgamepadbuttonevent.h"

namespace QtSDL {

/**
 * @brief The GamePadModifiers class tracks the current state of gamepad buttons and axes
 */
struct GamePadModifiers {
    /**
     * @brief pressedButtons Set of currently pressed buttons for modifier tracking.
     */
    std::bitset<SDL_GAMEPAD_BUTTON_COUNT> pressedButtons;

    /**
     * @brief pressedAxis Set of currently active axes (e.g., triggers) for modifier tracking.
     */
    std::bitset<SDL_GAMEPAD_AXIS_COUNT> pressedAxis;
};

/**
 * @brief The SDLEventManager class manages SDL events by redirecting them to Qt's event loop.
 *
 * This class runs a dedicated thread to poll SDL events. It wraps SDL events into
 * custom QEvent-based classes (QtSDL::QSDLGamepadButtonEvent, etc.) and posts them
 * to the main application thread.
 */
class QTSDL_EXPORT SDLEventManager: public QThread
{
    Q_OBJECT

public:
    SDLEventManager(QObject* parent = nullptr);
    ~SDLEventManager() override;

    enum Sensors {
        SENSOR_GYRO,
        SENSOR_ACCEL,
        SIZE
    };

    /**
     * @brief Requests the polling loop to terminate.
     * Use wait() after calling this to ensure the thread has finished.
     */
    void stop();

    int eventDelay() const;
    void setEventDelay(int newEventDelay);

    /**
     * @brief gamepadSensors current behavior for new gamepads.
     * @return
     */
    bool gamepadSensors(Sensors sensor) const;

    /**
     * @brief setGamepadSensors sets new value of gamepad sensors flag.
     * @param newGamepadSensors set to true to fetch signals from sensors.
     */
    void setGamepadSensors(Sensors sensor, bool newGamepadSensors);

protected:
    /**
     * @brief Main thread loop for polling SDL_Events.
     */
    void run() override;
    virtual void postEvent(QCoreApplication *appInstance, QSDLEvent* event);

private:
    /**
     * @brief Calculates and applies current modifier flags to a generic input event.
     * This method does not modify the internal state of pressed buttons.
     * @param event The event to be decorated with current modifiers.
     */
    void scanModifiers(QSDLGamepadInputEvent &event, int deviceIndex);

    /**
     * @brief Updates the internal modifier state based on a button press/release.
     * Adds or removes buttons from the internal tracking set and applies the result to the event.
     * @param event The button event providing the new state.
     */
    void scanModifiers(QSDLGamepadButtonEvent &event, int deviceIndex);

    /**
     * @brief Updates the internal modifier state based on trigger axis movement.
     * Converts analog trigger values (L2/R2) into virtual modifier states using
     * a predefined threshold.
     * @param event The axis event providing the pressure value.
     */
    void scanModifiers(QSDLGamepadAxisEvent &event, int deviceIndex);

    /**
     * @brief Flag to safely terminate the thread loop.
     */
    volatile bool m_quitFlag = false;

    /**
     * @brief m_gamepadSensors enabled or disable sensors on gamepad like giro
     */
    std::bitset<SIZE> m_gamepadSensors {};

    /**
     * @brief Polling interval in milliseconds to prevent high CPU usage.
     */
    int m_eventDelay = 10;

    /**
     * @brief Map of active SDL_Gamepad handles indexed by their instance ID.
     */
    QHash<int, SDL_Gamepad*> m_gamepads;

    /**
     * @brief Map of gamepad modifiers state indexed by gamepad instance ID.
     */
    QHash<int, GamePadModifiers> m_gamepadModifiers;



};
} // namespace QtSDL

#endif // SDLEVENTMANAGER_H
