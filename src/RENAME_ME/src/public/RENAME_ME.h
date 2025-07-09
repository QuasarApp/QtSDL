//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "RENAME_ME/global.h"
#include <QString>

inline void initRENAME_MEResources() { Q_INIT_RESOURCE(RENAME_ME); }

namespace RENAME_ME {

/**
 * @brief init main initialize method of The RENAME_ME library
 * @return true if library initialized successfull
 */
bool RENAME_ME_EXPORT init();

/**
 * @brief version This method return string value of a library version
 * @return string value of a library version
 */
QString RENAME_ME_EXPORT version();

};
