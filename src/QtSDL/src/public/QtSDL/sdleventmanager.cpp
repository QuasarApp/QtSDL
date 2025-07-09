//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "qsdlevent.h"
#include "sdleventmanager.h"
#include <QCoreApplication>

namespace QtSDL {

SDLEventManager::SDLEventManager(QObject* parent): QThread(parent) {}


void SDLEventManager::stop() {
    m_quitFlag = true;
}

void QtSDL::SDLEventManager::run() {
    m_quitFlag = false;

    auto appInstance = QCoreApplication::instance();
    while (!m_quitFlag && appInstance) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            appInstance->postEvent(appInstance,
                                   new QSDLEvent(event,
                                                 static_cast<SDL_EventType>(event.type)));
        }

        if (m_eventDelay) {
            SDL_Delay(m_eventDelay);
        }
    }
}

int SDLEventManager::eventDelay() const {
    return m_eventDelay;
}

void SDLEventManager::setEventDelay(int newEventDelay) {
    m_eventDelay = newEventDelay;
}
}
