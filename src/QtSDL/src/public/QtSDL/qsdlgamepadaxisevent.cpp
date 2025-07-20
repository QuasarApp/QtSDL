//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qsdlgamepadaxisevent.h"

namespace QtSDL {


QSDLGamepadAxisEvent::QSDLGamepadAxisEvent(SDL_Event event, SDL_EventType type):QSDLEvent(event, type)  {}

const SDL_GamepadAxisEvent &QSDLGamepadAxisEvent::sdlEvent() const {
    return data().gaxis;
}

}
