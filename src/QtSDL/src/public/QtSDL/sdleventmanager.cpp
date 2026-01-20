//#
//# Copyright (C) 2025-2026 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "QtSDL/qsdlgamepadaxisevent.h"
#include "QtSDL/qsdlgamepadbuttonevent.h"
#include "QtSDL/qsdlgamepadevent.h"
#include "QtSDL/qsdlgamepadsensorevent.h"
#include "QtSDL/qsdlgamepadtouchpadevent.h"
#include "qsdlevent.h"
#include "sdleventmanager.h"
#include <QCoreApplication>

namespace QtSDL {

SDLEventManager::SDLEventManager(QObject* parent): QThread(parent) {}

SDLEventManager::~SDLEventManager() {
    stop();
    wait();

    SDL_Quit();
}


void SDLEventManager::stop() {
    m_quitFlag = true;
}

void QtSDL::SDLEventManager::run() {
    m_quitFlag = false;

    auto appInstance = QCoreApplication::instance();
    while (!m_quitFlag && appInstance) {
        SDL_Event event;

        if (SDL_WaitEventTimeout(&event, m_eventDelay)) {

            do {

                // SDL_EVENT_GAMEPAD_AXIS_MOTION  = 0x650, /**< Gamepad axis motion */
                //     SDL_EVENT_GAMEPAD_BUTTON_DOWN,          /**< Gamepad button pressed */
                //     SDL_EVENT_GAMEPAD_BUTTON_UP,            /**< Gamepad button released */
                //     SDL_EVENT_GAMEPAD_ADDED,                /**< A new gamepad has been inserted into the system */
                //     SDL_EVENT_GAMEPAD_REMOVED,              /**< A gamepad has been removed */
                //     SDL_EVENT_GAMEPAD_REMAPPED,             /**< The gamepad mapping was updated */
                //     SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN,        /**< Gamepad touchpad was touched */
                //     SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION,      /**< Gamepad touchpad finger was moved */
                //     SDL_EVENT_GAMEPAD_TOUCHPAD_UP,          /**< Gamepad touchpad finger was lifted */
                //     SDL_EVENT_GAMEPAD_SENSOR_UPDATE,        /**< Gamepad sensor was updated */
                //     SDL_EVENT_GAMEPAD_UPDATE_COMPLETE,      /**< Gamepad update is complete */
                //     SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED,  /**< Gamepad Steam handle has changed */


                switch (event.type) {
                case SDL_EVENT_GAMEPAD_ADDED: {
                    int device_index = event.gdevice.which;
                    Q_ASSERT_X(!m_gamepads.contains(device_index), __FUNCTION__, "receivet invalid device index");

                    m_gamepads[device_index] = SDL_OpenGamepad(device_index);

                    appInstance->postEvent(appInstance,
                                           new QSDLGamepadEvent(event,
                                                                static_cast<SDL_EventType>(event.type)));
                    break;
                }

                case SDL_EVENT_GAMEPAD_REMOVED: {
                    int device_index = event.gdevice.which;
                    Q_ASSERT_X(m_gamepads.contains(device_index), __FUNCTION__, "receivet invalid device index");

                    SDL_CloseGamepad(m_gamepads.take(device_index));

                    appInstance->postEvent(appInstance,
                                           new QSDLGamepadEvent(event,
                                                                static_cast<SDL_EventType>(event.type)));
                    break;
                }

                case SDL_EVENT_GAMEPAD_REMAPPED:
                case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
                case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED: {
                    int device_index = event.gdevice.which;
                    Q_ASSERT_X(m_gamepads.contains(device_index), __FUNCTION__, "receivet invalid device index");

                    appInstance->postEvent(appInstance,
                                           new QSDLGamepadEvent(event,
                                                                static_cast<SDL_EventType>(event.type)));
                    break;
                }

                case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
                case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
                case SDL_EVENT_GAMEPAD_TOUCHPAD_UP: {
                    int device_index = event.gdevice.which;
                    Q_ASSERT_X(m_gamepads.contains(device_index), __FUNCTION__, "receivet invalid device index");

                    auto eventObj = new QSDLGamepadTouchpadEvent(event,
                                                                 static_cast<SDL_EventType>(event.type));

                    scanModifiers(*eventObj, device_index);

                    appInstance->postEvent(appInstance,
                                           eventObj);
                    break;

                }

                case SDL_EVENT_GAMEPAD_SENSOR_UPDATE: {
                    int device_index = event.gdevice.which;
                    Q_ASSERT_X(m_gamepads.contains(device_index), __FUNCTION__, "receivet invalid device index");

                    auto eventObj = new QSDLGamepadSensorEvent(event,
                                                               static_cast<SDL_EventType>(event.type));

                    scanModifiers(*eventObj, device_index);

                    appInstance->postEvent(appInstance,
                                           eventObj);
                    break;

                }

                case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                case SDL_EVENT_GAMEPAD_BUTTON_UP: {

                    int device_index = event.gdevice.which;
                    Q_ASSERT_X(m_gamepads.contains(device_index), __FUNCTION__, "receivet invalid device index");

                    auto eventObj = new QSDLGamepadButtonEvent(event,
                                                               static_cast<SDL_EventType>(event.type));

                    scanModifiers(*eventObj, device_index);

                    appInstance->postEvent(appInstance,
                                           eventObj);
                    break;

                }

                case SDL_EVENT_GAMEPAD_AXIS_MOTION: {

                    int device_index = event.gdevice.which;
                    Q_ASSERT_X(m_gamepads.contains(device_index), __FUNCTION__, "receivet invalid device index");

                    auto eventObj = new QSDLGamepadAxisEvent(event,
                                                             static_cast<SDL_EventType>(event.type));
                    scanModifiers(*eventObj, device_index);

                    appInstance->postEvent(appInstance,
                                           eventObj);
                    break;

                }

                default: {

                    appInstance->postEvent(appInstance,
                                           new QSDLEvent(event,
                                                         static_cast<SDL_EventType>(event.type)));
                    break;

                }
                }



            }
            while (SDL_PollEvent(&event));
        }

    }

}

void SDLEventManager::scanModifiers(QSDLGamepadInputEvent &event, int deviceIndex) {

    int modifiers = QSDLGamepadInputEvent::None;
    GamePadModifiers &gpModifiers = m_gamepadModifiers[deviceIndex];

    if (gpModifiers.pressedAxis.test(SDL_GAMEPAD_AXIS_LEFT_TRIGGER)) {
        modifiers = modifiers | QSDLGamepadInputEvent::L2;
    }

    if (gpModifiers.pressedAxis.test(SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)) {
        modifiers = modifiers | QSDLGamepadInputEvent::R2;
    }

    if (gpModifiers.pressedButtons.test(SDL_GAMEPAD_BUTTON_LEFT_SHOULDER)) {
        modifiers = modifiers | QSDLGamepadInputEvent::L1;
    }

    if (gpModifiers.pressedButtons.test(SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER)) {
        modifiers = modifiers | QSDLGamepadInputEvent::R1;
    }

    if (gpModifiers.pressedButtons.test(SDL_GAMEPAD_BUTTON_LEFT_STICK)) {
        modifiers = modifiers | QSDLGamepadInputEvent::L3;
    }

    if (gpModifiers.pressedButtons.test(SDL_GAMEPAD_BUTTON_RIGHT_STICK)) {
        modifiers = modifiers | QSDLGamepadInputEvent::R3;
    }

    event.setModifiers(modifiers);

}

void SDLEventManager::scanModifiers(QSDLGamepadButtonEvent &event, int deviceIndex) {

    GamePadModifiers &gpModifiers = m_gamepadModifiers[deviceIndex];

    gpModifiers.pressedButtons.set(event.data().gbutton.button, event.data().type == SDL_EVENT_GAMEPAD_BUTTON_DOWN);

    scanModifiers(static_cast<QSDLGamepadInputEvent&>(event), deviceIndex);
}

void SDLEventManager::scanModifiers(QSDLGamepadAxisEvent &event, int deviceIndex) {

    GamePadModifiers &gpModifiers = m_gamepadModifiers[deviceIndex];

    constexpr int TRIGGER_DEADZONE = 8000;
    gpModifiers.pressedAxis.set(event.data().gaxis.axis, std::abs(event.data().gaxis.value) > TRIGGER_DEADZONE);

    scanModifiers(static_cast<QSDLGamepadInputEvent&>(event), deviceIndex);

}


int SDLEventManager::eventDelay() const {
    return m_eventDelay;
}

void SDLEventManager::setEventDelay(int newEventDelay) {
    m_eventDelay = newEventDelay;
}
}
