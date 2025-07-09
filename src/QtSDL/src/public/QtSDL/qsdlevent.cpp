//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "qsdlevent.h"

QSDLEvent::QSDLEvent(SDL_Event event, SDL_EventType type):
    QEvent(static_cast<QEvent::Type>(SDLType)) {
    _data = event;
    _sdlType = type;
}

void QSDLEvent::setAccepted(bool accepted) {
    QEvent::setAccepted(accepted);
}

QEvent *QSDLEvent::clone() const {
    return new QSDLEvent(data(), sdlType());
}

SDL_Event QSDLEvent::data() const {
    return _data;
}

void QSDLEvent::setData(const SDL_Event &newData) {
    _data = newData;
}

SDL_EventType QSDLEvent::sdlType() const
{
    return _sdlType;
}

void QSDLEvent::setSdlType(SDL_EventType newSdlType)
{
    _sdlType = newSdlType;
}
