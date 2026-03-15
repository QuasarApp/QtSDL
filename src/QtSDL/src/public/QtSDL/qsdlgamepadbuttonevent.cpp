//#
//# Copyright (C) 2025-2026 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "qsdlgamepadbuttonevent.h"
namespace QtSDL {

QSDLGamepadButtonEvent::QSDLGamepadButtonEvent(SDL_Event event, SDL_EventType type):
    QSDLGamepadInputEvent(event, type)  {}

const SDL_GamepadButtonEvent &QSDLGamepadButtonEvent::sdlEvent() const {
    return data().gbutton;
}


}
