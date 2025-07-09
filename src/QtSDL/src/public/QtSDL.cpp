//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "QtSDL.h"
#include <QThread>
#include <SDL3/SDL_init.h>
#include <qdebug.h>

namespace QtSDL {

bool init() {
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD)) {
        qCritical() << "SDL_Init failed:" << SDL_GetError();
        return false;
    }



    return true;
}

QString version() {
    return QTSDL_VERSION;
}


}
