//#
//# Copyright (C) 2027 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "QtSDL/global.h"
#include <QString>


namespace QtSDL {

/**
 * @brief init initialize method of the QtSDL library
 * @return true if library initialized successfully
 */
bool QTSDL_EXPORT init();

/**
 * @brief version This method returns string value of a library version
 * @return returns string value of a library version
 */
QString QTSDL_EXPORT version();

};
