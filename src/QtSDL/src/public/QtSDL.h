//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "QtSDL/global.h"
#include <QString>


namespace QtSDL {

/**
 * @brief init main initialize method of The QtSDL library
 * @return true if library initialized successfull
 */
bool QTSDL_EXPORT init();

/**
 * @brief version This method return string value of a library version
 * @return string value of a library version
 */
QString QTSDL_EXPORT version();

};
