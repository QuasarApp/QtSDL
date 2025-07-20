//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "qsdlgamepadbuttonevent.h"
namespace QtSDL {

QSDLGamepadButtonEvent::QSDLGamepadButtonEvent(SDL_Event event, SDL_EventType type):QSDLEvent(event, type)  {}

const SDL_GamepadButtonEvent &QSDLGamepadButtonEvent::sdlEvent() const {
    return data().gbutton;
}


}
