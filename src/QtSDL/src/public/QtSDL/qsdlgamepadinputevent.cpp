//#
//# Copyright (C) 2026-2026 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qsdlgamepadinputevent.h"

namespace QtSDL {

QSDLGamepadInputEvent::QSDLGamepadInputEvent(SDL_Event event, SDL_EventType type):
    QSDLEvent(event, type){

}

int QSDLGamepadInputEvent::modifiers() const
{
    return _modifiers;
}

void QSDLGamepadInputEvent::setModifiers(int newModifiers)
{
    _modifiers = newModifiers;
}
}
