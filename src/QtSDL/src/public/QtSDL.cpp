//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "QtSDL.h"


namespace QtSDL {

bool init() {
    initQtSDLResources();
    return true;
}

QString version() {
    return QTSDL_VERSION;
}


}
